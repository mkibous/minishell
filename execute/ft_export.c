/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:42:02 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/13 02:34:57 by aitaouss         ###   ########.fr       */
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

static int	ft_strlen_until_equals(char *str)
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
	len = ft_strlen_until_equals(str);
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

int	check_if_exist_2(char *str, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen_until_equals(str);
	len++;
	char **split;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strncmp(split[0], str, len) == 0)
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

char	**join_2ds(char **join, char **to_join)
{
	int i;
	int j;
	char **tmp;

	i = 0;
	j = 0;
	tmp = (char **)malloc(sizeof(char *) * (ft_strlen_2d(join) + ft_strlen_2d(to_join) + 1));
	while (join[i])
	{
		tmp[i] = join[i];
		i++;
	}
	while (to_join[j])
	{
		tmp[i] = to_join[j];
		i++;
		j++;
	}
	tmp[i] = NULL;
	return (tmp);
}

int	check_if_the_cmd_is_in_argv(char *str, char **argv, int k)
{
	k += 1;
	while (argv[k])
	{
		if (ft_strncmp(str, argv[k], ft_strlen(str)) == 0)
			return (k);
		k++;
	}
	return (0);
}

int	check_if_the_real_one(char *str, char **real_one)
{
	int i;

	i = 0;
	while (real_one[i])
	{
		if (ft_strncmp(str, real_one[i], ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_export(t_cmd *cmd, t_table *table)
{
	int		i;
	int		check;
    int     flag;
	char	**new_env;

	check = 0;
	i = 1;
    flag = 0;
	if (cmd->argv[1] == NULL)
	{
		ft_putstr_2d_fd(table->declare_x, 1);
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (ft_strlen_2d_stat(cmd->argv) > 2)
		new_env = (char **)malloc(sizeof(char *) * (ft_strlen_2d_stat(table->env) + ft_strlen_2d_stat(cmd->argv)));
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] == '=' || !ft_isalpha(cmd->argv[i][0]))
		{
			ft_putstr_fd("export : not a valid identifier\n", 2);
			table->exit_status = 1;
			return ;
		}
		if (ft_strchr(cmd->argv[i], '='))
		{
			check = check_if_exist(cmd->argv[i], table->env);
			if (check != -1)
			{
				table->env[check] = ft_strdup(cmd->argv[i]);
				check = 0;
			}
			else
			{
				new_env = ft_add_env2(table->env, cmd->argv[i]);
				table->env = new_env;
			}
		}
		i++;
	}

	if (ft_strlen_2d_stat(cmd->argv) > 2)
		new_env = (char **)malloc(sizeof(char *) * (ft_strlen_2d_stat(table->env) + ft_strlen_2d_stat(cmd->argv)));
	i = 0;
	char **split;
	char	*to_join;
	char	*tmp_argv;
	to_join = ft_strdup("declare -x ");
	while (cmd->argv[++i])
	{
		if (cmd->argv[i][0] == '=' || !ft_isalpha(cmd->argv[i][0]))
		{
			ft_putstr_fd("export : not a valid identifier\n", 2);
			table->exit_status = 1;
			return ;
		}
		split = ft_split(cmd->argv[i], '=');
		split[0] = ft_strjoin("declare -x ", split[0]);
		check = check_if_exist_2(split[0], table->declare_x);
		if (check != -1)
		{
			if (ft_strchr(cmd->argv[i], '=') != 0)
			{
				tmp_argv = ft_strjoin(to_join, cmd->argv[i]);
				table->declare_x[check] = ft_strdup(tmp_argv);
			}
		}
		else
		{
			tmp_argv = ft_strjoin(to_join, cmd->argv[i]);
			new_env = ft_add_env2(table->declare_x, tmp_argv);
			table->declare_x = new_env;
		}
	}
}
