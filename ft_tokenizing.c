/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:44:32 by mkibous           #+#    #+#             */
/*   Updated: 2024/02/21 18:42:41 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_printlist(t_elem *elem)
{
	char *str;
	char *token;
	ft_printf("✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥\n");
    ft_printf("✥  content     ✥    len       ✥   state      ✥    token  ✥\n");
    ft_printf("✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥\n");
	while (elem)
	{
	if(elem->state == 0 )
		str = "IN_DQUOTE";
	else if (elem->state == 1)
		str = "IN_QUOTE";
	else
		str = "GENERAL";
	if (elem->type == WHITE_SPACE)
		token = "WHITE_SPACE";
	else if(elem->type == NEW_LINE)
		token = "NEW_LINE";
	else if(elem->type == QOUTE)
		token = "QOUTE";
	else if (elem->type == DOUBLE_QUOTE)
		token = "DOUBLE_QUOTE";
	else if (elem->type == ESCAPE)
		token = "ESCAPE";
	else if (elem->type == ENV)
		token = "ENV";
	else if(elem->type == PIPE_LINE)
		token = "PIPE_LINE";
	else if(elem->type == REDIR_IN)
		token = "REDIR_IN";
	else if(elem->type == REDIR_OUT)
		token = "REDIR_OUT";
	else if(elem->type == DREDIR_OUT)
		token = "DREDIR_OUT";
	else if(elem->type == HERE_DOC)
		token = "HERE_DOC";
	else if(elem->type == WORD)
		token = "WORD";
	ft_printf("✥              ✥              ✥              ✥           ✥\n");
	ft_printf("✥  '%s'", elem->content);
	int j = elem->len - 2;
	while (j < 8)
	{
		ft_printf(" ");
		j++;
	}
	
	ft_printf("✥    %d         ✥   %s    ✥ %s     ✥\n", elem->len, str, token);
	ft_printf("✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥\n");
		elem = elem->next;
	}
}
void ft_free(char **str)
{
	int i;

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
int len (char *str)
{
	int i = 0;

	if(str[i] == '$')
		i++;
	if(str[i] && (str[i] == ' ' || str[i] == '\'' || str[i] == '"' || str[i] == '|' || (str[i] == '>' && str[i + 1] != '>') || (str[i] == '<' && str[i + 1] != '<'))) //handle < or > and << >> 
		i++;
	else if(str[i] && str[i+1] && (str[i] == '\\' || (str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')))
		i = 2;
	else 
		while (str[i])
		{
			if(str[i] == ' ' || str[i] == '\'' || str[i] == '"'
					|| (str[i] == '\\' && str[i+1]) || str[i] == '$' || str[i] == '|' || str[i] == '>' || str[i] == '<')
				break;
			i++;
		}
	return (i);
}
int ft_listing (char *str, t_elem **elem)
{
	int i = 0;
	int l = 0;
	char *content;
	l = len(str);
	content = (char *)malloc(l + 1);
	if (content == NULL)
		exit(1);
	while (i < l)
	{
		content[i] = str[i];
		i++;
	}
	content[i] = '\0';
	ft_lstadd_back(elem, ft_lstnew(content));
	return (l);
}
void	ft_token(t_elem *elem)
{
	// 	WORD = -1,
	// WHITE_SPACE = ' ',
	// NEW_LINE = '\n',
	// QOUTE = '\'',
	// DOUBLE_QUOTE = '\"',
	// ESCAPE = '\\',
	// ENV = '$',
	// PIPE_LINE = '|',
	// REDIR_IN = '<',
	// REDIR_OUT = '>',
	// HERE_DOC, 63 <<
	// DREDIR_OUT, 64 >>
	while (elem)
	{
		if (elem->content[0] == ' ')
			elem->type = WHITE_SPACE;
		else if(elem->content[0] == '\\' && elem->content[1] == 'n')
			elem->type = NEW_LINE;
		else if(elem->content[0] == '\'' && elem->state == GENERAL)
			elem->type = QOUTE;
		else if (elem->content[0] == '"' && elem->state == GENERAL)
			elem->type = DOUBLE_QUOTE;
		else if (elem->content[0] == '\\' && elem->content[1] != 'n')
			elem->type = ESCAPE;
		else if (elem->content[0] == '$' && elem->state != IN_QUOTE)
			elem->type = ENV;
		else if(elem->content[0] == '|' && elem->state == GENERAL)
			elem->type = PIPE_LINE;
		else if(elem->content[0] == '>' && elem->content[1] != '>' && elem->state == GENERAL)
			elem->type = REDIR_OUT;
		else if(elem->content[0] == '<' && elem->content[1] != '<' && elem->state == GENERAL)
			elem->type = REDIR_IN;
		else if(elem->content[0] == '>' && elem->content[1] == '>' && elem->state == GENERAL)
			elem->type = DREDIR_OUT;
		else if(elem->content[0] == '<' && elem->content[1] == '<' && elem->state == GENERAL)
			elem->type = HERE_DOC;
		else
			elem->type = WORD;
		elem = elem->next;
	}
}
int ft_chek(t_elem *elem)
{
	int b = 0;
	while (elem)
	{
		if (elem->type == REDIR_IN || elem->type == REDIR_OUT || elem->type == HERE_DOC || elem->type == DREDIR_OUT)
		{
			if(b == 1)
				return (1);
			b = 1;
		}
		if (elem->type == PIPE_LINE)
		{
			if(b != 0)
				return (1);
			b = 2;
		}
		if(elem->type == WORD && (b == 1 || b == 2))
			b = 0;
		// if wrod b = 0 if rdir and b = 1 eroor
		elem = elem->next;
	}
	if(b != 0)
		return (1);
	return(0);
}
void ft_tokenizing(char *line)
{
	int Q = 0;
	int DQ = 0;
	int closedQ = 0;
	// to cheke if " or ' are closed and to handle  "'mehdi'" or '"mehdi"'
	int i = 0;
	int l = 0;

	t_elem *elem;
	t_elem *last; 
	elem = NULL;
	while (line[i])
	{
		if (line[i] == '"' && DQ == 0 && Q == 0)
			(DQ = 1, closedQ = 1);
		else if (line[i] == '\"' && DQ == 1)
			(DQ = 0,closedQ = 0);
		else if (line[i] == '\'' && Q == 0 && DQ == 0)
			(Q = 1, closedQ = 2);
		else if (line[i] == '\'' && Q == 1)
			(Q = 0, closedQ = 0);
		if (i == l)
		{
			l += ft_listing(line + i, &elem);
			last = ft_lstlast(elem);
			if(last)
			{
				// if(closedQ == 0)
				// ft_printf("|%d|", last->state);
				if(closedQ == 1 && last->content[0] != '"')
					last->state = 0;
				else if(closedQ == 2 && last->content[0] != '\n')
					last->state = 1;
				else
					last->state = 2;
					
			}
		}
		i++;
	}
	ft_token(elem);
	if(closedQ != 0 || ft_chek(elem))
	{
		ft_printf("syntax error\n");
		return ;
	}
	ft_printlist(elem);
}