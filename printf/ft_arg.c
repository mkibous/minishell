/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:37:00 by mkibous           #+#    #+#             */
/*   Updated: 2023/12/02 16:07:39 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_arg(va_list args, char c, int *l)
{
	if (c == 'c')
		ft_putchar(va_arg(args, int), l);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), l);
	else if (c == 'p')
		ft_hexad(va_arg(args, void *), l);
	else if (c == 'd')
		ft_putnbr(va_arg(args, int), l);
	else if (c == 'i')
		ft_putnbr(va_arg(args, int), l);
	else if (c == 'u')
		ft_putu(va_arg(args, unsigned int), l);
	else if (c == 'x')
		ft_putx(va_arg(args, int), l);
	else if (c == 'X')
		ft_putupx(va_arg(args, int), l);
	else if (c == '%')
		ft_putchar('%', l);
	else
	{
		ft_putchar(c, l);
	}
}
