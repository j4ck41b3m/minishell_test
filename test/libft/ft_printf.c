/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:55:12 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:48:12 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	subprint(char type, va_list args)
{
	if (type == 'i' || type == 'd')
		return (nbrprinter(args));
	if (type == 'u')
		return (uprinter(args));
	if (type == 'x' || type == 'X')
		return (hexprinter(type, va_arg(args, unsigned int)));
	if (type == 's')
		return (strprinter(args));
	if (type == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
		return (1);
	}
	if (type == 'p')
		return (hexprinter(type, (unsigned long long)va_arg(args, void *)));
	if (type == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	size_t	count;
	size_t	i;
	va_list	args;

	va_start(args, str);
	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar_fd(str[i], 1);
			count ++;
			i++;
		}
		else
		{
			count += subprint(str[i + 1], args);
			i += 2;
		}
	}
	va_end(args);
	return (count);
}
