/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:22:28 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:48:49 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sr;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	sr = malloc((ft_strlen(s2) + ft_strlen(s1) + 1) * sizeof(char));
	if (sr == 0)
		return (0);
	while (*(s1 + i) != 0)
	{
		*(sr + i) = *(s1 + k);
		i ++;
		k ++;
	}
	k = 0;
	while (k != ft_strlen(s2))
	{
		*(sr + i) = *(s2 + k);
		i ++;
		k ++;
	}
	*(sr + i) = 0;
	return (sr);
}
