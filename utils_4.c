/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:50:10 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/28 14:48:35 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	else_condition(int flag, t_cmd *cmd, char **tmp, char **tmp_3)
{
	if (flag)
	{
		cmd->table->env = ft_add_env2(cmd->table->env, *tmp);
		free(*tmp);
		free(*tmp_3);
	}
	if (flag == 2)
	{
		cmd->table->declare_x
			= ft_add_env2(cmd->table->declare_x, *tmp);
		free(*tmp);
		free(*tmp_3);
	}
}

void	utils_plus(t_cmd *cmd, char *tmp, char *tmp_2, char *tmp_3)
{
	char	*leak;

	if (cmd->table->check != -1)
	{
		cmd->table->s = 0;
		tmp_2 = copy_the_str(cmd->table->env[cmd->table->check],
				&cmd->table->s, 0);
		leak = ft_strdup(tmp_2);
		free(tmp_2);
		tmp_2 = ft_strjoin(leak, tmp_3);
		free(leak);
		leak = ft_strdup(tmp);
		free(tmp);
		tmp = get_the_argv_before_equal(leak);
		free(leak);
		leak = ft_strdup(tmp);
		free(tmp);
		tmp = ft_strjoin(leak, tmp_2);
		(1) && (free(leak), free(tmp_2), cmd->table->s = 0);
		free(cmd->table->env[cmd->table->check]);
		cmd->table->env[cmd->table->check] = ft_strdup(tmp);
		(1) && (free(tmp), free(tmp_3), cmd->table->s = 0);
	}
	else
		else_condition(1, cmd, &tmp, &tmp_3);
}

void	utils_plus_declare_x(t_cmd *cmd, char *tmp, char *tmp_2, char *tmp_3)
{
	char	*leak;

	if (cmd->table->check != -1)
	{
		tmp_2 = copy_s_after_eq(cmd->table->declare_x[cmd->table->check]);
		leak = ft_strdup(tmp_2);
		free(tmp_2);
		tmp_2 = ft_strjoin(leak, tmp_3);
		(1) && (free(leak), leak = ft_strdup(tmp), free(tmp), cmd->a = 0);
		tmp = get_the_argv_before_equal(leak);
		free(leak);
		leak = ft_strdup(tmp);
		free(tmp);
		tmp = ft_strjoin(leak, tmp_2);
		(1) && (free(leak), free(tmp_2), cmd->table->s = 0);
		free(cmd->table->declare_x[cmd->table->check]);
		cmd->table->declare_x[cmd->table->check] = ft_strdup(tmp);
		(1) && (free(tmp), free(tmp_3), cmd->table->s = 0);
	}
	else
	{
		cmd->table->declare_x
			= ft_add_env2(cmd->table->declare_x, tmp);
		(1) && (free(tmp), free(tmp_3), cmd->table->s = 0);
	}
}

char	*copy_the_str_without_plus(char *str)
{
	char	*tmp;
	int		i;
	int		s;
	int		flag;

	flag = 0;
	s = 0;
	i = -1;
	tmp = (char *)malloc(sizeof(char) * 255);
	if (!tmp)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '+' && flag == 0)
		{
			i++;
			flag = 1;
		}
		tmp[s] = str[i];
		s++;
	}
	tmp[s] = '\0';
	return (tmp);
}

char	**loop_unset(t_table *table, char **new_env, int len, int j)
{
	int	i;

	i = -1;
	while (table->env[++i])
	{
		if (ft_strncmp(table->env[i], table->cmd->argv[len],
				ft_strlen(table->cmd->argv[len])) == 0
			&& (len_a_eq(table->env[i])
				== (int)ft_strlen(table->cmd->argv[len])))
			continue ;
		else
			(1) && (new_env[j] = ft_strdup(table->env[i]), j++);
	}
	new_env[j] = NULL;
	return (new_env);
}
