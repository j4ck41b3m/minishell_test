/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 17:57:19 by jcolina-          #+#    #+#             */
/*   Updated: 2026/07/16 18:25:05 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_shell *msh)
{
	int	i;

	i = 1;
	msh->last_status = 0;
	if (msh->cmd->arg[1] && !ft_strncmp(msh->cmd->arg[1], "-n", 2))
		i++;
	while (msh->cmd->arg[i])
	{
		ft_putstr_fd(msh->cmd->arg[i++], msh->cmd->redirs->type);
		if (msh->cmd->arg[i])
			ft_putchar_fd(32, msh->cmd->redirs->type);
	}
	if (!(msh->cmd->arg[1] && !ft_strncmp(msh->cmd->arg[1], "-n", 2)))
		ft_putchar_fd(10, msh->cmd->redirs->type);
}
