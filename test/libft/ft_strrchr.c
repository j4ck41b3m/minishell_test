/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:49:07 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:49:38 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*t;
	char	o;

	i = 0;
	t = 0;
	o = (char)c;
	while (*(s + i) != 0)
	{
		if (*(s + i) == o)
		{
			t = (char *)(s + i);
		}
		i ++;
	}
	if (o == '\0')
		t = (char *)(s + i);
	return (t);
}
