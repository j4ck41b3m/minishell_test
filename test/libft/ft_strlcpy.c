/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:39:48 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:49:15 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (*(src + i) != 0)
	{
		i ++;
	}
	if (size > i + 1)
	{
		ft_memcpy(dst, src, i + 1);
	}
	else if (size != 0)
	{
		ft_memcpy(dst, src, size - 1);
		*(dst + size - 1) = 0;
	}
	return (i);
}
