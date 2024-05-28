/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:09:13 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/25 00:26:53 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	condition_1(t_table *table, t_cmd *cmd, char **path)
{
	if (cmd->table->exit_s == 1)
	{
		table->condition = 1;
		return ;
	}
	if (search_for_home(table) == -1)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		exit_state_in_child(cmd, table, 1);
		table->condition = 1;
		return ;
	}
	if (cmd->argv[1] == NULL || cmd->argv[1][0] == '\0')
	{
		ft_putstr_fd("Realtive Path Or Absolute Need\n", 2);
		exit_state_in_child(cmd, table, 1);
		table->condition = 1;
		return ;
	}
	if (ft_strcmp(cmd->argv[1], "~") == 1)
		*path = get_env_pro("HOME", table);
	else
		*path = ft_strdup(cmd->argv[1]);
}

void	condtion_inside(char **tmp, t_table *table, char *path, t_cmd *cmd)
{
	if (*tmp == NULL)
	{
		putstr_pro("cd: no such file or directory: ", path);
		exit_state_in_child(cmd, table, 1);
		table->gar = 1;
		free(*tmp);
		return ;
	}
	free(*tmp);
	table->gar = 0;
	change_pwd(table);
}

void	ft_cd(t_cmd *cmd, t_table *table)
{
	char	*path;
	char	*tmp;

	table->condition = 0;
	(1) && (path = NULL, tmp = NULL);
	condition_1(table, cmd, &path);
	if (!table->condition)
	{
		if (access(path, F_OK) == -1)
		{
			put_and_exit(table, cmd, path, 1);
			return (free(path));
		}
		else
		{
			if (chdir(path) == -1)
			{
				put_and_exit(table, cmd, path, 0);
				return (free(path));
			}
		}
		tmp = getcwd(NULL, 0);
		condtion_inside(&tmp, table, path, cmd);
	}
	free(path);
}

void	for_env(t_table *table, int *signe)
{
	int	i;

	i = -1;
	if (table->red == 1)
	{
		while (table->env[++i])
		{
			if (ft_strncmp(table->env[i], "PATH=", 5) != 0
				&& ft_strncmp(table->env[i], "SHELL=", 5) != 0)
				print_with_fd(table->env[i], 1);
		}
		*signe = -1;
		return ;
	}
}

void	ft_env(t_table *table, t_cmd *cmd)
{
	int		i;
	int		fd;
	char	**splited;

	(1) && (i = -1, fd = 0);
	for_env(table, &fd);
	if (fd == -1)
		return ;
	if ((search_for_path(table) != -1))
	{
		splited = ft_split(table->env[search_for_path(table)] + 5, ':');
		while (splited[++i])
		{
			if (ft_strncmp(splited[i], "/usr/bin", 8) == 0)
				fd = 1;
		}
	}
	if ((search_for_path(table) == -1 || fd == 0))
	{
		ft_putstr_fd("msh: env: No such file or directory\n", 2);
		exit_state_in_child(cmd, table, 127);
		return ;
	}
	free_2d(splited);
	ft_putstr2d_fd(table->env, 1);
}
