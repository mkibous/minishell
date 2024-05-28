/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:11:23 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/28 14:35:56 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr2d_fd(char **str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		if (str[i + 1] != NULL)
			ft_putstr_fd("\n", fd);
		i++;
	}
	if (i != 0)
		ft_putstr_fd("\n", fd);
}

int	len_a_eq(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	return (i);
}

int	ft_is_integer(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	utils_for_exit(t_table *table, t_cmd *cmd, int flag)
{
	table->exit_s = ft_atoi(cmd->argv[1], &flag);
	if (flag)
	{
		table->exit_s = 255;
		if (!cmd->pipe)
			ft_putstr_fd("exit\n", 2);
		if (ft_atol(cmd->argv[1]) < 9223372036854775807)
		{
			ft_putstr_fd("msh: exit: ", 2);
			ft_putstr_fd(cmd->argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
		}
		exit(255);
	}
	if (!cmd->pipe)
		ft_putstr_fd("exit\n", 2);
	exit(table->exit_s);
}

void	ft_exit(t_cmd *cmd, t_table *table)
{
	int	flag;

	flag = 0;
	if (cmd->argv[1] == NULL && !cmd->pipe)
	{
		ft_putstr_fd("exit\n", 2);
		exit(table->exit_s);
	}
	if (!ft_is_integer(cmd->argv[1]))
	{
		ft_putstr_fd("exit\nmsh: exit: ", 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		table->exit_s = 255;
		exit(255);
	}
	else if (ft_strlen_2d(cmd->argv) > 2)
	{
		if (!cmd->pipe)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("msh: exit: too many arguments\n", 2);
		table->exit_s = 1;
		exit_help(cmd);
	}
	else if (ft_is_integer(cmd->argv[1]))
		utils_for_exit(table, cmd, flag);
}
