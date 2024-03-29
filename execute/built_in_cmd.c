/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:11:23 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/21 01:34:28 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// function putstr2d_fd
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
}

// ft_strlen 2d
int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strlen_until_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	return (i);
}

// function check if the str is integer or nor include '-' and '+'
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

// function exit with all the protection
void	ft_exit(t_cmd *cmd, t_table *table)
{
	if (cmd->argv[1] == NULL)
	{
		ft_putstr_fd("exit\n", 2);
		exit(table->exit_status);
	}
	if (!ft_is_integer(cmd->argv[1]))
	{
		ft_putstr_fd("exit\nmsh: exit: ", 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		table->exit_status = 255;
		exit(255);
	}
	else if (ft_strlen_2d(cmd->argv) > 2)
	{
		ft_putstr_fd("exit\nmsh: exit: too many arguments\n", 2);
		table->exit_status = 1;
		if (cmd->pipe)
			exit(1);
	}
	else if (ft_is_integer(cmd->argv[1]))
	{
		table->exit_status = ft_atoi(cmd->argv[1]);
		ft_putstr_fd("exit\n", 2);
		exit(table->exit_status);
	}
}
