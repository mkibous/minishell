/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:44:32 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/20 18:47:17 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*manual_env(char *content, t_table *table, t_vars *vars)
{
	if (!ft_strncmp(content, "$", 2) && (!vars || (vars && vars->closedq == 0
				&& vars->tmp[0] != '\'' && vars->tmp[0] != '"')))
		return (strdup("$"));
	if (!ft_strncmp(content, "$$", 3))
		return (ft_itoa((int)table->pid));
	if (!ft_strncmp(content, "$?", 3))
		return (ft_itoa(table->exit_s));
	if (!ft_strncmp(content, "$0", 3))
		return (strdup("minishell"));
	if (!ft_strncmp(content, "$_", 3))
		return (strdup(table->last_arg));
	return (NULL);
}

char	*put_env(char *content, char **env, t_table *table, t_vars *vars)
{
	int		i;
	int		len;
	char	*tmp;

	(1) && (i = 0, len = 0);
	tmp = manual_env(content, table, vars);
	if (tmp != NULL)
		return (tmp);
	free(tmp);
	while (env[i])
	{
		if (ft_strlen(env[i]) > ft_strlen(content))
			len = ft_strlen(env[i]);
		else
			len = ft_strlen(content);
		if (i % 2 == 0 && i != 1 && !strncmp(content + 1, env[i], len))
			return (i++, strdup(env[i]));
		i++;
	}
	return (strdup(""));
}

void	ft_escape(t_elem *elem)
{
	char	*tmp;

	while (elem)
	{
		if (elem->content[0] == '\\' && elem->type == WORD
			&& elem->state == GENERAL)
		{
			tmp = ft_strdup(&elem->content[1]);
			free(elem->content);
			elem->content = ft_strdup(tmp);
			free(tmp);
		}
		elem = elem->next;
	}
}

int	ft_count_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**env_copy(char **envp)
{
	char	**envs;
	int		size;
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	l = 0;
	size = 0;
	size = ft_count_env(envp);
	envs = (char **)malloc(sizeof(char *) * ((size * 2) + 1));
	if (envs == NULL)
		return (NULL);
	while (envp[j])
	{
		l = env_len(envp[j]);
		envs[i] = ft_substr(envp[j], 0, env_len(envp[j]));
		i++;
		envs[i] = ft_substr(envp[j], l + 1, ft_strlen(envp[j] + l + 1));
		i++;
		j++;
	}
	envs[i] = NULL;
	return (envs);
}
