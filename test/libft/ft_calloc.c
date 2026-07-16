/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:39:58 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:46:57 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*ar;

	i = 0;
	ar = malloc(nmemb * size);
	if (ar == 0)
		return (0);
	while (i != nmemb * size)
	{
		*(ar + i) = 0;
		i ++;
	}
	return (ar);
}
