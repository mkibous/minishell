/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:44:32 by mkibous           #+#    #+#             */
/*   Updated: 2024/03/14 01:56:40 by mkibous          ###   ########.fr       */
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
		if (elem->state == 0)
			str = "IN_DQUOTE";
		else if (elem->state == 1)
			str = "IN_QUOTE";
		else
			str = "GENERAL";
		if (elem->type == WHITE_SPACE)
			token = "WHITE_SPACE";
		else if (elem->type == NEW_LINE)
			token = "NEW_LINE";
		else if (elem->type == QOUTE)
			token = "QOUTE";
		else if (elem->type == DOUBLE_QUOTE)
			token = "DOUBLE_QUOTE";
		else if (elem->type == ESCAPE)
			token = "ESCAPE";
		else if (elem->type == ENV)
			token = "ENV";
		else if (elem->type == PIPE_LINE)
			token = "PIPE_LINE";
		else if (elem->type == REDIR_IN)
			token = "REDIR_IN";
		else if (elem->type == REDIR_OUT)
			token = "REDIR_OUT";
		else if (elem->type == DREDIR_OUT)
			token = "DREDIR_OUT";
		else if (elem->type == HERE_DOC)
			token = "HERE_DOC";
		else if (elem->type == WORD)
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
		printf("%s| p%d e%d \n", cmd->cmd, cmd->pipe, cmd->env);
		int j = 0;
		if (cmd->argv)
		{
			while (cmd->argv[j] != NULL)
			{
				printf("<%s>\n", cmd->argv[j]);
				j++;
			}
		}
		j = 0;
		if (cmd->redir)
		{
			while (cmd->redir[j])
			{
				printf("redir : %s\n", cmd->redir[j]);
				printf("file : %s\n", cmd->file[j]);
				j++;
			}
		}
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
int len(char *str)
{
	int i = 0;
	int env = 0;
	if(str[i] == '\\' && str[i + 1] && str[i + 1] == '\'')
		return(1);
	// if (str[i] && ((str[i] == ' ' || str[i] == '\t') || str[i] == '\'' || str[i] == '"' || str[i] == '|' || (str[i] == '>' && str[i + 1] != '>') || (str[i] == '<' && str[i + 1] != '<'))) // handle < or > and << >>
	// 	i++;
	else if (str[i] && str[i + 1] && (str[i] == '\\' || (str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')))
		i = 2;
	else
	{
		if (str[i] == '$')
		{
			env = 1;
			i++;
		}
		while (str[i])
		{
			if (env == 1 && str[i - 1] == '$' &&  (str[i] == '$' || str[i] == '?'))
			{
				i++;
				break;
			}
			if ((str[i] == ' ' || str[i] == '\t') || str[i] == '\'' || str[i] == '"' || (str[i] == '\\' && str[i + 1]) || str[i] == '|' || str[i] == '>' || str[i] == '<' || (env == 1 && !ft_isalnum(str[i])) || str[i] == '$')
			{
				if (i == 0)
					return(1);
				break;
			}
			
			i++;
		}
	}
	return (i);
}
int ft_listing(char *str, t_elem **elem)
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
int ft_chek_if_escape(char c)
{
	if (c == 't' || c == 'b' || c == 'r' || c == '\\' || c == '\"' || c == '\''
		|| c == '$')
		return (1);
	return (0);
}
int ft_token_2(t_elem *elem)
{
	int ret;

	ret = 0;
	if ((elem->content[0] == ' ' || elem->content[0] == '\t')
				&& elem->state == GENERAL)
		(1) && (elem->type = WHITE_SPACE, ret = 1);
	else if (elem->state != GENERAL && elem->content[0] == '\\'
			&& elem->content[1] == 'n')
		(1) && (elem->type = NEW_LINE, ret = 1);
	else if (elem->content[0] == '\'' && elem->state == GENERAL
			&& (!elem->prev || (elem->prev
			&& ft_strncmp(elem->prev->content, "\\", 2) != 0)
			|| (elem->prev && elem->prev->state  != GENERAL
			&& ft_strncmp(elem->prev->content, "\\", 2) == 0)))
		(1) && (elem->type = QOUTE, ret = 1);
	else if (elem->content[0] == '"' && elem->state == GENERAL)
		(1) && (elem->type = DOUBLE_QUOTE, ret = 1);
	else if (elem->state == IN_DQUOTE && elem->content[0] == '\\'
			&& ft_chek_if_escape(elem->content[1]))
		(1) && (elem->type = ESCAPE, ret = 1);
	else if (elem->content[0] == '$' && (ft_strlen(elem->content) > 1
			|| (elem->state == GENERAL && elem->next
			&& (elem->next->content[0] == '\''
			|| elem->next->content[0] == '\"'))) && elem->state != IN_QUOTE)
		(1) &&(elem->type = ENV, ret = 1);
	return (ret);
}
void ft_token(t_elem *elem)
{
	while (elem)
	{
		if(ft_token_2(elem));
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
		elem = elem->next;
	}
}
int ft_chek_quotes(t_elem *elem, int *b, int *Q)
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
	return(0);
}
int ft_chek(t_elem *elem)
{
	int b;
	int Q;

	b = 0;
	Q = 0;
	while (elem)
	{
		if(ft_chek_quotes(elem, &b, &Q))
			return(1);
		if (elem->type == PIPE_LINE)
		{
			if (b != 0)
				return (1);
			b = 2;
		}
		if (elem->content[0] == '\\' && elem->type == WORD
				&& elem->state == GENERAL && !elem->content[1]
				&& (!elem->next || elem->next->content[0] != '\''))
			return(1);
		elem = elem->next;
	}
	if (b != 0 || Q != 0)
		return (1);
	return (0);
}
int ft_comp_n(char *str, t_elem *elem)
{
	int i;

	i = 0;
	if((elem->state == IN_DQUOTE && (elem->prev->type != DOUBLE_QUOTE
			|| elem->next->type != DOUBLE_QUOTE)) || (elem->state == IN_QUOTE
			&& (elem->prev->type != QOUTE || elem->next->type != QOUTE)))
			return(1);
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
	}
	if (str[i] == '\0' && i > 1)
		return (0);
	return (1);
}
void ft_count_echo_spaces(t_vars *vars, t_elem *elem)
{
	if (vars->spaces == 0 && vars->redir == 0 && vars->echo == 1 && elem->prev
				&& elem->type != WHITE_SPACE && elem->prev->type == WHITE_SPACE)
		{
			vars->size++;
			if (elem->type == WORD)
				(1) && (vars->n = 1, vars->size++);
			vars->spaces = 0;
		}
	else if (elem->type != DOUBLE_QUOTE && elem->type != QOUTE
				&& elem->type != WHITE_SPACE)
	{
		if(elem->type == WORD && elem->content[0] == '\0');
		else if (vars->redir == 1)
			vars->redir = 0;
		else 
			vars->size++;
		(1) && (vars->spaces = 0, vars->n = 1);
	}
}
int ft_count_argv(t_elem *elem, int *redirs)
{
	t_vars vars;
	ft_memset(&vars, 0, sizeof(vars));
	while (elem && elem->type != PIPE_LINE)
	{
		if (vars.n == 0 && vars.echo == 1 && !ft_comp_n(elem->content, elem))
			;
		else if (ft_strncmp(elem->content, "echo", 5) == 0)
			(1) && (vars.spaces = 1, vars.size++, vars.echo = 1);
		else if (elem->type == REDIR_IN || elem->type == REDIR_OUT
				|| elem->type == HERE_DOC || elem->type == DREDIR_OUT)
			(1) && ((*redirs)++, vars.redir = 1, vars.n = 1);
		else
			ft_count_echo_spaces(&vars, elem);
		if (elem->type == DOUBLE_QUOTE || elem->type == QOUTE)
			vars.spaces = 0;
		elem = elem->next;
	}
	return (vars.size);
}	
char *ft_get_escape(char c, t_state state)
{
	if (c == 't')
		return (ft_strdup("\\t"));
	else if (c == 'b')
		return (ft_strdup("\\b"));
	else if (c == 'r')
		return (ft_strdup("\\r"));
	else if (c == '\"' && state != IN_QUOTE)
		return (ft_strdup("\""));
	else if(c == '\"' && state == IN_QUOTE)
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
char *put_env(char *str, char **env, pid_t pid, int last_exit)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (!ft_strncmp(str, "$$", 3))
		return(ft_itoa((int)pid));
	if (!ft_strncmp(str, "$?", 3))
		return(ft_itoa(last_exit));
	while (env[i])
	{
		if (ft_strlen(env[i]) > ft_strlen(str))
			len = ft_strlen(env[i]);
		else
			len = ft_strlen(str);
		if (i % 2 == 0 && i != 1 && strncmp(str + 1, env[i], len) == 0)
		{
			i++;
			return (env[i]);
		}
		i++;
	}
	return (strdup(""));
}
void ft_envr(t_elem *elem, char **env, int last_exit)
{
	int i;

	i = 0;
	while (elem)
	{
		if (elem->type == ENV)
		{
			elem->type = WORD;
			elem->content = put_env(elem->content, env, elem->pid, last_exit);
		}
		if (elem->type == NEW_LINE)
		{
			elem->type = WORD;
			elem->content = strdup("\\n");
		}
		if (elem->content[0] == '\\' && elem->type == WORD
				&& elem->state == GENERAL)
			elem->content = ft_strdup(&elem->content[1]);
		else if (elem->type == ESCAPE)
		{
			elem->type = WORD;
			elem->content = ft_get_escape(elem->content[1], elem->state);
		}
		elem = elem->next;
	}
}
void ft_join(t_elem *elem)
{
	t_elem *tmp;
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
				tmp->content = ft_strjoin(tmp->content, elem->content);
				if (elem->next)
					elem->next->prev = elem->prev;
				elem->prev->next = elem->next;
				(1) && (free(elem), elem = tmp);
			}
			else
				elem = tmp->next;
		}
		else
			elem = elem->next;
	}
}
void ft_cmd(t_cmd **cmd, t_elem *elem, char **env, int last_exit)
{
	bool boolien = 0;
	bool redir = 0;
	bool prev_is_redir = 0;
	bool echo = 0;
	bool spaces = 0;
	bool n = 0;
	int j = 0;
	int i = 0;
	int redirs = 0;
	t_cmd *last;
	int size = 0;
	last = NULL;
	ft_envr(elem, env, last_exit);
	ft_join(elem);
	while (elem)
	{
		if(elem->content[0] == '\0' && elem->next)
			elem = elem->next;
		if (!n && echo == 1 && !ft_comp_n(elem->content, elem))
		{
			last->echo_new_line = 1;
		}
		else if ((elem->type == WORD) && boolien == 0 && redir == 0)
		{
			if (ft_strncmp(elem->content, "echo", 5) == 0)
			{
				spaces = 1;
				echo = 1;
				n = 0;
			}
			else
			{
				echo = 0;
				spaces = 0;
			}
			size = ft_count_argv(elem, &redirs);
			// printf("size : %d\n", size);
			if (prev_is_redir == 0)
			{
				ft_lstadd_back_cmd(cmd, ft_lstnew_cmd(elem->content));
				last = ft_lstlast_cmd(*cmd);
				if(redirs > 0)
				{
					last->redir = (char **)malloc(sizeof(char *) * (redirs + 1));
					if (last->redir == NULL)
						exit(1);
					last->file = (char **)malloc(sizeof(char *) * (redirs + 1));
					if (last->file == NULL)
						exit(1);
					last->redir[redirs] = NULL;
					last->file[redirs] = NULL;
				}
			}
			else
				last->cmd = elem->content;
			last = ft_lstlast_cmd(*cmd);
			// printf("%d\n", size);
			(*cmd)->count_cmd++;
			last->argv = (char **)malloc(sizeof(char *) * (size + 1));
			if (last->argv == NULL)
				exit(1);
			last->argv[size] = NULL;
			last->argv[j] = elem->content;
			if (last->prev && last->prev->pipe == 1)
				last->pipe = 1;
			j++;
			boolien = 1;
			prev_is_redir = 0;
		}
		else if (elem->type >= REDIR_IN && elem->type <= DREDIR_OUT)
		{
			if (boolien == 0 && redir == 0 && redirs == 0)
			{
				size = ft_count_argv(elem, &redirs);
				ft_lstadd_back_cmd(cmd, ft_lstnew_cmd(NULL));
				last = ft_lstlast_cmd(*cmd);
				last->redir = (char **)malloc(sizeof(char *) * (redirs + 1));
				if (last->redir == NULL)
					exit(1);
				last->file = (char **)malloc(sizeof(char *) * (redirs + 1));
				if (last->file == NULL)
					exit(1);
				last->redir[redirs] = NULL;
				last->file[redirs] = NULL;
			}
			last->redir[i] = elem->content;
			redir = 1;
			n = 1;
			redirs--;
		}
		else if (spaces == 0 && redir == 0 && echo == 1 && elem->type != PIPE_LINE && elem->prev && elem->type != WHITE_SPACE && elem->prev->type == WHITE_SPACE)
		{
			last->argv[j] = elem->prev->content;
			j++;
			if (elem->type == WORD)
			{
				last->argv[j] = elem->content;
				j++;
				n = 1;
			}
			spaces = 0;
		}
		else if (redir == 1 && (elem->type == WORD || elem->state != GENERAL))
		{
			redir = 0;
			last->file[i] = elem->content;
			i++;
			spaces = 0;
			prev_is_redir = 1;
			n = 1;
		}
		else if (boolien == 1 && (elem->type == ESCAPE || elem->type == ENV || elem->type == WORD))
		{
			last->argv[j] = elem->content;
			spaces = 0;
			j++;
			n = 1;
		}
		if (elem->type == ENV)
		{
			last->env = 1;
			spaces = 0;
			n = 1;
		}
		if (elem->type == PIPE_LINE)
		{
			last->pipe = 1;
			boolien = 0;
			redir = 0;
			echo = 0;
			spaces = 0;
			j = 0;
			i = 0;
			prev_is_redir = 0;
			n = 1;
		}
		if (elem->type == DOUBLE_QUOTE || elem->type == QOUTE)
			spaces = 0;
		elem = elem->next;
	}
}
int ft_count_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
int env_len(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	return (i);
}
char **env_copy(char **envp)
{
	char **envs;
	int size;
	int i;
	int j;
	int l;

	i = 0;
	j = 0;
	l = 0;
	size = 0;
	size = ft_count_env(envp);
	envs = (char **)malloc(sizeof(char *) * ((size * 2) + 1));
	if (envs == NULL)
		exit(1);
	while (envp[j])
	{
		l = env_len(envp[j]);
		envs[i] = ft_substr(envp[j], 0, env_len(envp[j]));
		i++;
		envs[i] = ft_substr(envp[j], l + 1, ft_strlen(envp[j] + l + 1));
		i++;
		j++;
	}
	envs[i] = NULL;
	return (envs);
}

void ft_tokenizing(char *line, t_cmd **cmd, t_table *table, pid_t pid)
{
	t_elem *elem;
	t_elem *last;
	int Q = 0;
	int DQ = 0;
	int closedQ = 0;
	char **env;
	int i = 0;
	int l = 0;
	env = env_copy(table->env);
	while (line[i])
	{
		if (line[i] == '"' && (i == 0 || line[i - 1] != '\\') && DQ == 0 &&
				Q == 0)
			(1) && (DQ = 1, closedQ = 1);
		else if (line[i] == '\"' && DQ == 1)
			(1) && (DQ = 0, closedQ = 0);
		else if (line[i] == '\'' && (i == 0 || line[i - 1] != '\\') && Q == 0
				&& DQ == 0)
			(1) && (Q = 1, closedQ = 2);
		else if (line[i] == '\'' && Q == 1)
			(1) && (Q = 0, closedQ = 0);
		if (i == l)
		{
			l += ft_listing(line + i, &elem);
			last = ft_lstlast(elem);
			if (last)
			{
				last->pid = pid;
				if (closedQ == 1 && last->content[0] != '"')
					last->state = 0;
				else if (closedQ == 2 && last->content[0] != '\'')
					last->state = 1;
				else
					last->state = 2;
			}
		}
		i++;
	}
	ft_token(elem);
	ft_printlist(elem, *cmd);
	if (ft_chek(elem))
	{
		printf("syntax error\n");
		return;
	}
	ft_cmd(cmd, elem, env, table->exit_status);
	// printf("''%p''\n", (*cmd)->redir);
	// ft_printlist(elem, *cmd);
}