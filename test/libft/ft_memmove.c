/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:14:44 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:48:07 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void	*dest, const void	*src, size_t	n)
{
	size_t	i;
	char	*a;
	char	*b;

	i = 0;
	a = (char *)src;
	b = (char *)dest;
	if (dest == 0 && src == 0)
		return (0);
	if (b > a)
	{
		while (n -- > 0)
			*(b + n) = *(a + n);
	}
	else
	{
		while (i < n)
		{
			*(b ++) = *(a ++);
			i ++;
		}
	}
	return (dest);
}
