/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:12:51 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:47:50 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int a)
{
	int	isdigit;

	if (a >= 48 && a <= 57)
	{
		isdigit = 1;
	}
	else
		isdigit = 0;
	return (isdigit);
}
