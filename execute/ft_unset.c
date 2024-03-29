/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:53:19 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/19 23:47:17 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_err(t_table *table, char **the_last, char *err_join, int f)
{
	ft_putstr_fd(err_join, 2);
	ft_putstr_fd(the_last[f - 1], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	table->exit_status = 1;
}

void	for_unset(t_cmd *cmd, t_table *table)
{
	int		d;
	char	**the_last;
	char	*err_join;
	int		f;
	int		flag;

	f = 0;
	flag = 0;
	d = 0;
	the_last = (char **)malloc(sizeof(char *) * 1000);
	err_join = ft_strdup("unset: `");
	while (cmd->argv[++d])
	{
		if (ft_strchr(cmd->argv[d], '=') != NULL)
		{
			the_last[f] = ft_strdup(cmd->argv[d]);
			flag = 1;
			f++;
		}
	}
	the_last[f] = NULL;
	if (flag == 1)
		put_err(table, the_last, err_join, f);
}

void	for_unset_2(t_cmd *cmd, t_table *table, int i, int j)
{
	char	**new_declare_x;
	int		len;

	len = ft_strlen_2d(table->declare_x) + 1;
	new_declare_x = (char **)malloc(sizeof(char *) * len);
	len = 0;
	while (cmd->argv[++len])
	{
		i = -1;
		j = 0;
		if (ft_strchr(cmd->argv[len], '=') != NULL)
			continue ;
		cmd->argv[len] = ft_strjoin("declare -x ", cmd->argv[len]);
		while (table->declare_x[++i])
		{
			if (ft_strncmp(table->declare_x[i], cmd->argv[len],
					ft_strlen(cmd->argv[len])) != 0)
				new_declare_x[j++] = ft_strdup(table->declare_x[i]);
		}
		new_declare_x[j] = NULL;
		table->declare_x = copy_the_env(new_declare_x);
	}
}

void	inside_loop(t_cmd *cmd, t_table *table, int i, int j)
{
	char	**new_env;
	int		len;

	new_env = (char **)malloc(sizeof(char *) * (ft_strlen_2d(table->env) + 1));
	len = 0;
	while (cmd->argv[++len])
	{
		i = 0;
		j = 0;
		if (ft_strchr(cmd->argv[len], '=') != NULL)
			continue ;
		while (table->env[i])
		{
			if (ft_strncmp(table->env[i], cmd->argv[len],
					ft_strlen(cmd->argv[len])) != 0)
			{
				new_env[j] = ft_strdup(table->env[i]);
				j++;
			}
			i++;
		}
		new_env[j] = NULL;
		table->env = copy_the_env(new_env);
	}
}

// function unset
void	ft_unset(t_cmd *cmd, t_table *table)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = (char **)malloc(sizeof(char *) * (ft_strlen_2d(table->env) + 1));
	for_unset(cmd, table);
	inside_loop(cmd, table, i, j);
	for_unset_2(cmd, table, i, j);
}
