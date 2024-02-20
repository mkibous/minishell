/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:06:52 by mkibous           #+#    #+#             */
/*   Updated: 2024/02/20 12:30:50 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_lstadd_front(t_elem **lst, t_elem *new)
{
	if (!lst || !new)
		return ;
	if (lst && new)
    {
        (*lst)->prev = new;
		new->next = *lst;
    }
	if (new)
		*lst = new;
}
int	ft_lstsize(t_elem *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
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