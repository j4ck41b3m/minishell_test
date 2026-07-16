/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uprinter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:17:56 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:50:08 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	uprinter(va_list args)
{
	char				*tstr;
	size_t				count;
	int					base_count;
	unsigned long long	test;

	test = va_arg(args, unsigned int);
	base_count = uint_len(test, 10);
	tstr = ft_calloc((base_count + 1), sizeof(char));
	if (!tstr)
	{
		tstr = "(null)";
		ft_putstr_fd(tstr, 1);
		count = ft_strlen(tstr);
		free(tstr);
		return (count);
	}
	else
	{
		tstr = convert(tstr, 10, "0123456789", test);
		ft_putstr_fd(tstr, 1);
		count = ft_strlen(tstr);
		free(tstr);
		return (count);
	}
}
