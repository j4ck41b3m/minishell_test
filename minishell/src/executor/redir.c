#include "minishell.h"
#include "libft.h"

void	connect_pipes(t_cmd **myred)
{
	t_cmd	*current;
	int		fd[2];

	current = *myred;
	while (current->next)
	{
		pipe(fd);
		while (current->redirs)
		{
			if (current->redirs->next)
				current->redirs = current->redirs->next;
			else
				current->redirs->redir_out = fd[1];
		}
		if (current->next && current->next->redirs)
			current->next->redirs->redir_in = fd[0];
		current = current->next;
	}
}

void	heredoc_loop(char *limit, int fd)
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
		free_mem(line);
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
		heredoc_loop(limit, fd[1]);
	}
	g_signal = S_HEREDOC_END;
	return (waitpid(-1, NULL, 0), close(fd[1]), fd[0]);
}

void	redirect(t_redir *tmp)
{
	int	fd;

	if (tmp->type == INPUT)
	{
		fd = open(tmp->target, O_RDONLY);
		tmp->redir_in = fd;
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
		fd = heredoc(tmp->target);
		tmp->redir_in = fd;
		if (g_signal != S_CANCEL_EXEC)
			g_signal = S_BASE;
	}
}

void	fill_redirs(t_cmd *mycmd)
{
	t_redir	*myred;

	myred = mycmd->redirs;
	while (myred)
	{
		redirect(myred);
		myred = myred->next;
	}
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
