/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:14:29 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:47:23 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*rs1;
	unsigned char	*rs2;	

	i = 0;
	rs1 = (unsigned char *)s1;
	rs2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if ((unsigned char)*(rs1 + i) != (unsigned char)*(rs2 + i))
		{
			return ((unsigned char)*(rs1 + i) - (unsigned char)*(rs2 + i));
		}
		i ++;
	}
	return (0);
}
