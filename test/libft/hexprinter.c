/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexprinter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:21:23 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:50:00 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*strchoser(char type, unsigned long long test)
{
	char	*tstr;
	int		base_count;

	base_count = uint_len(test, 16);
	tstr = ft_calloc((base_count + 1), sizeof(char));
	if (tstr == 0)
		tstr = "(null)";
	else
	{
		if (type == 'p')
			ft_putstr_fd("0x", 1);
		if (type == 'x' || type == 'p')
			tstr = convert(tstr, 16, "0123456789abcdef", test);
		else
			tstr = convert(tstr, 16, "0123456789ABCDEF", test);
	}
	return (tstr);
}

int	hexprinter(char type, unsigned long long test)
{
	char	*tstr;
	size_t	count;

	if (type == 'p' && test == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	else
	{
		tstr = strchoser(type, test);
		ft_putstr_fd(tstr, 1);
		count = ft_strlen(tstr);
		free(tstr);
		if (type == 'p')
			return (count + 2);
		else
			return (count);
	}
}
