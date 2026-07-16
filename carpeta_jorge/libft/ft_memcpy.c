/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:54:34 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:48:02 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	if (dest == 0 && src == 0)
		return (dest);
	a = (unsigned char *)src;
	b = (unsigned char *)dest;
	while (i < n)
	{
		*(b ++) = *(a ++);
		i++;
	}
	return (dest);
}
