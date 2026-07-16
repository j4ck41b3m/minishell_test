/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:01:53 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:48:53 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const char	*src, size_t	size)
{
	size_t	dest_l;
	size_t	src_l;

	dest_l = ft_strlen(dst);
	src_l = ft_strlen(src);
	if (dest_l >= size)
		dest_l = size;
	if (dest_l == size)
	{
		return (size + src_l);
	}
	if (size - dest_l > src_l)
	{
		ft_memcpy(dst + dest_l, src, src_l + 1);
	}
	else
	{
		ft_memcpy(dst + dest_l, src, size - dest_l - 1);
		*(dst + size -1) = 0;
	}
	return (src_l + dest_l);
}
