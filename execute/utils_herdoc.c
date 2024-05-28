/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:05:41 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/27 23:00:15 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_put_env(char **line, t_cmd *cmd)
{
	int		i;
	char	**env;

	i = 0;
	cmd->table->l = 0;
	if (cmd->state != GENERAL || ft_strchr(*line, '$') == NULL)
		return ;
	env = env_copy(cmd->table->env);
	for_put_env(line, cmd, env, i);
}

int	search_for_home(t_table *table)
{
	int	i;

	i = 0;
	while (table->env[i])
	{
		if (ft_strncmp(table->env[i], "HOME=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	condition_flag_herdoc(t_cmd *cmd, int k, int **fd)
{
	if (cmd->in == 0)
	{
		if (cmd->prev)
			cmd->in = fd[k - 1][0];
	}
}

long	ft_atol(char *str)
{
	int		i;
	long	nbr;
	int		s;

	i = 0;
	nbr = 0;
	s = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		nbr = (nbr * 10) + (str[i] - 48);
		i++;
	}
	return (nbr * s);
}
