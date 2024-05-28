/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:57:02 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/28 14:35:56 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_env(char **env, char *str, int *fd)
{
	int	i;

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
		free(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

int	check_if_exist(char *str, char **env, int flag)
{
	int		i;
	int		len;
	char	**split;

	if (str == NULL)
		return (-1);
	(1) && (i = -1, len = len_a_eq(str));
	len++;
	while (env[++i] && flag == 1)
	{
		if (ft_strncmp(env[i], str, len) == 0)
			return (i);
	}
	while (env[i] && flag == 2)
	{
		split = ft_split(env[i], '=');
		if (ft_strncmp(split[0], str, len) == 0)
		{
			free_2d(split);
			return (i);
		}
		free_2d(split);
		i++;
	}
	return (-1);
}

char	**join_2ds(char **join, char **to_join)
{
	int		i;
	int		j;
	char	**tmp;
	int		len;

	len = ft_strlen_2d(join) + ft_strlen_2d(to_join) + 1;
	i = 0;
	j = 0;
	tmp = (char **)malloc(sizeof(char *) * (len + 1));
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

int	check_if_there_is_space(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == ' ')
			return (-1);
		i++;
	}
	return (i);
}
