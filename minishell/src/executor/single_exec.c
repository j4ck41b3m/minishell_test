#include "minishell.h"
#include "libft.h"

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	**paths;
	int		i;
	char	*tmp_str;
	char	*complete_path;
	char	*tmp;

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
		if (!access(complete_path, X_OK))
		{
			free_mem_all(paths);
			return (complete_path);
		}
		free(complete_path);
	}
	free_mem_all(paths);
	return (NULL);
}

void	exec_cmd(t_shell *msh)
{
	char	*cmd_path;
	char	**envp;
	pid_t	pid;
	int		owns_cmd_path;

	envp = env_to_array(msh);
	if (msh->cmd->redirs)
	{
		if (msh->cmd->redirs->redir_in != 0)
			dup2(msh->cmd->redirs->redir_in, STDIN_FILENO);
		if (msh->cmd->redirs->redir_out != 1)
			dup2(msh->cmd->redirs->redir_out, STDOUT_FILENO);
	}
	cmd_path = get_cmd_path(msh->cmd->arg[0], msh->env);
	owns_cmd_path = 1;
	if (!ft_isalnum(msh->cmd->arg[0][0]))
	{
		free_mem(cmd_path);
		cmd_path = msh->cmd->arg[0];
		owns_cmd_path = 0;
	}
	pid = fork();
	if (pid == 0)
		execve(cmd_path, msh->cmd->arg, envp);
	waitpid(-1, &msh->last_status, 0);
	free_mem_all(envp);
	if (owns_cmd_path)
		free_mem(cmd_path);
}
