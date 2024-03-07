/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:42:02 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/07 20:57:22 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_env(char **env, char *str, int *fd)
{
	int		i;
	
	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], *fd);
		ft_putstr_fd("\n", *fd);
		i++;
	}
	ft_putstr_fd(str, *fd);
	ft_putstr_fd("\n", *fd);
}

char	**ft_add_env2(char **env, char *str)
{
	int		i;
	char	**new_env;
	
	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	return (new_env);
}

static int	ft_strlen_until_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	return (i);
}

int	check_if_exist(char *str, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen_until_equal(str);
	len++;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, len) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

static void ft_putstr_2d_fd(char **str, int fd)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		if (str[i + 1] != NULL)
			ft_putstr_fd("\n", fd);
		i++;
	}
}

static int	ft_strlen_2d_stat(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_export(t_cmd *cmd, t_table *table)
{
	int		i;
	int		fd_ex;
	int		check;
    int     flag;
	char	**new_env;

	check = 0;
	i = 1;
    flag = 0;
	if (ft_strlen_2d_stat(cmd->argv) > 2)
		new_env = (char **)malloc(sizeof(char *) * (ft_strlen_2d_stat(table->env) + ft_strlen_2d_stat(cmd->argv)));
	while (cmd->argv[i])
	{
		fd_ex = open(ft_strjoin(table->alpha, "/export.txt"), O_CREAT | O_RDWR | O_APPEND | O_TRUNC, 0644);
		if (cmd->argv[i][0] == '=' || !ft_isalpha(cmd->argv[i][0]))
		{
			ft_putstr_fd("export : not a valid identifier\n", 2);
			ft_putstr_2d_fd(table->env, fd_ex);
			return ;
		}
		if (ft_strchr(cmd->argv[i], '='))
		{
            flag = 1;
			check = check_if_exist(cmd->argv[i], table->env);
			if (check != -1)
			{
				table->env[check] = ft_strdup(cmd->argv[i]);
				check = 0;
				ft_putstr_2d_fd(table->env, fd_ex);
			}
			else
			{
				ft_add_env(table->env, cmd->argv[i], &fd_ex);
				new_env = ft_add_env2(table->env, cmd->argv[i]);
				table->env = new_env;
			}
		}
		else
		{
			ft_putstr_2d_fd(table->env, fd_ex);
		}
		i++;
	}
	close(fd_ex);
}
