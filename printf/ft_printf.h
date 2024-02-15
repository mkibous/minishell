/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:03:24 by mkibous           #+#    #+#             */
/*   Updated: 2023/11/30 14:41:15 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

void	ft_putchar(char c, int *l);
void	ft_putstr(char *s, int *l);
int		ft_printf(const char *str, ...);
void	ft_hexad(void *str, int *l);
void	ft_putnbr(int nb, int *l);
void	ft_putu(unsigned int nb, int *l);
void	ft_putx(unsigned int s, int *l);
void	ft_putupx(unsigned int s, int *l);
void	ft_arg(va_list args, char c, int *l);
#endif