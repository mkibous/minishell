/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:53:19 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/28 14:48:00 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	for_unset(t_cmd *cmd, t_table *table)
{
	int		d;
	char	**the_last;
	char	*err_join;
	int		f;
	int		flag;

	(1) && (f = 0, flag = 0, d = 0);
	the_last = (char **)malloc(sizeof(char *) * 1000);
	err_join = ft_strdup("unset: `");
	while (cmd->argv[++d])
	{
		if (ft_strchr(cmd->argv[d], '=') != NULL
			|| check_if_there_is_space(cmd->argv[d]) == -1
			|| is_alpha_num(cmd->argv[d]) == -1)
		{
			the_last[f] = ft_strdup(cmd->argv[d]);
			flag = 1;
			f++;
		}
	}
	the_last[f] = NULL;
	if (flag == 1)
		put_err(table, the_last, err_join, f);
	free(err_join);
	free_2d(the_last);
}

void	for_unset_3(char **new_declare_x, t_table *table, int j)
{
	new_declare_x[j] = NULL;
	free_2d(table->declare_x);
	table->declare_x = copy_the_env(new_declare_x);
	free_2d(new_declare_x);
}

void	for_unset_2(t_cmd *cmd, t_table *table, int i, int j)
{
	char	**new_declare_x;
	int		len;
	char	*tmp;
	int		lena;

	(1) && (lena = ft_strlen_2d(table->declare_x) + 1, len = 0);
	while (cmd->argv[++len])
	{
		new_declare_x = (char **)malloc(sizeof(char *) * lena);
		if (ft_strchr(cmd->argv[len], '=') != NULL)
		{
			free(new_declare_x);
			continue ;
		}
		(1) && (tmp = ft_strdup(cmd->argv[len]), free(cmd->argv[len]), i = -1);
		(1) && (cmd->argv[len] = ft_strjoin("declare -x ", tmp),
			free(tmp), j = 0);
		while (table->declare_x[++i])
		{
			if (ft_strncmp(table->declare_x[i], cmd->argv[len],
					ft_strlen(cmd->argv[len])) != 0)
				new_declare_x[j++] = ft_strdup(table->declare_x[i]);
		}
		for_unset_3(new_declare_x, table, j);
	}
}

void	inside_loop(t_cmd *cmd, t_table *table, int i, int j)
{
	char	**new_env;
	int		len;

	len = 0;
	while (cmd->argv[++len])
	{
		new_env = (char **)malloc(sizeof(char *)
				* (ft_strlen_2d(table->env) + 1));
		(1) && (i = -1, j = 0);
		if (ft_strchr(cmd->argv[len], '=') != NULL
			|| ft_strncmp(cmd->argv[len], "_", 2) == 0)
		{
			free(new_env);
			continue ;
		}
		new_env = loop_unset(table, new_env, len, j);
		(1) && (free_2d(table->env), j = 0);
		table->env = copy_the_env(new_env);
		free_2d(new_env);
	}
}

void	ft_unset(t_cmd *cmd, t_table *table)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	for_unset(cmd, table);
	inside_loop(cmd, table, i, j);
	for_unset_2(cmd, table, i, j);
}
