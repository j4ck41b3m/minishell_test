#include "minishell.h"
#include "libft.h"

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	**paths;
	int		i;
	char	*tmp_str;
	char	*complete_path;

	while (env && ft_strncmp(env->key, "PATH", 4))
		env = env->next;
	if (!env)
		return (NULL);
	paths = ft_split(env->key, ':');
	i = -1;
	while (paths[++i])
	{
		tmp_str = ft_strjoin(paths[i], "/");
		complete_path = ft_strjoin(tmp_str, cmd);
		free_mem(tmp_str);
		if (!access(complete_path, X_OK))
		{
			free_mem_all(paths);
			return (complete_path);
		}
		free_mem(complete_path);
	}
	free_mem_all(paths);
	return (NULL);
}

void	exec_cmd(t_shell *msh)
{
	char	*cmd_path;
//	char	**envp;

//	envp = env_to_array(msh);
	if (msh->cmd->redirs->type != 0)
		dup2(msh->cmd->redirs->type, STDIN_FILENO);
	if (msh->cmd->redirs->type != 1)
		dup2(msh->cmd->redirs->type, STDOUT_FILENO);
	cmd_path = get_cmd_path(msh->cmd->arg[0], msh->env);
	if (!ft_isalnum(msh->cmd->arg[0][0]))
	{
		free_mem(cmd_path);
		cmd_path = msh->cmd->arg[0];
	}
//	execve(cmd_path, msh->cmd->arg, envp);
	exit(127);
}
