/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbrprinter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:34:24 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:50:02 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbrprinter(va_list args)
{
	char	*tstr;
	size_t	count;

	tstr = ft_itoa(va_arg(args, int));
	ft_putstr_fd(tstr, 1);
	count = ft_strlen(tstr);
	free(tstr);
	return (count);
}
