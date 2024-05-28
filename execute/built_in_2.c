/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:27:59 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/16 10:39:30 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->table->exit_s == 1)
		return ;
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		i++;
		cmd->table->exit_s = 0;
	}
	if (cmd->echo_new_line == 0)
		ft_putstr_fd("\n", 1);
}

void	for_change_pwd(t_table *table, char **tmp2, char **oldpwd)
{
	int		i;

	i = -1;
	if (!table->flag_old)
	{
		table->flag_old = 1;
		table->env = ft_add_env2(table->env, "OLDPWD=");
	}
	while (table->env[++i])
	{
		if (ft_strncmp(table->env[i], "PWD=", 4) == 0)
		{
			*tmp2 = getcwd(NULL, 0);
			free(table->env[i]);
			table->env[i] = ft_strjoin("PWD=", *tmp2);
			free(*tmp2);
		}
		if (ft_strncmp(table->env[i], "OLDPWD=", 7) == 0)
		{
			free(table->env[i]);
			(1) && (*oldpwd = ft_strdup(table->pwd_env),
				table->env[i] = ft_strjoin("OLDPWD=", *oldpwd));
			free(*oldpwd);
		}
	}
}

void	loop_pwd(t_table *table, char **tmp, char **tmp2, char **tmp3)
{
	int	i;

	i = 0;
	while (table->declare_x[i])
	{
		if (ft_strncmp(table->declare_x[i], "declare -x PWD=", 15) == 0)
		{
			*tmp = ft_strdup(table->declare_x[i]);
			*tmp2 = getcwd(NULL, 0);
			*tmp3 = table->declare_x[i];
			table->declare_x[i] = ft_strjoin("declare -x PWD=", *tmp2);
			free(*tmp3);
			free(*tmp2);
			free(*tmp);
		}
		if (ft_strncmp(table->declare_x[i], "declare -x OLDPWD", 17) == 0)
		{
			*tmp3 = table->declare_x[i];
			table->declare_x[i]
				= ft_strjoin("declare -x OLDPWD=", table->pwd_env);
			free(*tmp3);
		}
		i++;
	}
}

void	change_pwd(t_table *table)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*oldpwd;
	char	*tmp3;

	i = 0;
	for_change_pwd(table, &tmp, &oldpwd);
	loop_pwd(table, &tmp, &tmp2, &tmp3);
	i = 0;
	tmp3 = table->pwd_env;
	table->pwd_env = getcwd(NULL, 0);
	free(tmp3);
}

char	*get_env_pro(char *str, t_table *table)
{
	int		i;
	char	*tmp;

	i = 0;
	while (table->env[i])
	{
		if (ft_strncmp(table->env[i], str, ft_strlen(str)) == 0)
		{
			tmp = ft_strdup(table->env[i] + (ft_strlen(str) + 1));
			return (tmp);
		}
		i++;
	}
	return (NULL);
}
