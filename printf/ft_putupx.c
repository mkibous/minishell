/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putupx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:33:57 by mkibous           #+#    #+#             */
/*   Updated: 2023/12/02 18:28:53 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putupx(unsigned int s, int *l)
{
	int		i;
	char	*hexa;
	char	ind[17];

	hexa = "0123456789ABCDEF";
	i = 0;
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
