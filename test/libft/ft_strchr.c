/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:52:11 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:48:35 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	k;

	i = 0;
	k = (char)c;
	while (*(s + i) != 0)
	{
		if (*(s + i) == k)
		{
			return ((char *)(s + i));
		}
		i ++;
	}
	if (*(s + i) == k)
	{
		return ((char *)(s + i));
	}
	return (0);
}
