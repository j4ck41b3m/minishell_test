/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:13:29 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:49:41 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char s1, const char *set)
{
	size_t	k;

	k = 0;
	while (*(set + k) != 0)
	{
		if (s1 == *(set + k))
			return (1);
		k ++;
	}
	return (0);
}

static char	*stri(const char *ogstr, size_t	sl, size_t	el)
{
	char	*sr;
	size_t	k;
	size_t	len;

	len = el - (sl - 1);
	if (len <= 0 || sl >= ft_strlen(ogstr))
		return (ft_strdup(""));
	sr = ft_calloc(len + 1, sizeof(char));
	if (sr == 0)
		return (0);
	k = 0;
	while (k < len)
	{
		*(sr + k) = *(ogstr + sl + k);
		k ++;
	}
	return (sr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	srt_le;
	size_t	end_le;

	srt_le = 0;
	end_le = ft_strlen(s1) - 1;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	while (check(*(s1 + srt_le), set))
	{
		srt_le ++;
	}
	while (check(*(s1 + end_le), set))
	{
		end_le --;
	}
	return (stri(s1, srt_le, end_le));
}
