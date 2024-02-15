/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:55:04 by mkibous           #+#    #+#             */
/*   Updated: 2023/11/08 20:55:32 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int nb, int *l)
{
	if (nb == -2147483648)
	{
		ft_putstr("-2147483648", l);
		return ;
	}
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar('-', l);
	}
	if (nb < 10)
		ft_putchar(nb + '0', l);
	else
	{
		ft_putnbr(nb / 10, l);
		ft_putnbr(nb % 10, l);
	}
}
