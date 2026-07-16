/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:25:01 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:47:53 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*iszero(char *resu)
{
	if (resu == 0)
		return (0);
	*resu = '0';
	*(resu + 1) = 0;
	return (resu);
}

char	*assignit(int n, long tn, int ncount, int fakebool)
{
	int		i;
	char	*resu;

	if (fakebool == 0)
		resu = malloc((ncount + 1) * sizeof(char));
	else
		resu = malloc((ncount + 2) * sizeof(char));
	if (resu == 0)
		return (0);
	i = ncount - (1 - fakebool);
	while (tn != 0)
	{
		*(resu + i) = ((tn % 10 + 48));
		tn = tn / 10;
		i --;
	}
	*(resu + ncount + fakebool) = 0;
	if (n < 0)
		*resu = '-';
	return (resu);
}

int	countit(long tn)
{
	int	count;

	count = 0;
	while (tn != 0)
	{
		tn /= 10;
		count ++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*resu;
	int		ncount;
	int		fakebool;
	long	tn;

	tn = n;
	fakebool = 0;
	if (tn < 0)
	{
		fakebool = 1;
		tn = -tn;
	}
	if (tn == 0)
	{
		resu = malloc(2 * sizeof(char));
		return (iszero(resu));
	}
	else
	{
		ncount = countit(tn);
		return (assignit(n, tn, ncount, fakebool));
	}
}
