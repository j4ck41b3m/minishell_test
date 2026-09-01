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
		fill_redirs(shell, mycmd);
		mycmd = mycmd->next;
	}
	return (SUCCESS);
}

void	execute_single(t_shell *shell)
{
	int	ant_stdin;
	int	ant_stdout;

	if (shell->cmd->is_builtin)
	{
		ant_stdin = dup(STDIN_FILENO);
		ant_stdout = dup(STDOUT_FILENO);
		apply_redirs(shell->cmd);
		exec_builtin(shell);
		dup2(ant_stdin, STDIN_FILENO);
		dup2(ant_stdout, STDOUT_FILENO);
		close(ant_stdin);
		close(ant_stdout);
		return ;
	}
	else
		exec_cmd(shell);
	return ;
}

void	child_exec(t_shell *shell, t_cmd *cmd, int prev_fd, int pipefd[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	apply_redirs(cmd);
	if (cmd->is_builtin)
		exec_builtin(shell);
	else
		execve_cmd(shell, cmd);
	exit(shell->last_status);
}

void	execute_pipeline(t_shell *shell)
{
	int		prev_fd;
	int		pipefd[2];
	int		status;
	pid_t	pid;
	pid_t	last_pid;
	t_cmd	*cmd;
	t_redir	*redir;

	prev_fd = -1;
	last_pid = -1;
	cmd = shell->cmd;
	while (cmd)
	{
		if (!cmd->arg || !cmd->arg[0])
		{
			cmd = cmd->next;
			continue ;
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
	}
	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_status = 128 + WTERMSIG(status);
	else
		shell->last_status = 1;
	redir = shell->cmd->redirs;
	while (redir)
	{
		if (redir->redir_in > 2)
			close(redir->redir_in);
		if (redir->redir_out > 2)
			close(redir->redir_out);
		redir = redir->next;
	}
}

void	executor(t_shell *shell)
{
	classify_cmd(&shell->cmd);
	if (!shell->cmd)
		return ;
	prepare_redirections(shell);
	if (!shell->cmd->next)
		execute_single(shell);
	else
		execute_pipeline(shell);
}
