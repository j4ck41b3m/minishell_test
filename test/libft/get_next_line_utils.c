/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:15:37 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:49:55 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*newline_found(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\n')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*temp;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	temp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!temp)
		return (NULL);
	i = -1;
	while (s1[++i])
		temp[i] = s1[i];
	j = -1;
	while (s2[++j])
		temp[i++] = s2[j];
	temp[i] = '\0';
	return (free(s1), free(s2), temp);
}

void	*ft_gnl_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (count && size > SIZE_MAX / count)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < count)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}
