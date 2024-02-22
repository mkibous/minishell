/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:44:32 by mkibous           #+#    #+#             */
/*   Updated: 2024/02/23 00:27:09 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_printlist(t_elem *elem, t_cmd *cmd)
{
	char *str;
	char *token;
	printf("✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥\n");
    printf("✥  content     ✥    len       ✥   state      ✥    token  ✥\n");
    printf("✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥\n");
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
	printf("✥              ✥              ✥              ✥           ✥\n");
	printf("✥  '%s'", elem->content);
	int j = elem->len - 2;
	while (j < 8)
	{
		printf(" ");
		j++;
	}
	
	printf("✥    %d         ✥   %s    ✥ %s     ✥\n", elem->len, str, token);
	printf("✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥✥\n");
		elem = elem->next;
	}
	while (cmd)
	{
		printf("%s| p%d e%d r%s \n", cmd->cmd, cmd->pipe, cmd->env, cmd->redir);
		if(cmd->file)
			printf("F%s\n", cmd->file);
		int j = 0;
		while (cmd->argv[j] != NULL)
		{
			printf("<%s>\n", cmd->argv[j]);
			j++;
		}
		j = 0;
		cmd = cmd->next;
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
	while (elem)
	{
		if (elem->content[0] == ' ')
			elem->type = WHITE_SPACE;
		else if(elem->state != GENERAL && elem->content[0] == '\\' && elem->content[1] == 'n')
			elem->type = NEW_LINE;
		else if(elem->content[0] == '\'' && elem->state == GENERAL)
			elem->type = QOUTE;
		else if (elem->content[0] == '"' && elem->state == GENERAL)
			elem->type = DOUBLE_QUOTE;
		else if (elem->state != GENERAL && elem->content[0] == '\\' && elem->content[1] != 'n')
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
int ft_count_argv(t_elem *elem)
{
	bool echo = 0;
	bool spaces = 0;
	int size = 0;
	while (elem && elem->type != PIPE_LINE)
	{
		if(ft_strncmp(elem->content, "echo", 5) == 0)
		{
			spaces = 1;
			size++;
			echo = 1;
		}
		else if(elem->type == REDIR_IN || elem->type == REDIR_OUT || elem->type == HERE_DOC || elem->type == DREDIR_OUT)
			size -= 2;
		else if (elem->type != DOUBLE_QUOTE && elem->type != QOUTE && (elem->type != WHITE_SPACE || (elem->type == WHITE_SPACE && elem->state != GENERAL)))
		{
			size++;
			spaces = 0;
		}
		else if (spaces == 0 && echo == 1 && (elem->type == WHITE_SPACE && elem->state == GENERAL))
		{
			size++;
			spaces = 1;
		}
		elem = elem->next;
	}
	return (size);
}

void ft_cmd(t_cmd **cmd, t_elem *elem)
{
	bool boolien = 0;
	bool redir = 0;
	bool echo = 0;
	bool spaces = 0;
	int j = 0;
	t_cmd *last;
	int size = 0;

	last = NULL;
	while (elem)
	{
		if(elem->type == WORD && boolien == 0)
		{
			if(ft_strncmp(elem->content, "echo", 5) == 0)
			{
				spaces = 1;
				echo = 1;
			}
			else
			{
				echo = 0;
				spaces = 0;
			}
			ft_lstadd_back_cmd(cmd ,ft_lstnew_cmd(elem->content));
			last = ft_lstlast_cmd(*cmd);
			size = ft_count_argv(elem);
			// printf("|||||%d||||", size);
			last->argv = (char **)malloc(sizeof(char *) * (size + 1));
			last->argv[size] = NULL;
			last->argv[j] = elem->content;
			j++;
			boolien = 1;
		}
		else if (boolien == 1 && spaces == 0 && echo == 1 && (elem->type == WHITE_SPACE && elem->state == GENERAL))
		{
			last->argv[j] = elem->content;
			j++;
			spaces = 1;
		}
		else if(elem->type == REDIR_IN || elem->type == REDIR_OUT || elem->type == HERE_DOC || elem->type == DREDIR_OUT)
		{
			last->redir =  elem->content;
			redir = 1;
		}
		else if (redir == 1 && elem->type == WORD)
		{
			redir = 0;
			last->file = elem->content;
			spaces = 1;
		}
		else if(boolien == 1  && (elem->type == ENV || elem->type == WORD || (elem->type == WHITE_SPACE && elem->state != GENERAL)))
		{
			last->argv[j] = elem->content;
			spaces = 0;
			j++;
		}
		if (elem->type == ENV)
		{
			last->env = 1;
			spaces = 0;
		}
		if (elem->type == PIPE_LINE)
		{
			last->pipe = 1;
			boolien = 0;
			redir = 0;
			spaces = 0;
			j = 0;
		}
		elem = elem->next;
	}
	
}
void ft_tokenizing(char *line, t_cmd **cmd)
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
				// printf("|%d|", last->state);
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
		printf("syntax error\n");
		return ;
	}
	ft_cmd(cmd, elem);
	// printf("%s", cmd->cmd);
	// ft_printlist(elem, *cmd);
}