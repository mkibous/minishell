/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:39:19 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/11 18:55:21 by mkibous          ###   ########.fr       */
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

int	env_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	last_arg(t_cmd *cmd, t_table *table)
{
	int		i;
	char	**str;

	i = 0;
	if (cmd && cmd->argv)
	{
		str = cmd->argv;
		while (str[i])
			i++;
		if (cmd && !cmd->next)
		{
			free(table->last_arg);
			table->last_arg = ft_strdup(cmd->argv[i - 1]);
		}
		else if (cmd && cmd->next)
		{
			free(table->last_arg);
			table->last_arg = ft_strdup("");
		}
	}
	else
	{
		free(table->last_arg);
		table->last_arg = ft_strdup("");
	}
}
