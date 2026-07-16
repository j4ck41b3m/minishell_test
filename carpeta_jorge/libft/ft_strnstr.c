/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:43:32 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:49:33 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *bi, const char *li, size_t le)
{
	size_t	i;
	size_t	k;
	char	*t_big;

	i = 0;
	k = 0;
	t_big = (char *)bi;
	if (*li == 0)
		return (t_big);
	while (*(bi + i) != 0 && i < le)
	{
		while (*(bi + i + k) == *(li + k) && *(bi + i + k) != 0 && i + k < le)
		{
			k++;
			if (*(li + k) == 0)
				return (t_big + i);
		}
		i++;
		k = 0;
	}
	return (0);
}
