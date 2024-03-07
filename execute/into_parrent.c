/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   into_parrent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:09:10 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/07 20:57:47 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	max_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**join_2d(char **join, char **to_join)
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
void    into_parrent(t_cmd *cmd, int pid[], int k, t_table *table, char buf[])
{
	int bytes;

	if (cmd->cmd)
	{
		if (ft_strncmp(cmd->cmd, "exit", 4) == 0)
		{
			waitpid(pid[k], NULL, 0);
			int fd_in = open(ft_strjoin(table->alpha, "/exit"), O_RDONLY);
			bytes = 1;
			while ((bytes = read(fd_in, buf, 1)));
			unlink(ft_strjoin(table->alpha, "/exit"));
			if (buf[0] == '1')
				exit(EXIT_SUCCESS);
		}
		if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
		{
			char *join = ft_strdup("");
			waitpid(pid[k], NULL, 0);
			int fd_in = open(ft_strjoin(table->alpha, "/cd"), O_RDONLY);
			char *path;
			path = (char *)malloc(1000);
			bytes = 1;
			while (bytes)
			{
				bytes = read(fd_in, path, 1000);
				if (bytes == -1)
					break;
				path[bytes] = '\0';
				join = ft_strjoin(join, path);
			}
			unlink(ft_strjoin(table->alpha, "/cd"));
			chdir(join);
		}
		if (ft_strncmp(cmd->cmd, "export", 6) == 0)
		{
			waitpid(pid[k], NULL, 0);
			if (cmd->argv[1])
			{
				int fd_in;
				char    *buffer;
				char 	*join;

				fd_in = open(ft_strjoin(table->alpha, "/export.txt"), O_RDONLY);
				bytes = 1;
				buffer = (char *)malloc(1000);
				join = ft_strdup("");
				while(bytes)
				{
					bytes = read(fd_in, buffer, sizeof(buffer) - 1);
					buffer[bytes] = '\0';
					if (bytes)
						join = ft_strjoin(join, buffer);
				}
				table->env = ft_split(join, '\n');
				unlink(ft_strjoin(table->alpha, "/export.txt"));
				// parte for the declare x
				char	*to_join;
				to_join = ft_strdup("declare -x ");
				int i = 0;
				while (cmd->argv[i])
					i++;
				char	**declare_x = (char **)malloc(sizeof(char *) * ft_strlen_2d(table->env) + i);
				i = 0;
				while (table->env[i])
				{
					declare_x[i] = ft_strjoin(to_join, table->env[i]);
					i++;
				}
				declare_x[i] = NULL;
				table->declare_x = declare_x;
			}
			if (!table->declare_x)
			{
				char	*to_join;
				to_join = ft_strdup("declare -x ");
				int i = 0;
				while (cmd->argv[i])
					i++;
				char	**declare_x = (char **)malloc(sizeof(char *) * ft_strlen_2d(table->env) + i);
				i = 0;
				while (table->env[i])
				{
					declare_x[i] = ft_strjoin(to_join, table->env[i]);
					i++;
				}
				declare_x[i] = NULL;
				table->declare_x = declare_x;
			}
			if (cmd->argv[1])
			{
				char	*to_join;
				to_join = ft_strdup("declare -x ");
				char	**tmp;
				int j = 1;
				int i = 0;

				tmp = (char **)malloc(sizeof(char *) * ft_strlen_2d(table->env) + i);
				while (cmd->argv[j])
				{
					if (ft_strchr(cmd->argv[j], '=') == 0)
					{
						tmp[i] = ft_strjoin(to_join, cmd->argv[j]);
						i++;
					}
					j++;
				}
				tmp[i] = NULL;
				if (!table->trash)
					table->trash = tmp;
				else
					table->trash = join_2d(table->trash, tmp);
				table->declare_x = join_2d(table->declare_x, table->trash);
			}
			if (cmd->argv[1] == NULL)
			{
				ft_putstr2d_fd(table->declare_x, 1);
				ft_putstr_fd("\n", 1);
			}
		}
		if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		{
			waitpid(pid[k], NULL, 0);
			if (cmd->argv[1])
			{
				int	fd_in;
				char *buffer;
				char *join;
				
				fd_in = open(ft_strjoin(table->alpha, "/unset.txt"), O_RDONLY);
				bytes = 1;
				buffer = (char *)malloc(1000);
				join = ft_strdup("");
				while(bytes)
				{
					bytes = read(fd_in, buffer, sizeof(buffer) - 1);
					buffer[bytes] = '\0';
					if (bytes)
						join = ft_strjoin(join, buffer);
				}
				table->env = ft_split(join, '\n');
			}
			unlink(ft_strjoin(table->alpha, "/unset.txt"));
		}
	}
}