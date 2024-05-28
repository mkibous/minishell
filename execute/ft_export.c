/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:42:02 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/28 14:35:56 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**utils_declare_x(t_cmd *cmd, t_table *table, int i)
{
	int		c;
	char	*tmp_argv;
	char	**split;

	split = ft_split(cmd->argv[i], '=');
	if (split[0] == NULL)
		return (table->declare_x);
	(1) && (tmp_argv = ft_strdup(split[0]), free(split[0]), c = 0);
	split[0] = ft_strjoin("declare -x ", tmp_argv);
	c = check_if_exist(split[0], table->declare_x, 2);
	free(tmp_argv);
	free_2d(split);
	if (c != -1)
	{
		if (ft_strchr(cmd->argv[i], '=') != 0)
		{
			tmp_argv = ft_strjoin("declare -x ", cmd->argv[i]);
			free(table->declare_x[c]);
			table->declare_x[c] = ft_strdup(tmp_argv);
			free(tmp_argv);
		}
	}
	else
		utils_util_dec(table, &tmp_argv, i, cmd);
	return (table->declare_x);
}

void	export_declare_x(t_table *table, t_cmd *cmd)
{
	int		i;
	int		test;
	int		valid;

	valid = 0;
	test = 0;
	i = 0;
	while (cmd->argv[++i])
	{
		test = is_alpha_num(cmd->argv[i]);
		if (test == -1 && check_if_valid(cmd->argv[i]))
			test = 1;
		if (ft_strncmp(cmd->argv[i], "_=", 2) != 0 && test != -1)
		{
			if (ft_strchr(cmd->argv[i], '+')
				&& check_if_valid(cmd->argv[i]) == 1)
				the_plus_for_declare_x(cmd, i, table);
			else
				table->declare_x = utils_declare_x(cmd, table, i);
		}
	}
}

char	*get_the_argv_before_equal(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != '=')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	the_plus_for_declare_x(t_cmd *cmd, int i, t_table *table)
{
	int		check;
	char	*tmp;
	char	*tmp_2;
	char	*tmp_3;
	char	**split;

	tmp_2 = NULL;
	tmp = ft_strdup(cmd->argv[i]);
	free(cmd->argv[i]);
	cmd->argv[i] = ft_strjoin("declare -x ", tmp);
	free(tmp);
	table->j = len_a_eq(cmd->argv[i]) + 1;
	tmp_3 = copy_the_str(cmd->argv[i], &table->j, 1);
	tmp = copy_the_str_without_plus(cmd->argv[i]);
	split = ft_split(tmp, '=');
	check = check_if_exist(split[0], table->declare_x, 2);
	free_2d(split);
	table->i = i;
	table->check = check;
	utils_plus_declare_x(cmd, tmp, tmp_2, tmp_3);
}

void	the_plus(t_cmd *cmd, int i, t_table *table)
{
	int		check;
	char	*tmp;
	char	*tmp_2;
	char	*tmp_3;

	tmp_2 = NULL;
	table->j = len_a_eq(cmd->argv[i]) + 1;
	tmp_3 = copy_the_str(cmd->argv[i], &table->j, 1);
	tmp = copy_the_str_without_plus(cmd->argv[i]);
	check = check_if_exist(tmp, table->env, 1);
	table->i = i;
	table->check = check;
	utils_plus(cmd, tmp, tmp_2, tmp_3);
}
