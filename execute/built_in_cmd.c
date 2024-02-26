/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:11:23 by aitaouss          #+#    #+#             */
/*   Updated: 2024/02/24 23:04:03 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Function echo with printf
void	ft_echo(t_cmd *cmd)
{
	int i;

	i = 1;
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
}

// fucntion cd with opendir and readdir
void	ft_cd(t_cmd *cmd)
{
	DIR		*dir;
	char	*path;

	if (cmd->argv[1] == NULL)
		path = "/Users/aitaouss";
	else
		path = cmd->argv[1];
	dir = opendir(path);
	if (dir == NULL)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		chdir(path);
		closedir(dir);
	}
}
//function of pwd command
void    ft_pwd()
{
	char    cwd[1024];
	if (!getcwd(cwd, sizeof(cwd)))
		exit(1);
	printf("%s\n", cwd);
	exit(0);
}

void	ft_env(t_table *table)
{
	int i;

	i = 0;
	while (table->env[i])
	{
		ft_putstr_fd(table->env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

// add env function
char	**ft_add_env(char **env, char *str)
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

// function export
void	ft_export(t_cmd *cmd, t_table *table)
{
	int		i;
	char	*str;

	i = 1;
	while (cmd->argv[i])
	{
		if (ft_strchr(cmd->argv[i], '='))
		{
			table->env = ft_add_env(table->env, cmd->argv[i]);
		}
		else
		{
			str = ft_strjoin(cmd->argv[i], "=");
			table->env = ft_add_env(table->env, str);
			free(str);
		}
		i++;
	}
}

// ft_strlen 2d
int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// function unset
void ft_unset(t_cmd *cmd, t_table *table)
{
    int  i;
    int  j;
    int  len;
    char **new_env;

    i = 0;
    j = 0;
    len = ft_strlen_2d(table->env) + 1;
    new_env = (char **)malloc(sizeof(char *) * len);
	if (cmd->argv[1] == NULL)
	{
		ft_putstr_fd("nset: not enough arguments\n", 2);
		return ;
	}
    while (table->env[i])
    {
        if (ft_strncmp(table->env[i], cmd->argv[1], ft_strlen(cmd->argv[1])) != 0)
        {
            new_env[j] = ft_strdup(table->env[i]);
            j++;
        }
        i++;
    }
    new_env[j] = NULL; // Moved this line inside the loop
    i = 0;
    while (table->env[i])
    {
        free(table->env[i]);
        i++;
    }
    free(table->env);
    table->env = new_env;
}
