/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:51:35 by mkibous           #+#    #+#             */
/*   Updated: 2023/11/18 09:53:26 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	chek(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		l;
	int		n;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	l = ft_strlen(s1) - 1;
	while (s1[i] && chek(set, s1[i]))
		i++;
	while (l > i && chek(set, s1[l]))
		l--;
	n = l - i + 1;
	return (ft_substr(s1, i, n));
}
