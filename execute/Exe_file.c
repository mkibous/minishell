/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exe_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:42:02 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/13 23:47:44 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_built_in(t_cmd *cmd, int fd[][2], t_table *table, int k)
{
	if (cmd->next)
		close(fd[k][1]);
	if (ft_strcmp(cmd->cmd, "cd"))
		ft_cd(cmd, table);
	else if (ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd(cmd, table);
	else if (ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd, table);
	else if (ft_strcmp(cmd->cmd, "env"))
		ft_env(table, cmd);
	else if (ft_strcmp(cmd->cmd, "export"))
		ft_export(cmd, table);
	else if (ft_strcmp(cmd->cmd, "unset"))
		ft_unset(cmd, table);
	else if (ft_strcmp(cmd->cmd, "exit"))
		ft_exit(cmd, table);
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

void	creat_pipe(t_table *table, int fd[][2], int k)
{
	while (k < table->count_cmd)
	{
		if (pipe(fd[k]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		k++;
	}
}

void	into_child(t_cmd *cmd, int fd[][2], t_table *table, int k)
{
	if (k > 0)
		dup2(fd[k][0], 0);
	if (cmd->next)
		dup2(fd[k + 1][1], 1);
	close_file_descriptor(fd, k);
	if (cmd->is_builtin)
		execute_built_in(cmd, fd, table, k);
	else if (ft_strcmp(cmd->cmd, "clear"))
		ft_putstr_fd(CLEAR, 1);
	else
		execute_cmd(cmd, fd, cmd->argv, k, table);
	exit(EXIT_SUCCESS);
}

void	wait_all_pid(t_table *table, pid_t pid[], int k)
{
	int	status;

	status = 0;
	while (k < table->count_cmd)
	{
		waitpid(pid[k], &status, 0);
		k++;
	}
	table->exit_status = (WEXITSTATUS(status));
}
void	execute_for_cmd(t_cmd *cmd, t_table *table)
{
	int	k;
	int	fd[table->count_cmd][2];
	pid_t	pid[table->count_cmd];

	k = 0;
	creat_pipe(table, fd, k);
	while (cmd)
	{
		if (cmd->pipe || !cmd->is_builtin)
		{
			pid[k] = fork();
			if (pid[k] == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (pid[k] == 0)
				into_child(cmd, fd, table, k);
		}
		else
		{
			if (cmd->is_builtin)
				execute_built_in(cmd, fd, table, k);
			else if (ft_strcmp(cmd->cmd, "clear"))
				ft_putstr_fd(CLEAR, 1);
			else
				execute_cmd(cmd, fd, cmd->argv, k, table);
		}
		k++;
		cmd = cmd->next;
	}
	close_file_descriptor(fd, k);
	k = 0;
	wait_all_pid(table, pid, k);
}
