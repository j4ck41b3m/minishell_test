/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:54:22 by jcolina-          #+#    #+#             */
/*   Updated: 2026/07/16 18:54:34 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *msh)
{
	char	*pwd;

	msh->last_status = 0;
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	ft_memfree(pwd);
}