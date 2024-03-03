/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:11:23 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/01 23:53:37 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Function echo with printf and check redirection
void	ft_echo(t_cmd *cmd)
{
	int i;
	int	fd;

	fd = 1;
	i = 1;
	int j = 0;
	if (cmd->redir)
	{
		while(cmd->redir[j])
		{
			if (cmd->file)
			{
				if (ft_strncmp(cmd->redir[j], ">>", 2) == 0)
					fd = open(cmd->file[j], O_CREAT | O_RDWR | O_APPEND, 0644);
				else if (ft_strncmp(cmd->redir[j], ">", 1) == 0)
					fd = open(cmd->file[j], O_CREAT | O_RDWR | O_TRUNC, 0644);
				// close(fd);
			}
			j++;
		}
		while (cmd->argv[i])
		{
			ft_putstr_fd(cmd->argv[i], fd);
			i++;
		}
		ft_putstr_fd("\n", fd);
		close(fd);
	}
	else
	{
		while (cmd->argv[i])
		{
			ft_putstr_fd(cmd->argv[i], 1);
			i++;
		}
		ft_putstr_fd("\n", 1);
	}
}

// fucntion cd with opendir and readdir
void	ft_cd(t_cmd *cmd)
{
	char	*path;
	int		fd_cd;

	fd_cd = open("cd", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->argv[1] == NULL)
		path = "/Users/aitaouss";
	else
		path = cmd->argv[1];
	if(cmd->argv[1])
		write(fd_cd, path, ft_strlen(path));
	else
		write(fd_cd, path, ft_strlen(path));
	close(fd_cd);
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		chdir(path);
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
		// if (table->env[i + 1] != NULL)
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

// function putstr2d_fd
void	ft_putstr2d_fd(char **str, int fd)
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

// ft_strlen 2d
int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strlen_until_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i + 1] == '=')
			break;
		i++;
	}
	return (i);
}

// function export
void	ft_export(t_cmd *cmd, t_table *table)
{
	int		i;
	int		fd_ex;

	fd_ex = open("export", O_CREAT | O_RDWR | O_TRUNC, 0644);
	i = 1;
	while (cmd->argv[i])
	{
		if (ft_strchr(cmd->argv[i], '='))
		{
			if (ft_strncmp(table->env[i], cmd->argv[i], ft_strlen_until_equal(cmd->argv[i])) == 0)
			{
				while(table->env[i])
				{
					if (ft_strncmp(table->env[i], cmd->argv[i], ft_strlen(cmd->argv[i])) == 0)
					{
						table->env[i] = ft_strdup(cmd->argv[i]);
						break ;
					}
					i++;
				}
			}
			else
				table->env = ft_add_env(table->env, cmd->argv[i]);
		}
		i++;
	}
	ft_putstr2d_fd(table->env, fd_ex);
	ft_putstr_fd("\n", fd_ex);
	close(fd_ex);
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
    new_env[j] = NULL;
    i = 0;
    while (table->env[i])
    {
        free(table->env[i]);
        i++;
    }
    free(table->env);
    table->env = new_env;
}

// function exit
void ft_exit(char *line)
{
	if (ft_strcmp(line, "exit") == 1)
	{
		int fd_out = open("exit", O_CREAT | O_RDWR, 0644);
		dup2(fd_out, 1);
		write(fd_out, "1", 1);
		free(line);
		// unlink("exit");
		exit(0);
	}
}