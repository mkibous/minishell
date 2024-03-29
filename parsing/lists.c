/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:06:52 by mkibous           #+#    #+#             */
/*   Updated: 2024/03/19 15:24:14 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_elem	*ft_lstnew(char *content)
{
	t_elem	*lst;

	lst = (t_elem *)malloc(sizeof(t_elem));
	if (lst == NULL)
		return (NULL);
	lst->content = content;
	lst->len = ft_strlen(content);
	lst->prev = NULL;
	lst->next = NULL;
	return (lst);
}

void	ft_lstadd_back(t_elem **lst, t_elem *new)
{
	t_elem	*l;

	if (!lst || !new)
		return ;
	l = ft_lstlast(*lst);
	if (*lst)
	{
		new->prev = l;
		l->next = new;
	}
	else
		*lst = new;
}

t_elem	*ft_lstlast(t_elem *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	elem_free(t_elem *elem)
{
	t_elem *tmp;
	while (elem)
	{
		free(elem->content);
		tmp = elem->next;
		free(elem);
		elem = tmp;
		if(tmp)
			free(tmp);
	}
}