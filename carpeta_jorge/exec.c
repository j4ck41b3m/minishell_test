/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 12:02:51 by jcolina-          #+#    #+#             */
/*   Updated: 2026/07/16 19:53:55 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_memfree(tmp_str);
		if (!access(complete_path, X_OK))
		{
			ft_memfree_all(paths);
			return (complete_path);
		}
		ft_memfree(complete_path);
	}
	ft_memfree_all(paths);
	return (NULL);
}

void	ft_next_cmd(t_cmd *msh)
{
	t_cmd	*tmp;

	ft_memfree_all(msh->arg);
	if (msh->redirs->type != 0)
		close(msh->redirs->type);
	if (msh->redirs->type != 1)
		close(msh->redirs->type);
	tmp = msh;
	msh = msh->next;
	ft_memfree(tmp);
}

void	exec_cmd(t_shell *msh)
{
	char	*cmd_path;
	char	**envp;

	envp = env_to_array(msh);
	if (msh->cmd->redirs->type != 0)
		dup2(msh->cmd->redirs->type, STDIN_FILENO);
	if (msh->cmd->redirs->type != 1)
		dup2(msh->cmd->redirs->type, STDOUT_FILENO);
	cmd_path = get_cmd_path(msh->cmd->arg[0], msh->env);
	if (!ft_isalnum(msh->cmd->arg[0][0]))
	{
		ft_memfree(cmd_path);
		cmd_path = msh->cmd->arg[0];
	}
	execve(cmd_path, msh->cmd->arg, envp);
	exit(127);
}

void	child_proccess(t_shell *myshell, t_cmd *mycmd)
{
	if (myshell->cmd->is_builtin)
		ft_builtin(mycmd);
	else
		exec_cmd(myshell);
}

void	ft_executor(t_shell *myshell, char **envp)
{
	__pid_t	pid;

	ft_lst_env_init(&myshell->env, envp);
	while (myshell->cmd->next)
	{
		if (!ft_isascii(myshell->cmd->arg[0]))
		{
			myshell->last_status = 1;
			break ;
		}
		myshell->cmd = ft_split_shell(myshell, myshell->cmd->arg, 32);
		if (myshell->cmd->is_builtin)
		{
			ft_builtin(myshell->cmd);
		}
		else
		{
			pid = fork();
			if (pid == 0)
				child_proccess(myshell, myshell->cmd);
			else
				waitpid(-1, myshell->cmd->redirs->type, 0);
		}
		myshell->cmd = myshell->cmd->next;
	}
}
