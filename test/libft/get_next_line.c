/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:39:36 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:49:57 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*getfileval(int fd, char *str)
{
	char	*buff;
	int		read_val;

	read_val = 1;
	while (!newline_found(str) && read_val != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		read_val = (int)read(fd, buff, BUFFER_SIZE);
		if ((!str && read_val == 0) || read_val == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_val] = '\0';
		str = ft_strjoin(str, buff);
	}
	return (str);
}

char	*gettheline(char *str)
{
	char	*line;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != '\n')
		line[i] = str[i];
	if (str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*restofline(char *str, char *tmp)
{
	char	*rest;
	int		i;
	int		j;

	i = ft_strlen(tmp);
	if (!str[i])
		return (free(str), NULL);
	j = 0;
	while (str[i++])
		j++;
	rest = malloc(sizeof(char) * (j + 1));
	if (!rest)
		return (NULL);
	i = ft_strlen(tmp);
	j = 0;
	while (str[i])
		rest[j++] = str[i++];
	rest[j] = '\0';
	free(str);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*tmp;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = getfileval(fd, str);
	if (!buffer)
	{
		if (str)
			free(str);
		str = NULL;
		return (NULL);
	}
	str = buffer;
	tmp = gettheline(str);
	str = restofline(str, tmp);
	return (tmp);
}
