/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:52:17 by mkibous           #+#    #+#             */
/*   Updated: 2023/12/02 18:28:24 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hexad(void *str, int *l)
{
	int				i;
	char			*hexa;
	unsigned long	s;
	char			ind[17];

	hexa = "0123456789abcdef";
	i = 0;
	s = (unsigned long )str;
	ft_putstr("0x", l);
	while (s >= 16)
	{
		ind[i] = hexa[s % 16];
		s = s / 16;
		i++;
	}
	if (s < 16)
		ind[i] = hexa[s];
	while (i >= 0)
	{
		ft_putchar(ind[i], l);
		i--;
	}
}
