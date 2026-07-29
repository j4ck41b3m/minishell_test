#include "minishell.h"
#include "libft.h"

static void	heredoc_loop(char *limit, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("\033[1;34m> \033[0m");
		if (!line || (!ft_strncmp(limit, line, ft_strlen(limit))
				&& !ft_strncmp(limit, line, ft_strlen(line))))
			exit(EXIT_SUCCESS);
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		ft_memfree(line);
	}
}

int	heredoc(char *limit)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
		return (ft_putendl_fd("failed to open pipe", 2), 1);
	pid = fork();
	if (pid < 0)
		return (ft_putendl_fd("failed to open fork", 2), 1);
	if (pid == 0)
	{
		g_signal = S_HEREDOC;
		close(fd[0]);
		ft_heredoc_loop(limit, fd[1]);
	}
	g_signal = S_HEREDOC_END;
	return (waitpid(-1, NULL, 0), close(fd[1]), fd[0]);
}

void	redirect(t_cmd *tmp)
{
	int	fd;

	print_cmd(tmp);
	if (tmp->redirs->type == INPUT)
	{
		fd = open(tmp->redirs->target, O_RDONLY);
		tmp->redirs->redir_in = fd;
	}
	else if (tmp->redirs->type == TRUNC)
	{
		fd = open(tmp->redirs->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		tmp->redirs->redir_out = fd;
	}
	else if (tmp->redirs->type == APPEND)
	{
		fd = open(tmp->redirs->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		tmp->redirs->redir_out = fd;
	}
	else if (tmp->redirs->type == HEREDOC)
	{
		fd = ft_heredoc(tmp->redirs->target);
		tmp->redirs->redir_in = fd;
		if (g_signal != S_CANCEL_EXEC)
			g_signal = S_BASE;
	}
}
