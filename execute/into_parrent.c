/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   into_parrent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:09:10 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/12 02:29:31 by aitaouss         ###   ########.fr       */
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

int	check_if_in_the_declare_x(char *str, char **declare_x)
{
	int i;

	i = 0;
	str = ft_strjoin("declare -x ", str);
	if (declare_x == NULL)
		return (0);
	// while (declare_x[i])
	// {
	// 	if (ft_strncmp(str, declare_x[i], ft_strlen(str)) == 0)
	// 		return (i);
	// 	i++;
	// }
	while (declare_x[i])
	{
		if (ft_strncmp(str, declare_x[i], ft_strlen_until_equal(str)) == 0)
			return (i);
		i++;
	}
	return (0);
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