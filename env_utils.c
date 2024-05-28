/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:27:47 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/16 15:33:00 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop_alloc_env(char **env, int i, char **new_env, int *j)
{
	char	*tmp;
	char	*tmp2;

	while (env[i])
	{
		if (ft_strncmp(env[i], "_=", 2) != 0)
		{
			tmp2 = ft_strdup(env[i]);
			tmp = ft_strjoin("declare -x ", tmp2);
			if (!tmp)
				return (free(tmp2), -1);
			free(tmp2);
			new_env[*j] = ft_strdup(tmp);
			free(tmp);
			(*j)++;
		}
		i++;
	}
	return (0);
}

char	**alloc_env(char **env)
{
	int		i;
	char	**new_env;
	int		j;

	(1) && (j = 0, i = 0);
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * 255);
	if (!new_env)
		return (NULL);
	i = 0;
	if (loop_alloc_env(env, i, new_env, &j) == -1)
		return (free(new_env), NULL);
	new_env[j] = ft_strdup("declare -x OLDPWD");
	new_env[j + 1] = NULL;
	return (new_env);
}

char	**remove_old_pwd(char **env)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;

	(1) && (i = 0, j = 0, len = 0);
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			len++;
		i++;
	}
	new_env = (char **)malloc(sizeof(char *) * (i - len + 1));
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) != 0)
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

void	if_null(t_table *table)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	table->env[0] = ft_strjoin("PWD=", tmp);
	free(tmp);
	table->env[1] = ft_strdup("SHLVL=1");
	table->env[2] = ft_strdup("_=/usr/bin/env");
	table->env[3] = ft_strdup("PATH=/Users/aitaouss/.brew/bin:"
			"/usr/local/bin:/usr/bin:/bin"
			":/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin");
	table->env[4] = ft_strdup("SHELL=/bin/msh");
	table->env[5] = NULL;
	table->red = 1;
}

char	**ft_strdup_2d(char **str)
{
	int		i;
	char	**new_str;

	i = 0;
	while (str[i])
		i++;
	new_str = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = ft_strdup(str[i]);
		i++;
	}
	new_str[i] = NULL;
	return (new_str);
}
