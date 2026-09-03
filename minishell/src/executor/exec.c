#include "minishell.h"
#include "libft.h"

t_status	prepare_redirections(t_shell *shell)
{
	t_cmd	*mycmd;
	int		tmp;
	int		ret;

	mycmd = shell->cmd;
	ret = 1;
	while (mycmd)
	{
		tmp = fill_redirs(shell, mycmd);
		if (!tmp)
			ret = 0;
		mycmd = mycmd->next;
	}
	if (ret)
		return (SUCCESS);
	else
		return (FAILURE);
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
	signal(SIGQUIT, SIG_DFL);
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
	pid_t	last_pid;
	t_cmd	*cmd;

	prev_fd = -1;
	last_pid = -1;
	cmd = shell->cmd;
	while (cmd)
	{
		if (cmd->arg && cmd->arg[0])
		{
			if (cmd->next && pipe(pipefd) < 0)
				return (exit_pipecmd(shell, "lol"));
			last_pid = fork();
			if (last_pid < 0)
				return (exit_pipecmd(shell, "fork"));
			if (last_pid == 0)
				exec_split(shell, cmd, prev_fd, pipefd);
			exec_split_second(cmd, &prev_fd, pipefd);
		}
		cmd = cmd->next;
	}
	exec_pipeline_cont(shell, last_pid);
}

void	executor(t_shell *shell)
{
	classify_cmd(&shell->cmd);
	if (!shell->cmd)
		return ;
	if (prepare_redirections(shell) == SUCCESS)
	{
		if (g_signal == S_SIGINT_CMD)
			return ;
		if (!shell->cmd->next)
			execute_single(shell);
		else
			execute_pipeline(shell);
	}
}
