/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:19:31 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:48:40 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*rs;

	i = 0;
	rs = (char *) malloc(ft_strlen(s) + 1);
	if (rs == 0)
		return (0);
	while (*(s + i) != 0)
	{
		*(rs + i) = *(s + i);
		i ++;
	}
	*(rs + i) = 0;
	return (rs);
}
