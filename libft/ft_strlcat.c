/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:39:18 by mkibous           #+#    #+#             */
/*   Updated: 2023/11/17 15:25:16 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ld;
	size_t	ls;

	if ((dst == NULL && src == NULL) || size == 0)
	{
		if (src && !size)
			return (ft_strlen(src));
		return (0);
	}
	i = 0;
	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	if (size <= ld)
		return (ls + size);
	while (src[i] && i + ld + 1 < (size))
	{
		dst[ld + i] = src[i];
		i++;
	}
	if (ld + i < size)
		dst[ld + i] = '\0';
	return (ld + ls);
}
