/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:44:32 by mkibous           #+#    #+#             */
/*   Updated: 2024/03/29 14:54:21 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_chek_quotes(t_elem *elem, int *b, int *Q)
{
	if (elem->type == DOUBLE_QUOTE)
	{
		if (*Q == 0)
			*Q = 1;
		else if (*Q == 1)
			*Q = 0;
	}
	else if (elem->type == QOUTE)
	{
		if (*Q == 0)
			*Q = 2;
		else if (*Q == 2)
			*Q = 0;
	}
	if (elem->type == REDIR_IN || elem->type == REDIR_OUT
		|| elem->type == HERE_DOC || elem->type == DREDIR_OUT)
	{
		if (*b == 1)
			return (1);
		*b = 1;
	}
	if ((elem->type == WORD || elem->state != GENERAL || elem->type == ENV)
		&& (*b == 1 || *b == 2))
		*b = 0;
	return (0);
}

int	chek_prev(t_elem *elem)
{
	if (elem->prev)
		elem = elem->prev;
	while (elem)
	{
		if (elem->type != WHITE_SPACE)
			return (0);
		elem = elem->prev;
	}
	return (1);
}

int	ft_chek(t_elem *elem)
{
	int	b;
	int	q;

	b = 0;
	q = 0;
	while (elem)
	{
		if (ft_chek_quotes(elem, &b, &q))
			return (1);
		if (elem->type == PIPE_LINE)
		{
			if (b != 0 || chek_prev(elem) == 1)
				return (1);
			b = 2;
		}
		if (elem->content[0] == '\\' && elem->type == WORD
			&& elem->state == GENERAL && !elem->content[1]
			&& (!elem->next || elem->next->content[0] != '\''))
			return (1);
		elem = elem->next;
	}
	if (b != 0 || q != 0)
		return (1);
	return (0);
}

char	*ft_get_escape(char c, t_state state)
{
	if (c == 't')
		return (ft_strdup("\\t"));
	else if (c == 'b')
		return (ft_strdup("\\b"));
	else if (c == 'r')
		return (ft_strdup("\\r"));
	else if (c == '\"' && state != IN_QUOTE)
		return (ft_strdup("\""));
	else if (c == '\"' && state == IN_QUOTE)
		return (ft_strdup("\""));
	else if (c == '\'')
		return (ft_strdup("\'"));
	else if (c == '$' && state == IN_QUOTE)
		return (ft_strdup("\\$"));
	else if (c == '$' && state != IN_QUOTE)
		return (ft_strdup("$"));
	else
		return (ft_strdup("\\"));
}

void	ft_join(t_elem *elem)
{
	t_elem	*tmp;
	char 	*str;

	while (elem)
	{
		if (elem->next && (elem->type == WORD))
		{
			(1) && (tmp = elem, elem = elem->next);
			while (elem->next && (elem->type == DOUBLE_QUOTE
					|| elem->type == QOUTE))
				elem = elem->next;
			if (elem->type == WORD)
			{
				str = ft_strjoin(tmp->content, elem->content);
				free(tmp->content);
				tmp->content = ft_strdup(str);
				free(str);
				if(elem->state == IN_QUOTE || tmp->state == IN_QUOTE)
					tmp->state = IN_QUOTE;
				if (elem->state == IN_DQUOTE || tmp->state == IN_DQUOTE)
					tmp->state = IN_DQUOTE;
				if (elem->next)
					elem->next->prev = elem->prev;
				elem->prev->next = elem->next;
				(1) && (free(elem->content), free(elem), elem = tmp);
			}
			else
				elem = tmp->next;
		}
		else
			elem = elem->next;
	}
}
