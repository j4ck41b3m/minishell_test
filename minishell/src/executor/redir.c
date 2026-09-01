#include "minishell.h"
#include "libft.h"

void	heredoc_loop(t_shell *shell, char *limit, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("\033[1;34m\002> \033[0m\002");
		if (g_signal == S_SIGINT_CMD || g_signal == S_CANCEL_EXEC)
		{
			free_mem(line);
			close(fd);
			end_shell(shell);
			exit(130);
		}
		if (!line || !ft_strcmp(line, limit))
		{
			free_mem(line);
			close(fd);
			end_shell(shell);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free_mem(line);
	}
}

int	heredoc(t_shell *shell, char *limit)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) < 0)
		return (ft_putendl_fd("failed to open pipe", 2), 1);
	pid = fork();
	if (pid < 0)
		return (ft_putendl_fd("failed to open fork", 2), 1);
	if (pid == 0)
	{
		signal(SIGINT, sigint_handler);
		g_signal = S_HEREDOC;
		close(fd[0]);
		heredoc_loop(shell, limit, fd[1]);
	}
	g_signal = S_HEREDOC_END;
	waitpid(pid, &status, 0);
	close(fd[1]);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_signal = S_SIGINT_CMD;
		return (-1);
	}
	return (fd[0]);
}

int	redirect(t_shell *shell, t_redir *tmp)
{
	int	fd;

	if (tmp->type == INPUT)
	{
		return (input_asignment(tmp));
	}
	else if (tmp->type == TRUNC)
	{
		fd = open(tmp->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		tmp->redir_out = fd;
	}
	else if (tmp->type == APPEND)
	{
		fd = open(tmp->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		tmp->redir_out = fd;
	}
	else if (tmp->type == HEREDOC)
	{
		fd = heredoc(shell, tmp->target);
		tmp->redir_in = fd;
		if (g_signal != S_CANCEL_EXEC)
			g_signal = S_BASE;
	}
	return (1);
}

int	fill_redirs(t_shell *shell, t_cmd *mycmd)
{
	t_redir	*myred;
	int		tmp;
	int		ret;

	ret = 1;
	myred = mycmd->redirs;
	while (myred)
	{
		tmp = redirect(shell, myred);
		if (!tmp)
			ret = 0;
		myred = myred->next;
	}
	return (ret);
}

void	apply_redirs(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->redir_in != -1 && redir->redir_in != STDIN_FILENO)
		{
			dup2(redir->redir_in, STDIN_FILENO);
			close(redir->redir_in);
		}
		if (redir->redir_out != -1 && redir->redir_out != STDOUT_FILENO)
		{
			dup2(redir->redir_out, STDOUT_FILENO);
			close(redir->redir_out);
		}
		redir = redir->next;
	}
}
