/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:45:02 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:47:20 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	tc;

	i = 0;
	str = (unsigned char *)s;
	tc = (unsigned char)c;
	while (i != n)
	{
		if (*(str + i) == tc)
			return (str + i);
		i ++;
	}
	return (0);
}
