/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:11:23 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/13 18:32:49 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Function echo with printf and check redirection
void	ft_echo(t_cmd *cmd, t_table *table)
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
		if (cmd->echo_new_line == 0)
			ft_putstr_fd("\n", 1);
	}
}

// change pwd with protection
void	change_pwd(t_table *table)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	
	i = 0;
	while (table->env[i])
	{
		if (ft_strncmp(table->env[i], "PWD=", 4) == 0)
		{
			tmp = ft_strdup(table->env[i]);
			free(table->env[i]);
			tmp2 = getcwd(NULL, 0);
			table->env[i] = ft_strjoin("PWD=", tmp2);
			free(tmp2);
			free(tmp);
		}
		if (ft_strncmp(table->env[i], "OLDPWD=", 7) == 0)
		{
			char *oldpwd = table->pwd_env;
			table->env[i] = ft_strjoin("OLDPWD=", oldpwd);
		}
		i++;
	}
	table->pwd_env = getcwd(NULL, 0);
}
// fucntion cd with opendir and readdir
void	ft_cd(t_cmd *cmd, t_table *table)
{
	char	*path;

	if (cmd->argv[1] == NULL || ft_strcmp(cmd->argv[1], "~") == 1)
		path = getenv("HOME");
	else
		path = cmd->argv[1];
	if (ft_strncmp(path, "~", 1) && access(path, F_OK) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		if (chdir(path) == -1)
		{
			ft_putstr_fd("cd: permission denied: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	change_pwd(table);
}
//function of pwd command
void    ft_pwd(t_cmd *cmd, t_table *table)
{
	char    cwd[1024];
	int     i;
	int 	fd;

	i = 0;
	if (cmd->redir)
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
			{
				table->exit_status = 1;
				exit(1);
			}
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
		{
			table->exit_status = 1;
			exit(1);
		}
		printf("%s\n", cwd);
	}
}

void	ft_env(t_table *table, t_cmd *cmd)
{
	int i;
	int	fd;

	i = 0;
	if (cmd->redir)
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

    i = 0;
    j = 0;
    len = ft_strlen_2d(table->env) + 1;
    new_env = (char **)malloc(sizeof(char *) * len);
	int d= 1;
	char	**the_last;
	char	*err_join;
	
	the_last = (char **)malloc(sizeof(char *) * 1000);
	err_join = ft_strdup("unset: `");
	int f = 0;
	int	flag = 0;
	while (cmd->argv[d])
	{
		if (ft_strchr(cmd->argv[d], '=') != NULL)
		{
			the_last[f] = ft_strdup(cmd->argv[d]);
			flag = 1;	
			f++;
		}
		d++;
	}
	the_last[f] = NULL;
	if (flag == 1)
	{
		ft_putstr_fd(err_join, 2);
		ft_putstr_fd(the_last[f - 1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	d = 0;
	while(cmd->argv[++d])
	{
		i = 0;
		j = 0;

		if (ft_strchr(cmd->argv[d], '=') != NULL)
			continue;
    	while (table->env[i])
    	{
    	    if (ft_strncmp(table->env[i], cmd->argv[d], ft_strlen(cmd->argv[d])) != 0)
    	    {
    	        new_env[j] = ft_strdup(table->env[i]);
				j++;
			}
    	    i++;
    	}
		new_env[j] = NULL;
		table->env = copy_the_env(new_env);
	}
	// samething but apply in the export
	i = 0;
	j = 0;
	len = ft_strlen_2d(table->declare_x) + 1;
	char	**new_declare_x;
	new_declare_x = (char **)malloc(sizeof(char *) * len);

	d = 0;
	while (cmd->argv[++d])
	{
		i = 0;
		j = 0;

		if (ft_strchr(cmd->argv[d], '=') != NULL)
			continue;
		cmd->argv[d] = ft_strjoin("declare -x ", cmd->argv[d]);
    	while (table->declare_x[i])
    	{
    	    if (ft_strncmp(table->declare_x[i], cmd->argv[d], ft_strlen(cmd->argv[d])) != 0)
    	    {
    	        new_declare_x[j] = ft_strdup(table->declare_x[i]);
				j++;
			}
    	    i++;
    	}
		new_declare_x[j] = NULL;
		table->declare_x = copy_the_env(new_declare_x);
	}
}

// function check if the str is integer or nor include '-' and '+'
int	ft_is_integer(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// function exit with all the protection
void	ft_exit(t_cmd *cmd, t_table *table)
{
	if (cmd->argv[1] == NULL)
	{
		ft_putstr_fd("exit\n", 2);
		exit(table->exit_status);
	}
	else
	if (!ft_is_integer(cmd->argv[1]))
	{
		ft_putstr_fd("exit\nmsh: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		table->exit_status = 255;
		exit(255);
	}
	else if (ft_strlen_2d(cmd->argv) > 2)
	{
		ft_putstr_fd("exit\nmsh: exit: too many arguments\n", 2);
		table->exit_status = 1;
		if (cmd->pipe)
			exit(1);
	}
	else if (ft_is_integer(cmd->argv[1]))
	{
		table->exit_status = ft_atoi(cmd->argv[1]);
		ft_putstr_fd("exit\n", 2);
		exit(table->exit_status);
	}
}