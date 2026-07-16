/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:41:59 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:47:46 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int a)
{
	int	isalpha;

	if (a >= 65 && a <= 90)
	{
		isalpha = 1;
	}
	else if (a >= 97 && a <= 122)
	{
		isalpha = 1;
	}
	else
		isalpha = 0;
	return (isalpha);
}
