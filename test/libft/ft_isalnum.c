/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:23:15 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:47:44 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

int	ft_isalnum(int a)
{
	int	isalnum;

	if (a >= 48 && a <= 57)
	{
		isalnum = 1;
	}
	else
	{
		if (a >= 65 && a <= 90)
		{
			isalnum = 1;
		}
		else if (a >= 97 && a <= 122)
		{
			isalnum = 1;
		}
		else
			isalnum = 0;
	}
	return (isalnum);
}
