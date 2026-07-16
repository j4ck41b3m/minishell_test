/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strprinter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:58:49 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:50:04 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	strprinter(va_list args)
{
	char	*tstr;

	tstr = va_arg(args, char *);
	if (tstr)
	{
		ft_putstr_fd(tstr, 1);
		return (ft_strlen(tstr));
	}
	else
	{
		tstr = "(null)";
		ft_putstr_fd(tstr, 1);
		return (ft_strlen(tstr));
	}
}
