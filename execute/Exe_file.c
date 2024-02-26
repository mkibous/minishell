/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exe_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:42:02 by aitaouss          #+#    #+#             */
/*   Updated: 2024/02/25 04:37:27 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_built_in(t_cmd *cmd, int fd[][2], t_table *table, int k)
{
	if (cmd->next)
		close(fd[k][1]);
	if (ft_strcmp(cmd->cmd, "cd"))
		ft_cd(cmd);
	else if (ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd();
	else if (ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "env"))
		ft_env(table);
	else if (ft_strcmp(cmd->cmd, "export"))
		ft_export(cmd, table);
	else if (ft_strcmp(cmd->cmd, "unset"))
		ft_unset(cmd, table);
}

void ft_exit(char **line)
{
	if (ft_strcmp(*line, "exit") == 1)
	{
		free(*line);
		exit(0);
	}
}

void close_file_descriptor(int fd[][2], int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}


void	execute_for_cmd(t_cmd *cmd, t_table *table)
{
	int	k;
	int	fd[table->count_cmd][2];
	pid_t	pid[table->count_cmd];

	k = 0;
	while (k < table->count_cmd)
	{
		if (pipe(fd[k]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		k++;
	}
	k = 0;
	while (cmd)
	{
		pid[k] = fork();
		if (pid[k] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid[k] == 0)
		{
			if (k > 0)
				dup2(fd[k][0], 0);
			if (cmd->next)
				dup2(fd[k + 1][1], 1);
			close_file_descriptor(fd, k);
			if (cmd->is_builtin)
				execute_built_in(cmd, fd, table, k);
			else
				execute_cmd(cmd, fd, cmd->argv, k);
			exit(EXIT_SUCCESS);
		}
		k++;
		cmd = cmd->next;
	}
	close_file_descriptor(fd, k);
	k = 0;
	while (k < table->count_cmd)
	{
		waitpid(pid[k], NULL, 0);
		k++;
	}
}
