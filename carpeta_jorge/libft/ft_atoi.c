/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:19:22 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:46:44 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkspace(int a)
{
	if ((a >= 9 && a <= 13) || a == 32)
	{
		return (1);
	}
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		res;
	int		isneg;

	res = 0;
	i = 0;
	isneg = 0;
	while (checkspace(*(nptr + i)) != 0)
		i++;
	if (*(nptr + i) == '+' && *(nptr + i + 1) != '-')
		i++;
	if (*(nptr + i) == '-')
	{
		isneg = 1;
		i++;
	}
	while (ft_isdigit(*(nptr + i)) != 0 && *(nptr + i) != 0)
	{
		res *= 10;
		res += *(nptr + i) - 48;
		i++;
	}
	if (isneg != 0)
		res *= -1;
	return (res);
}
