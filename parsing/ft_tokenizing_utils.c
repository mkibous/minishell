/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:45:52 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/28 14:31:54 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_else_token(t_elem *elem)
{
	if ((elem->content[0] == ' ' || elem->content[0] == '\t')
		&& elem->state == GENERAL)
		return (elem->type = WHITE_SPACE, 1);
	else if (elem->content[0] == '\'' && elem->state == GENERAL
		&& (!elem->prev || (elem->prev
				&& ft_strncmp(elem->prev->content, "\\", 2) != 0)
			|| (elem->prev && elem->prev->state != GENERAL
				&& ft_strncmp(elem->prev->content, "\\", 2) == 0)))
		return (elem->type = QOUTE, 1);
	else if (elem->content[0] == '"' && elem->state == GENERAL)
		return (elem->type = DOUBLE_QUOTE, 1);
	return (0);
}

void	ft_token(t_elem *elem)
{
	if (ft_else_token(elem))
		;
	else if (elem->content[0] == '|' && elem->state == GENERAL)
		elem->type = PIPE_LINE;
	else if (elem->content[0] == '>' && elem->content[1] != '>'
		&& elem->state == GENERAL)
		elem->type = REDIR_OUT;
	else if (elem->content[0] == '<' && elem->content[1] != '<'
		&& elem->state == GENERAL)
		elem->type = REDIR_IN;
	else if (elem->content[0] == '>' && elem->content[1] == '>'
		&& elem->state == GENERAL)
		elem->type = DREDIR_OUT;
	else if (elem->content[0] == '<' && elem->content[1] == '<'
		&& elem->state == GENERAL)
		elem->type = HERE_DOC;
	else
		elem->type = WORD;
}

void	ft_open_quote(t_vars *vars, t_table *table)
{
	if (vars->last && ft_strncmp(vars->last->content, "\"", 2) == 0
		&& vars->dq == 0 && vars->q == 0)
		(1) && (vars->dq = 1, vars->closedq = 1);
	else if (vars->last && ft_strncmp(vars->last->content, "\"", 2) == 0
		&& vars->dq == 1)
		(1) && (vars->dq = 0, vars->closedq = 0);
	else if (vars->last && ft_strncmp(vars->last->content, "\'", 2) == 0
		&& vars->q == 0 && vars->dq == 0)
		(1) && (vars->q = 1, vars->closedq = 2);
	else if (vars->last && ft_strncmp(vars->last->content, "\'", 2) == 0
		&& vars->q == 1)
		(1) && (vars->q = 0, vars->closedq = 0);
	vars->last->pid = table->pid;
	if (vars->last)
	{
		if ((vars->closedq == 1 && vars->last->content[0] != '"'))
			vars->last->state = 0;
		else if (vars->closedq == 2 && vars->last->content[0] != '\'')
			vars->last->state = 1;
		else
			vars->last->state = 2;
	}
}

void	ft_state(char **line, t_vars *vars, t_elem **elem, t_table *table)
{
	if (vars->i == vars->l)
	{
		vars->l += ft_listing(line, elem, table, vars);
		vars->last = ft_lstlast(*elem);
		ft_open_quote(vars, table);
		ft_token(vars->last);
		if (vars->last->type == HERE_DOC)
			vars->redir = 1;
		else if (vars->redir == 1 && (vars->last->type == WHITE_SPACE
				|| vars->last->type == WORD))
			vars->redir = 2;
		else if (vars->redir == 2 && vars->last->type != WORD
			&& vars->last->type != QOUTE && vars->last->type != DOUBLE_QUOTE)
			vars->redir = 0;
		if (vars->env != 0 && vars->last->type != WHITE_SPACE)
		{
			(1) && (vars->last->state = IN_DQUOTE, vars->env--);
			if (ft_strncmp(vars->last->content, "\"", 2) == 0)
				vars->closedq = 0;
			vars->last->type = WORD;
		}
	}
	if ((*line)[vars->i] != '\0')
		vars->i++;
}

void	ft_join(t_elem *elem)
{
	t_elem	*tmp;

	ft_escape(elem);
	while (elem)
	{
		if (elem->next && (elem->type == WORD))
		{
			(1) && (tmp = elem, elem = elem->next);
			while (elem->next && (elem->type == DOUBLE_QUOTE
					|| elem->type == QOUTE))
				elem = elem->next;
			ft_newstate(&elem, &tmp);
		}
		else
			elem = elem->next;
	}
}
