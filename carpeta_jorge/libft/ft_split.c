/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:33:16 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:48:30 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*makeit(const char *s, int strnum, int i)
{
	char	*sr;
	int		k;

	k = 0;
	sr = malloc((i - strnum + 1) * sizeof(char));
	if (sr == 0)
		return (0);
	while (strnum < i)
	{
		*(sr + k) = *(s + strnum);
		k ++;
		strnum ++;
	}
	*(sr + k) = 0;
	return (sr);
}

static void	*freeit(char **strs, int c)
{
	int	i;

	i = 0;
	while (i < c)
	{
		free(*(strs + i));
		i ++;
	}
	free(strs);
	return (0);
}

static char	**assignit(const char *s, char c, char **strs, int strnum)
{
	size_t	i;
	int		k;

	i = 0;
	k = 0;
	while (i <= ft_strlen(s))
	{
		if (*(s + i) != c && strnum < 0)
			strnum = i;
		else if ((*(s + i) == c || i == ft_strlen(s)) && strnum >= 0)
		{
			*(strs + k) = makeit(s, strnum, i);
			if (*(strs + k) == 0)
				return (freeit(strs, k));
			strnum = -1;
			k ++;
		}
		i ++;
	}
	return (strs);
}

static int	countit(const char *s, char c)
{
	int	a;
	int	b;
	int	fabool;

	a = 0;
	b = 0;
	fabool = 0;
	while (*(s + b) != 0)
	{
		if (*(s + b) != c && fabool == 0)
		{
			fabool = 1;
			a ++;
		}
		else if (*(s + b) == c)
			fabool = 0;
		b ++;
	}
	return (a);
}

char	**ft_split(const char *s, char c)
{
	int		strnum;
	char	**strs;

	strnum = -1;
	strs = ft_calloc((countit(s, c) + 1), sizeof(char *));
	if (strs == 0)
		return (0);
	return (assignit(s, c, strs, strnum));
}
