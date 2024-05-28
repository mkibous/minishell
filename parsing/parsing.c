/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:44:32 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/28 14:32:01 by aitaouss         ###   ########.fr       */
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

void	get_cmd(t_elem *elem, t_vars *vars, t_cmd **cmd)
{
	if ((elem->type == WORD) && vars->boolien == 0 && vars->redir == 0)
	{
		if (ft_strncmp(elem->content, "echo", 5) == 0)
			(1) && (vars->spaces = 1, vars->echo = 1);
		else
			(1) && (vars->echo = 0, vars->spaces = 0);
		vars->size = ft_count_argv(elem, &vars->rdrs, 0);
		if (vars->prev_is_redir == 0)
		{
			ft_lstadd_back_cmd(cmd, ft_lstnew_cmd(ft_strdup(elem->content)));
			vars->l_cmd = ft_lstlast_cmd(*cmd);
		}
		else
			vars->l_cmd->cmd = ft_strdup(elem->content);
		vars->l_cmd = ft_lstlast_cmd(*cmd);
		(*cmd)->count_cmd++;
		vars->l_cmd->argv = (char **)malloc(sizeof(char *) * (vars->size + 1));
		if (vars->l_cmd->argv == NULL)
			exit(1);
		vars->l_cmd->argv[vars->size] = NULL;
		if (vars->l_cmd->prev && vars->l_cmd->prev->pipe == 1)
			vars->l_cmd->pipe = 1;
		(1) && (vars->boolien = 1, vars->prev_is_redir = 0);
	}
}

void	ft_fill_cmd(t_cmd **cmd, t_elem *elem, t_vars *vars)
{
	if (vars->echo == 1 && !ft_comp_n(elem->content) && vars->nn == 0)
		(1) && (vars->l_cmd->echo_new_line = 1, vars->spaces = 1, vars->n = 1);
	else
	{
		get_cmd(elem, vars, cmd);
		echo_spaces(vars, elem);
		fill_redir_file(elem, vars, cmd);
	}
	if (vars->echo && !vars->nn && ft_comp_n(elem->content)
		&& elem->type != WHITE_SPACE && vars->j != 1)
		(1) && (vars->nn = 1);
}

void	ft_cmd(t_cmd **cmd, t_elem *elem, t_table *table)
{
	t_vars	vars;
	t_elem	*tmp;

	ft_memset(&vars, 0, (sizeof(vars)));
	tmp = elem;
	ft_join(elem);
	while (elem)
	{
		if (elem->content[0] == '\0' && elem->state == GENERAL && !vars.redir)
			elem = elem->next;
		if (!elem)
		{
			if (!vars.l_cmd)
				table->set_flag = 1;
			break ;
		}
		ft_fill_cmd(cmd, elem, &vars);
		if (elem->type == PIPE_LINE)
		{
			if (vars.l_cmd)
				vars.l_cmd->pipe = 1;
			ft_memset(&vars, 0, (sizeof(vars)));
		}
		elem = elem->next;
	}
}

void	ft_parsing(char *line, t_cmd **cmd, t_table *table)
{
	t_elem	*elem;
	t_vars	vars;
	t_cmd	*tmp;
	char	*str;

	str = ft_strdup(line);
	ft_memset(&vars, 0, sizeof(vars));
	ft_memset(&elem, 0, sizeof(elem));
	while (str[vars.i])
		ft_state(&str, &vars, &elem, table);
	if (ft_chek(elem))
	{
		(1) && (table->exit_s = 258);
		ft_free_elem(&elem);
		(1) && (free(str), printf("syntax error\n"));
		return ;
	}
	ft_cmd(cmd, elem, table);
	tmp = *cmd;
	while (tmp)
		(1) && (tmp->table = table, tmp->elem = elem, tmp = tmp->next);
	if (!(*cmd))
		ft_free_elem(&elem);
	last_arg(*cmd, table);
	free(str);
}
