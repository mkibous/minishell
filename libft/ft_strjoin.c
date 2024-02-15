/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:02:15 by mkibous           #+#    #+#             */
/*   Updated: 2023/11/19 15:24:06 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lt;
	size_t	l1;
	size_t	l2;
	size_t	i;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	lt = l2 + l1 +1;
	str = (char *)malloc(lt);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, lt);
	ft_strlcat(str, s2, lt);
	return (str);
}
