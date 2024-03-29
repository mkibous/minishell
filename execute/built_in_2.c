/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:27:59 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/29 13:54:45 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmd *cmd, t_table *table)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		i++;
	}
	if (cmd->echo_new_line == 0)
		ft_putstr_fd("\n", 1);
}

// change pwd with protection
void	change_pwd(t_table *table)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*oldpwd;

	i = 0;
	while (table->env[i])
	{
		if (ft_strncmp(table->env[i], "PWD=", 4) == 0)
		{
			tmp = ft_strdup(table->env[i]);
			free(table->env[i]);
			tmp2 = getcwd(NULL, 0);
			table->env[i] = ft_strjoin("PWD=", tmp2);
			free(tmp2);
			free(tmp);
		}
		if (ft_strncmp(table->env[i], "OLDPWD=", 7) == 0)
		{
			oldpwd = table->pwd_env;
			table->env[i] = ft_strjoin("OLDPWD=", oldpwd);
		}
		i++;
	}
	table->pwd_env = getcwd(NULL, 0);
}

// fucntion cd with opendir and readdir
void	ft_cd(t_cmd *cmd, t_table *table)
{
	char	*path;

	if (cmd->argv[1] == NULL || ft_strcmp(cmd->argv[1], "~") == 1)
		path = getenv("HOME");
	else
		path = cmd->argv[1];
	if (ft_strncmp(path, "~", 1) && access(path, F_OK) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		if (chdir(path) == -1)
		{
			ft_putstr_fd("cd: permission denied: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	change_pwd(table);
}

void	loop_for_env(t_table *table)
{
	int	i;

	i = 0;
	while (table->env[i])
	{
		ft_putstr_fd(table->env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void	ft_env(t_table *table)
{
	int		i;
	int		fd;
	char	**splited;

	i = -1;
	fd = 0;
	if (search_for_path(table) != -1)
	{
		splited = ft_split(table->env[search_for_path(table)] + 5, ':');
		while (splited[++i])
		{
			if (ft_strncmp(splited[i], "/usr/bin", 8) == 0)
				fd = 1;
		}
	}
	if (search_for_path(table) == -1 || fd == 0)
	{
		ft_putstr_fd("msh: env: No such file or directory\n", 2);
		table->exit_status = 127;
		return ;
	}
	loop_for_env(table);
}
