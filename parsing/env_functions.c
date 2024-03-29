/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:44:32 by mkibous           #+#    #+#             */
/*   Updated: 2024/03/29 22:53:05 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*put_env(t_elem *elem, char **env, int last_exit)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!ft_strncmp(elem->content, "$$", 3))
		return (ft_itoa((int)elem->pid));
	if (!ft_strncmp(elem->content, "$?", 3))
		return (ft_itoa(last_exit));
	while (env[i])
	{
		if (ft_strlen(env[i]) > ft_strlen(elem->content))
			len = ft_strlen(env[i]);
		else
			len = ft_strlen(elem->content);
		if (i % 2 == 0 && i != 1 && strncmp(elem->content + 1, env[i], len) == 0)
		{
			i++;
			return (strdup(env[i]));
		}
		i++;
	}
		return (strdup(""));
}

void	ft_envr(t_elem *elem, char **env, int last_exit)
{
	int	i;
	int redir;
	char	*tmp;

	i = 0;
	redir = 0;
	while (elem)
	{
		if (elem->type == REDIR_IN || elem->type == REDIR_OUT
			|| elem->type == HERE_DOC || elem->type == DREDIR_OUT)
			redir = 1;
		if (elem->type == ENV)
		{
			elem->type = WORD;
			tmp = put_env(elem, env, last_exit);
			free(elem->content);
			elem->content = strdup(tmp);
			free(tmp);
		}
		if (elem->type == NEW_LINE)
		{
			elem->type = WORD;
			free(elem->content);
			elem->content = strdup("\\n");
		}
		if (elem->content[0] == '\\' && elem->type == WORD
			&& elem->state == GENERAL)
		{
			tmp = ft_strdup(&elem->content[1]);
			free(elem->content);
			elem->content = ft_strdup(tmp);
			free(tmp);
		}
			
		else if (elem->type == ESCAPE)
		{
			elem->type = WORD;
			tmp = ft_get_escape(elem->content[1], elem->state);
			free(elem->content);
			elem->content = strdup(tmp);
			free(tmp);
		}
		if (elem->type == WORD && redir == 1)
			redir = 0;
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

int	env_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
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
