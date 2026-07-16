/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:14:37 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:48:10 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*a;
	size_t	i;

	a = (char *)b;
	i = 0;
	while (i < len)
	{
		*(a ++) = (char)c;
		i ++;
	}
	return (b);
}
