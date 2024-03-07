/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:11:23 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/06 01:20:32 by aitaouss         ###   ########.fr       */
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
			}
			j++;
		}
		while (cmd->argv[i])
		{
			ft_putstr_fd(cmd->argv[i], fd);
			i++;
		}
		if (cmd->echo_new_line == 0)
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
void	ft_cd(t_cmd *cmd, t_table *table)
{
	char	*path;
	int		fd_cd;

	fd_cd = open(ft_strjoin(table->alpha, "/cd"), O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->argv[1] == NULL || ft_strcmp(cmd->argv[1], "~") == 1)
		path = getenv("HOME");
	else
		path = cmd->argv[1];
	if(cmd->argv[1])
		write(fd_cd, path, ft_strlen(path));
	else
		write(fd_cd, path, ft_strlen(path));
	close(fd_cd);
	if (ft_strncmp(cmd->path, "~", 1) && access(path, F_OK) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		printf("cmd path : %s\n", cmd->path);
		if (chdir(path) == -1)
		{
			ft_putstr_fd("cd: permission denied: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd("\n", 2);
		}
	}
}
//function of pwd command
void    ft_pwd(t_cmd *cmd)
{
	char    cwd[1024];
	int     i;
	int 	fd;

	i = 0;
	if (cmd->redir[0] != NULL)
	{
		while (cmd->redir[i])
		{
			if (ft_strncmp(cmd->redir[i], ">>", 2) == 0)
				fd = open(cmd->file[i], O_CREAT | O_RDWR | O_APPEND, 0644);
			else if (ft_strncmp(cmd->redir[i], ">", 1) == 0)
				fd = open(cmd->file[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
			else if (ft_strncmp(cmd->redir[i], "<", 1) == 0)
				fd = 1;
			if (!getcwd(cwd, sizeof(cwd)))
				exit(1);
			if (cmd->redir[i + 1] == NULL)
			{
				ft_putstr_fd(cwd, fd);
				ft_putstr_fd("\n", fd);
			}
			close(fd);
			i++;
		}
	}
	else
	{
		if (!getcwd(cwd, sizeof(cwd)))
			exit(1);
		printf("%s\n", cwd);
		exit(0);
	}
}

void	ft_env(t_table *table, t_cmd *cmd)
{
	int i;
	int	fd;

	i = 0;
	if (cmd->redir[0] != NULL)
	{
		while (cmd->redir[i])
		{
			if (ft_strncmp(cmd->redir[i], ">>", 2) == 0)
				fd = open(cmd->file[i], O_CREAT | O_RDWR | O_APPEND, 0644);
			else if (ft_strncmp(cmd->redir[i], ">", 1) == 0)
				fd = open(cmd->file[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
			else if (ft_strncmp(cmd->redir[i], "<", 1) == 0)
				fd = 1;
			ft_putstr2d_fd(table->env, fd);
			ft_putstr_fd("\n", fd);
			close(fd);
			i++;
		}
	}
	else
	{
		while (table->env[i])
		{
			ft_putstr_fd(table->env[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
	
	}
}

// add env function
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

// function export
void	ft_export(t_cmd *cmd, t_table *table)
{
	int		i;
	int		fd_ex;
	int		check;
	char	**new_env;

	check = 0;
	i = 1;
	if (ft_strlen_2d(cmd->argv) > 2)
		new_env = (char **)malloc(sizeof(char *) * (ft_strlen_2d(table->env) + ft_strlen_2d(cmd->argv)));
	
	while (cmd->argv[i])
	{
		fd_ex = open(ft_strjoin(table->alpha, "/export.txt"), O_CREAT | O_RDWR | O_APPEND | O_TRUNC, 0644);
		if (cmd->argv[i][0] == '=' || !ft_isalpha(cmd->argv[i][0]))
		{
			ft_putstr_fd("export : not a valid identifier\n", 2);
			ft_putstr2d_fd(table->env, fd_ex);
			return ;
		}
		if (ft_strchr(cmd->argv[i], '='))
		{
			check = check_if_exist(cmd->argv[i], table->env);
			if (check != -1)
			{
				table->env[check] = ft_strdup(cmd->argv[i]);
				check = 0;
				ft_putstr2d_fd(table->env, fd_ex);
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
			ft_putstr2d_fd(table->env, fd_ex);
		}
		i++;
	}
	close(fd_ex);
}

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

// function unset
void ft_unset(t_cmd *cmd, t_table *table)
{
    int  i;
    int  j;
    int  len;
    char **new_env;
	int	fd_out;
    i = 0;
    j = 0;
    len = ft_strlen_2d(table->env) + 1;
    new_env = (char **)malloc(sizeof(char *) * len);
	if (cmd->argv[1] == NULL)
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return ;
	}
	int d= 1;
	while(cmd->argv[d])
	{
		fd_out = open(ft_strjoin(table->alpha, "/unset.txt"), O_CREAT | O_RDWR | O_APPEND | O_TRUNC, 0644);
		i = 0;
		j = 0;
    	while (table->env[i])
    	{
    	    if (ft_strncmp(table->env[i], cmd->argv[d], ft_strlen(cmd->argv[d])) != 0)
    	    {
    	        new_env[j] = ft_strdup(table->env[i]);
				if (cmd->argv[d + 1] == NULL)
				{
					ft_putstr_fd(new_env[j], fd_out);
					ft_putstr_fd("\n", fd_out);
				}
				j++;
    	    }
    	    i++;
    	}
		table->env = copy_the_env(new_env);
		d++;
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
		unlink("exit");
		exit(0);
	}
}