/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:44:28 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:49:26 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*resu;

	i = 0;
	resu = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (resu == 0)
		return (0);
	while (i < ft_strlen(s))
	{
		*(resu + i) = (*f)(i, *(s + i));
		i ++;
	}
	*(resu + i) = 0;
	return (resu);
}
