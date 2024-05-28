/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:30:49 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/28 15:41:44 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_built_in(t_cmd **cmd, t_table *table)
{
	t_cmd	*tmp;

	tmp = *cmd;
	table->count_cmd = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->cmd, "cd") || ft_strcmp(tmp->cmd, "pwd")
			|| ft_strcmp(tmp->cmd, "echo") || ft_strcmp(tmp->cmd, "env")
			|| ft_strcmp(tmp->cmd, "export")
			|| ft_strcmp(tmp->cmd, "unset") || ft_strcmp(tmp->cmd, "exit"))
			tmp->is_builtin = 1;
		table->count_cmd++;
		tmp = tmp->next;
	}
}

char	**the_twode(char **twode)
{
	int		index;
	char	**new_twode;

	index = 0;
	while (twode[index])
		index++;
	new_twode = (char **)malloc(sizeof(char *) * (index + 1));
	if (!new_twode)
		return (NULL);
	index = 0;
	while (twode[index])
	{
		new_twode[index] = ft_strdup(twode[index]);
		index++;
	}
	new_twode[index] = NULL;
	return (new_twode);
}

pid_t	ft_get_pid(void)
{
	pid_t	pid;

	pid = 0;
	pid = fork();
	if (pid < 1)
		exit(0);
	pid--;
	return (pid);
}

void	sort_double_pointer_2(char **array, int size)
{
	int		i;
	char	*temp;
	int		sorted;

	(1) && (sorted = 0, i = 0);
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (i < size - 1)
		{
			if (array[i] && array[i + 1])
			{
				if (array[i][11] > array[i + 1][11])
				{
					temp = array[i];
					array[i] = array[i + 1];
					array[i + 1] = temp;
					sorted = 0;
				}
			}
			i++;
		}
		size--;
	}
}

int	check_access_if(char *command, char **splited)
{
	if (command[0] == '/')
	{
		free_2d(splited);
		return (0);
	}
	return (1);
}
