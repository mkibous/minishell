/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:57:59 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/24 18:57:32 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_argv(t_elem *elem, int *redirs, int rdr)
{
	t_vars	vars;

	ft_memset(&vars, 0, sizeof(vars));
	while (elem && elem->type != PIPE_LINE)
	{
		if (vars.nn == 0 && vars.echo == 1 && !ft_comp_n(elem->content))
			(1) && (vars.spaces = 1, vars.n = 1);
		else if (vars.echo == 0 && ft_strncmp(elem->content, "echo", 5) == 0)
			(1) && (vars.spaces = 1, vars.size++, vars.echo = 1, vars.j = 1);
		else if (rdr == 1 && (elem->type == REDIR_IN || elem->type == REDIR_OUT
				|| elem->type == HERE_DOC || elem->type == DREDIR_OUT))
			(1) && ((*redirs)++, vars.redir = 1, vars.n = 1);
		else
			ft_count_echo_spaces(&vars, elem);
		if (elem->type == DOUBLE_QUOTE || elem->type == QOUTE)
			vars.spaces = 0;
		if (vars.echo && !vars.nn && ft_comp_n(elem->content)
			&& elem->type != WHITE_SPACE && vars.j != 1)
			(1) && (vars.nn = 1);
		elem = elem->next;
	}
	return (vars.size);
}

void	exit_status(t_table *table, int status)
{
	if (status == 5)
		table->exit_s = 1;
}

void	exit_help(t_cmd *cmd)
{
	if (cmd->pipe)
		exit(1);
}

void	put_and_exit(t_table *table, t_cmd *cmd, char *path, int flag)
{
	if (flag)
	{
		putstr_pro("cd: no such file or directory: ", path);
		exit_state_in_child(cmd, table, 1);
	}
	else
	{
		putstr_pro("cd: permission denied: ", path);
		exit_state_in_child(cmd, table, 1);
	}
}
