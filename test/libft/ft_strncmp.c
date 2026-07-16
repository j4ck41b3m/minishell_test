/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:52:58 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:49:29 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char	*s1, const char	*s2, size_t	n)
{
	size_t			i;
	unsigned char	*rs1;
	unsigned char	*rs2;

	i = 0;
	rs1 = (unsigned char *)s1;
	rs2 = (unsigned char *)s2;
	while ((*(rs1 + i) != 0 || *(rs2 + i) != 0) && i != n)
	{
		if (*(rs1 + i) != *(rs2 + i))
		{
			if (*(rs1 + i) < *(rs2 + i))
				return (-1);
			else if (*(rs1 + i) > *(rs2 + i))
				return (1);
		}
		i++;
	}
	return (0);
}
