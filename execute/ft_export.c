/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:42:02 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/19 02:50:31 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**utils_declare_x(t_cmd *cmd, t_table *table, int i)
{
	int		check;
	char	*tmp_argv;
	char	**new_env;
	char	**split;

	split = ft_split(cmd->argv[i], '=');
	split[0] = ft_strjoin("declare -x ", split[0]);
	check = check_if_exist(split[0], table->declare_x, 2);
	if (check != -1)
	{
		if (ft_strchr(cmd->argv[i], '=') != 0)
		{
			tmp_argv = ft_strjoin("declare -x ", cmd->argv[i]);
			table->declare_x[check] = ft_strdup(tmp_argv);
		}
	}
	else
	{
		tmp_argv = ft_strjoin("declare -x ", cmd->argv[i]);
		new_env = ft_add_env2(table->declare_x, tmp_argv);
		table->declare_x = new_env;
	}
	return (table->declare_x);
}

void	export_declare_x(t_table *table, t_cmd *cmd)
{
	int		i;
	char	**new_env;

	if (ft_strlen_2d(cmd->argv) > 2)
		new_env = (char **)malloc(sizeof(char *)
				* (ft_strlen_2d(table->env) + ft_strlen_2d(cmd->argv)));
	i = 0;
	while (cmd->argv[++i])
	{
		if (cmd->argv[i][0] == '=' || !ft_isalpha(cmd->argv[i][0]))
		{
			ft_putstr_fd("export : not a valid identifier\n", 2);
			table->exit_status = 1;
			return ;
		}
		table->declare_x = utils_declare_x(cmd, table, i);
	}
}

void	after_export(t_cmd *cmd, t_table *table, int check)
{
	int		i;

	i = 0;
	while (cmd->argv[++i])
	{
		if (cmd->argv[i][0] == '=' || !ft_isalpha(cmd->argv[i][0]))
		{
			ft_putstr_fd("export : not a valid identifier\n", 2);
			table->exit_status = 1;
			return ;
		}
		if (ft_strchr(cmd->argv[i], '='))
		{
			check = check_if_exist(cmd->argv[i], table->env, 1);
			if (check != -1)
			{
				table->env[check] = ft_strdup(cmd->argv[i]);
				check = 0;
			}
			else
				table->env = ft_add_env2(table->env, cmd->argv[i]);
		}
	}
}

void	ft_export(t_cmd *cmd, t_table *table)
{
	int		i;
	int		check;
	int		flag;

	check = 0;
	i = 1;
	flag = 0;
	if (cmd->argv[1] == NULL)
	{
		ft_putstr2d_fd(table->declare_x, 1);
		ft_putstr_fd("\n", 1);
		return ;
	}
	after_export(cmd, table, check);
	export_declare_x(table, cmd);
}
