/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:08:22 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:50:06 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	uint_len(unsigned long long n, int basenum)
{
	size_t				i;
	unsigned long long	bl;

	i = 1;
	bl = basenum;
	while (n >= bl)
	{
		n /= bl;
		i++;
	}
	return (i);
}
