/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 19:51:18 by jcolina-          #+#    #+#             */
/*   Updated: 2026/07/16 19:51:43 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h";

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