/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:39:19 by mkibous           #+#    #+#             */
/*   Updated: 2024/03/23 00:25:06 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_lstnew_cmd(char *content)
{
	t_cmd	*lst;

	lst = (t_cmd *)malloc(sizeof(t_cmd));
	if (lst == NULL)
		return (NULL);
	ft_memset(lst, 0, sizeof(t_cmd));
	lst->cmd = content;
	
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

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}
