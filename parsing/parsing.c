/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:44:32 by mkibous           #+#    #+#             */
/*   Updated: 2024/03/29 23:21:29 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	len(char *str)
{
	int	i;
	int	env;

	(1) && (i = 0, env = 0);
	if (str[i] == '\\' && str[i + 1] && str[i + 1] == '\'')
		return (1);
	else if (str[i] && str[i + 1] && (str[i] == '\\' || (str[i] == '>'
				&& str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')))
		i = 2;
	else
	{
		(str[i] == '$') && (env = 1, i++);
		while (str[i])
		{
			if (env && str[i - 1] == '$' && (str[i] == '$' || str[i] == '?'
				|| ft_isdigit(str[i])))
				return (2);
			if (!ft_isalnum(str[i]) && i == 0)
				return (1);
			else if (!ft_isalnum(str[i]) && (!env || (env && str[i] != '_')))
				break ;
			i++;
		}
	}
	return (i);
}

int	ft_count_argv(t_elem *elem, int *redirs)
{
	t_vars	vars;

	ft_memset(&vars, 0, sizeof(vars));
	while (elem && elem->type != PIPE_LINE)
	{
		if (vars.n == 0 && vars.echo == 1 && !ft_comp_n(elem->content, elem))
			(1) && (vars.spaces = 1, vars.n = 1);
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

void	get_cmd(t_elem *elem, t_vars *vars, t_cmd **cmd)
{
	if ((elem->type == WORD) && vars->boolien == 0 && vars->redir == 0)
	{
		if (ft_strncmp(elem->content, "echo", 5) == 0)
			(1) && (vars->spaces = 1, vars->echo = 1);
		else
			(1) && (vars->echo = 0, vars->spaces = 0);
		vars->size = ft_count_argv(elem, &vars->rdrs);
		if (vars->prev_is_redir == 0)
		{
			ft_lstadd_back_cmd(cmd, ft_lstnew_cmd(ft_strdup(elem->content)));
			vars->l_cmd = ft_lstlast_cmd(*cmd);
		}
		else
			vars->l_cmd->cmd = elem->content;
		vars->l_cmd = ft_lstlast_cmd(*cmd);
		(*cmd)->count_cmd++;
		vars->l_cmd->argv = (char **)malloc(sizeof(char *) * (vars->size + 1));
		if (vars->l_cmd->argv == NULL)
			exit(1);
		vars->l_cmd->argv[vars->size] = NULL;
		if (vars->l_cmd->prev && vars->l_cmd->prev->pipe == 1)
			vars->l_cmd->pipe = 1;
		(1) && (vars->boolien = 1, vars->prev_is_redir = 0, vars->rdrs = 0);
		printf("size : %d\n", vars->size);
	}
}

void	ft_cmd(t_cmd **cmd, t_elem *elem, char **env, int last_exit)
{
	t_vars	vars;

	ft_memset(&vars, 0, (sizeof(vars)));
	ft_envr(elem, env, last_exit);
	ft_join(elem);
	while (elem)
	{
		if(elem->content[0] == '\0' && elem->state == GENERAL && !vars.redir)
		{
			elem = elem->next;
		}
		if(!elem)
			break;
		if (vars.n == 0 && vars.echo == 1 && !ft_comp_n(elem->content, elem))
			(1) && (vars.l_cmd->echo_new_line = 1, vars.spaces = 1, vars.n = 1);
		else
		{
			get_cmd(elem, &vars, cmd);
			echo_spaces(&vars, elem);
			fill_redir_file(elem, &vars, cmd);
		}
		if (elem->type == PIPE_LINE)
			(1) && (vars.l_cmd->pipe = 1, ft_memset(&vars, 0, (sizeof(vars))));
		elem = elem->next;
	}
}

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
        printf("%s| p%d e-n%d \n", cmd->cmd, cmd->pipe, cmd->echo_new_line);
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

void	ft_parsing(char *line, t_cmd **cmd, t_table *table, pid_t pid)
{
	t_elem	*elem;
	char	**env;
	t_vars	vars;
	t_cmd	*tmp;

	ft_memset(&vars, 0, sizeof(vars));
	ft_memset(&elem, 0, sizeof(elem));
	env = env_copy(table->env);
	while (line[vars.i])
	{
		ft_state(line, &vars, &elem, pid);
		vars.i++;
	}
	ft_token(elem);
	if (ft_chek(elem))
	{
		ft_free(env);
		table->exit_status = 258;
		printf("syntax error\n");
		return ;
	}
	ft_cmd(cmd, elem, env, table->exit_status);
	ft_printlist(elem, *cmd);
	tmp = *cmd;
	while(tmp)
	{
		tmp->table = table;
		tmp->elem = elem;
		tmp = tmp->next;
	}
	ft_free(env);
}
