/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:44:11 by mkibous           #+#    #+#             */
/*   Updated: 2023/11/17 20:12:53 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cont_int(int n)
{
	int	i;
	int	d;

	i = 0;
	d = n;
	if (d == 0)
		i++;
	while (d != 0)
	{
		d = d / 10;
		i++;
	}
	return (i);
}

static char	ft_trns(int n)
{
	char	c;

	if (n > 0)
		c = ((n % 10) + '0');
	else
		c = ((-(n % 10)) + '0');
	return (c);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		l;
	int		s;

	s = 0;
	l = ft_cont_int(n);
	if (n < 0)
	{
		l++;
		s = 1;
	}
	nbr = (char *)malloc(l + 1);
	if (nbr == NULL)
		return (NULL);
	nbr[l] = '\0';
	while (l > s)
	{
		l--;
		nbr[l] = ft_trns(n);
		n = n / 10;
	}
	if (s == 1)
		nbr[0] = '-';
	return (nbr);
}
