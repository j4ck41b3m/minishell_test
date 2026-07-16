/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 12:02:51 by jcolina-          #+#    #+#             */
/*   Updated: 2026/07/07 13:32:15 by jcolina-         ###   ########.fr       */
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

void	ft_builtin(t_cmd *mycmd)
{
	if (!ft_strncmp(mycmd->arg[0], "echo", 4))
		ft_echo(mycmd);
	else if (!ft_strncmp(mycmd->arg[0], "cd", 2))
		ft_cd(mycmd);
	else if (!ft_strncmp(mycmd->arg[0], "pwd", 3))
		ft_pwd(mycmd);
	else if (!ft_strncmp(mycmd->arg[0], "export", 6))
		ft_export(mycmd);
	else if (!ft_strncmp(mycmd->arg[0], "unset", 5))
		ft_unset(mycmd);
	else if (!ft_strncmp(mycmd->arg[0], "env", 3))
		ft_env(mycmd);
	else if (!ft_strncmp(mycmd->arg[0], "exit", 4))
		ft_exit(mycmd);
}

void	child_proccess(t_shell *myshell, t_cmd *mycmd)
{
	if (myshell->cmd->is_builtin)
		ft_builtin(mycmd);
	else
		exec_cmd(myshell, mycmd);
}

void	ft_executor(t_shell *myshell, char **envp)
{
	__pid_t	pid;

	ft_lst_env_init(&myshell->env, envp);
	while (myshell->cmd->next)
	{
		//to insert function that checks if arguments are in ascii if Bernardo didnt/*
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
