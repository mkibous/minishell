/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:33:36 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/19 23:46:45 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_strdup function
char	*ft_strdup(const char *s1)
{
    char	*str;
    int		i;

    i = 0;
    while (s1[i])
        i++;
    str = (char *)malloc(sizeof(char) * (i + 1));
    if (!str)
        return (NULL);
    i = 0;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

// copy env function
char	**copy_the_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

// ft_strlen function
size_t	ft_strlen(const char *s)
{
    size_t	i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

static int	count_word(const char *str, char c, size_t slen)
{
	size_t	i;
	size_t	old_i;
	size_t	count;

	count = 0;
	i = 0;
	while (i < slen)
	{
		while (i < slen && str[i] == c)
			i++;
		old_i = i;
		while (i < slen && str[i] != c)
			i++;
		if (i > old_i)
			count++;
	}
	return (count);
}

void	*freee(char **string, int index)
{
	int	i;

	i = 0;
	while (i <= index)
	{
		free(string[i]);
		string[i] = NULL;
		i++;
	}
	free(string);
	string = NULL;
	return (NULL);
}

static void	*subs(char const *s, char c, size_t slen, char **strings)
{
	size_t	i;
	size_t	j;
	size_t	index;
	char	buffer[255];

	index = 0;
	i = 0;
	while (i < slen)
	{
		while (i < slen && s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		j = 0;
		while (i < slen && s[i] != c)
			buffer[j++] = s[i++];
		buffer[j] = '\0';
		strings[index] = ft_strdup(buffer);
		if (!strings[index])
			return (freee(strings, (index - 1)));
		index++;
	}
	return ((void *)1);
}

char	**ft_split(char const *s, char c)
{
	size_t	slen;
	char	**strings;
	int		count_w;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	count_w = count_word(s, c, slen);
	strings = (char **)malloc(sizeof(char *) * (count_w + 1));
	if (!strings)
		return (NULL);
	if (!subs(s, c, slen, strings))
		return (NULL);
	strings[count_w] = NULL;
	return (strings);
}

// ft_strcmp function
int	ft_strcmp(char *str, char *str2)
{
	int i;

	i = 0;
	if(!str || !str2)
		return (0);
	while (str[i] && str2[i])
	{
		if (str[i] != str2[i])
			return (0);
		i++;
	}
	if (str[i] != str2[i])
		return (0);
	return (1);
}

// ft_strjoin function
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

int	search_for_path(t_table *table)
{
	int	i;

	i = 0;
	while (table->env[i])
	{
		if (ft_strncmp(table->env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

// a function to check the access of the path
int	check_access(char *command, t_cmd *cmd, t_table *table)
{
	char	*env = getenv("PATH");
	char	**splited = NULL;
	int		i;
	int		flag;
	
	flag = 0;
	i = 0;
	
	if (search_for_path(table) != -1)
	{
		env = table->env[search_for_path(table)];
		// copy all after =
		env = ft_strdup(env + 5);
		splited = ft_split(env, ':');
	}
	if (search_for_path(table) == -1)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		// no shuch file or directory
		ft_putstr_fd(": No such file or directory\n", 2);
		table->exit_status = 127;
		exit(127);
	}
	while (splited[i])
	{
		char	*new_path = ft_strjoin(splited[i], "/");
		char	*new_path2 = ft_strjoin(new_path, command);
		if (access(new_path2, F_OK) == 0 && access(new_path2, X_OK) == 0)
		{
			flag = 1;
			cmd->path = new_path2;
			break ;
		}
		i++;
	}
	if (flag)
		return (1);
	return (0);
}
