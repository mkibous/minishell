/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   into_parrent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:09:10 by aitaouss          #+#    #+#             */
/*   Updated: 2024/02/27 16:07:56 by aitaouss         ###   ########.fr       */
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

void    into_parrent(t_cmd *cmd, int pid[], int k, t_table *table, char buf[])
{
	int bytes;

	if (ft_strncmp(cmd->cmd, "exit", 4) == 0)
	{
		waitpid(pid[k], NULL, 0);
		int fd_in = open("exit", O_RDONLY);
		bytes = 1;
		while ((bytes = read(fd_in, buf, 1)));
		unlink("exit");
		if (buf[0] == '1')
			exit(EXIT_SUCCESS);
	}
	if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
	{
		char *join = ft_strdup("");
		waitpid(pid[k], NULL, 0);
		int fd_in = open("cd", O_RDONLY);
		char *path;
		path = (char *)malloc(1000);
		bytes = 1;
		while (bytes)
		{
			bytes = read(fd_in, path, 1000);
			path[bytes] = '\0';
			join = ft_strjoin(join, path);
		}
		unlink("cd");
		chdir(join);
	}
	if (ft_strncmp(cmd->cmd, "export", 6) == 0)
	{
		waitpid(pid[k], NULL, 0);
		int fd_in = open("export", O_RDONLY);
		bytes = 1;
		int i = 0;
		char    buffer[1000];
		int		len_double = max_env(table->env);
		char	**new_env;

		new_env = (char **)malloc(sizeof(char *) * (len_double + 1));
		while(bytes)
		{
			bytes = read(fd_in, buffer, sizeof(buffer) - 1);
			buffer[bytes] = '\0';
			if (bytes)
			{
				new_env[i] = ft_strdup(buffer);
				i++;
			}
		}
		if (new_env[i - 1][ft_strlen(new_env[i - 1]) - 1] == '\n')
			new_env[i - 1][ft_strlen(new_env[i - 1]) - 1] = '\0';
		new_env[i] = NULL;
		table->env = new_env;
		unlink("export");
	}
}