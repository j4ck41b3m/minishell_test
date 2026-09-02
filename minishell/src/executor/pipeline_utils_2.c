#include "minishell.h"

void	close_pids(t_shell *shell)
{
	t_redir	*redir;
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		redir = shell->cmd->redirs;
		while (redir)
		{
			if (redir->redir_in > 2)
				close(redir->redir_in);
			if (redir->redir_out > 2)
				close(redir->redir_out);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

void	exec_split(t_shell *shell, t_cmd *cmd, int prev_fd, int pipefd[2])
{
	g_signal = S_CMD;
	child_exec(shell, cmd, prev_fd, pipefd);
}

void	exec_split_second(t_cmd *cmd, int *prev_fd, int pipefd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

void	exec_pipeline_cont(t_shell *shell, pid_t last_pid)
{
	int	status;

	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->last_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit (core dumped)\n");
	}
	else
		shell->last_status = 1;
	while (waitpid(-1, NULL, 0) > 0)
		continue ;
	close_pids(shell);
}

void	exit_pipecmd(t_shell *shell, char *str)
{
	perror(str);
	shell->last_status = 1;
}
