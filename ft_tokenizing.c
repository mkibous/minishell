/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:44:32 by mkibous           #+#    #+#             */
/*   Updated: 2024/02/20 16:56:27 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

	if(str[i] && (str[i] == ' ' || str[i] == '\'' || str[i] == '"'))
		i++;
	else if((str[i] && str[i+1] && str[i] == '\\' && str[i+1] == 'n'))
		i = 1;
	else 
		while (str[i])
		{
			if(str[i] == ' ' || str[i] == '\'' || str[i] == '"' || (str[i] == '\\' && str[i+1] == 'n'))
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
		if((str[i] && str[i+1] && str[i] == '\\' && str[i+1] == 'n'))
			content[0] = '\n';
		else
			content[i] = str[i];
		i++;
	}
	content[i] = '\0';
	ft_lstadd_back(elem, ft_lstnew(content));
	return (l);
}
void ft_printlist(t_elem *elem)
{
	char *str;
	ft_printf("*************************************************************\n");
    ft_printf("*  content     *    len       *   state      *    token     *\n");
    ft_printf("*************************************************************\n");
	while (elem)
	{
	if(elem->state == 0 )
		str = "IN_DQUOTE";
	else if (elem->state == 1)
		str = "IN_QUOTE";
	else
		str = "GENERAL";
	ft_printf("*              *              *              *              *\n");
	ft_printf("*  '%s'        *    %d        *   %s         *    token     *\n", elem->content, elem->len, str);
	ft_printf("*************************************************************\n");
		elem = elem->next;
	}
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
	// HERE_DOC, 63
	// DREDIR_OUT, 64
	while (elem)
	{
		if (elem->content[0] == ' ')
			elem->type = ' ';
		else if(elem->content[0] == '\\' && elem->content[1] == 'n')
			elem->type = '\n';
		// else if (elem->content)
		
		elem = elem->next;
	}
	
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
	// ft_token(elem);
	ft_printlist(elem);
	ft_readline();
}