/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:16:04 by jcolina-          #+#    #+#             */
/*   Updated: 2026/05/01 13:46:24 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*convert(char *tstr, int num, char *bchain, unsigned long long test)
{
	int	base_count;

	base_count = uint_len(test, num);
	while (base_count)
	{
		base_count--;
		tstr[base_count] = bchain[test % num];
		test /= num;
	}
	return (tstr);
}
