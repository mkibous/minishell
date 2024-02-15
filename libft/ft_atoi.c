/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:51:46 by mkibous           #+#    #+#             */
/*   Updated: 2024/01/21 21:15:46 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_outoflimit(long long n, int s, int count)
{
	n = n * s;
	if (n > 2147483647 || n < -2147483648 || count > 19)
	{
		ft_putstr_fd("Error \nsome arguments are bigger than an integer", 2);
		exit(1);
	}
	return (n);
}

static int	ft_skipzero(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '0')
		i++;
	if (!ft_isdigit(str[i]) && i > 0)
		i--;
	return (i);
}

int	ft_atoi(const char *str)
{
	int				s;
	int				i;
	long long		nbr;
	int				count;

	i = 0;
	s = 1;
	nbr = 0;
	count = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	i = i + ft_skipzero(str + i);
	while (ft_isdigit(str[i]))
	{
		nbr = (nbr * 10) + (str[i] - 48);
		count++;
		i++;
	}
	return (ft_outoflimit(nbr, s, count));
}
