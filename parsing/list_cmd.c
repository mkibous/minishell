/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:39:19 by mkibous           #+#    #+#             */
/*   Updated: 2024/02/23 00:23:20 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_lstnew_cmd(char *content)
{
	t_cmd	*lst;

	lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (lst == NULL)
		return (NULL);
	lst->cmd = content;
    lst->prev = NULL;
	lst->next = NULL;
	lst->file = NULL;
	lst->redir = NULL;
	return (lst);
}

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*l;

	if (!lst || !new)
		return ;
	l = ft_lstlast_cmd(*lst);
	if (*lst)
    {
        new->prev = l;
		l->next = new;
    }
	else
		*lst = new;
}

void	ft_lstadd_front_cmd(t_cmd **lst, t_cmd *new)
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
int	ft_lstsize_cmd(t_cmd *lst)
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
t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}