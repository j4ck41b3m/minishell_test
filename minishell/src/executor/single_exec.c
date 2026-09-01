#include "minishell.h"
#include "libft.h"

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	**paths;
	int		i;
	char	*tmp_str;
	char	*complete_path;
	char	*tmp;

	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK))
			return (ft_strdup(cmd));
		return (NULL);
	}
	if (!env)
		return (NULL);
	tmp = env_get(env, "PATH");
	paths = ft_split(tmp, ':');
	free_mem(tmp);
	i = -1;
	while (paths[++i])
	{
		tmp_str = ft_strjoin(paths[i], "/");
		complete_path = ft_strjoin(tmp_str, cmd);
		free(tmp_str);
		if (!access(complete_path, F_OK))
		{
			free_mem_all(paths);
			return (complete_path);
		}
		free(complete_path);
	}
	free_mem_all(paths);
	return (NULL);
}

void	execve_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*cmd_path;
	char	**envp;

	if (!cmd || !cmd->arg || !cmd->arg[0])
	{
		ft_putstr_fd("minishell: invalid command\n", 2);
		exit(127);
	}
	cmd_path = get_cmd_path(cmd->arg[0], shell->env);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->arg[0], 2);
		exit(127);
	}
	envp = env_to_array(shell);
	execve(cmd_path, cmd->arg, envp);
	perror(shell->name);
	free_mem_all(envp);
	free_mem(cmd_path);
	exit(127);
}

void	exec_cmd(t_shell *msh)
{
	pid_t	pid;
	int		status;
	t_redir	*redir;

	pid = fork();
	if (pid == 0)
	{
		g_signal = S_CMD;
		signal(SIGQUIT, SIG_DFL);
		apply_redirs(msh->cmd);
		execve_cmd(msh, msh->cmd);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		msh->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		msh->last_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit (core dumped)\n");
	}
	else
		msh->last_status = 1;
	redir = msh->cmd->redirs;
	while (redir)
	{
		if (redir->redir_in > 2)
			close(redir->redir_in);
		if (redir->redir_out > 2)
			close(redir->redir_out);
		redir = redir->next;
	}
}
