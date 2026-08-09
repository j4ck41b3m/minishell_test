#include "minishell.h"
#include "libft.h"

void	classify_cmd(t_cmd **cmd)
{
	t_cmd	*aux;

	aux = *cmd;
	while (aux)
	{
		if (aux->argc == 0)
			aux->is_builtin = 0;
		else
			aux->is_builtin = is_builtin(aux);
		aux = aux->next;
	}
}

t_status	prepare_redirections(t_shell *shell)
{
	t_cmd	*mycmd;

	mycmd = shell->cmd;
	while (mycmd)
	{
		fill_redirs(mycmd);
		mycmd = mycmd->next;
	}
/*	if (shell->cmd->next)
	{
		connect_pipes(&shell->cmd);
	}*/
	return (SUCCESS);
}

void	execute_single(t_shell *shell)
{
	if (shell->cmd->is_builtin)
	{
		fill_redirs(shell->cmd);
		apply_redirs(shell->cmd);
		exec_builtin(shell);
		return ;
	}
	else
		exec_cmd(shell);
	return ;
}

void	child_exec(t_shell *shell, t_cmd *cmd, int prev_fd, int pipefd[2])
{
	if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (cmd->next)
		dup2(pipefd[1], STDOUT_FILENO);
	fill_redirs(cmd);
	apply_redirs(cmd);
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (cmd->is_builtin)
		exec_builtin(shell);
	else
		execve_cmd(shell, cmd);
	exit(shell->last_status);		
}

void	execute_pipeline(t_shell *shell)
{
	int	prev_fd;
	int	pipefd[2];
	pid_t	pid;
	pid_t	last_pid;
	t_cmd	*cmd;

	prev_fd = -1;
	last_pid = -1;
	cmd = shell->cmd;
	while (cmd)
	{
		if (!cmd->arg || !cmd->arg[0])
		{
			cmd = cmd->next;
			continue;
		}
		if (cmd->next)
		{
			if (pipe(pipefd) < 0)
			{
				perror("pipe");
				shell->last_status = 1;
				return ;
			}
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			shell->last_status = 1;
			return ;
		}
		if (pid == 0)
		{
			g_signal = S_CMD;
			child_exec(shell, cmd, prev_fd, pipefd);
		}
		last_pid = pid;
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmd = cmd->next;
//		shell->cmd = cmd;
	}
	waitpid(last_pid, &shell->last_status, 0);
			/* if (ft_isascii(shell->cmd->arg[0][0]) == 0)
		{
			shell->last_status = 1;
			break ;
		} 
		if (shell->cmd->is_builtin)
			exec_builtin(shell);
		else
		{
			g_signal = S_CMD;
			pid = fork();
			if (pid == 0)
				execute_single(shell);
			else
				waitpid(pid, &shell->last_status, 0);
			handle_status(shell);
		}
		next_cmd(shell);*/
}

void	executor(t_shell *shell)
{
	classify_cmd(&shell->cmd);
	if (!shell->cmd)
		return ;
//	fill_redirs(shell->cmd);
	if (!shell->cmd->next)
		execute_single(shell);
	else
		execute_pipeline(shell);
}
