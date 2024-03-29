/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exe_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:42:02 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/27 16:04:27 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_built_in(t_cmd *cmd, int **fd, t_table *table, int k)
{
	if (cmd->next)
		close(fd[k][1]);
	if (ft_strcmp(cmd->cmd, "cd"))
		ft_cd(cmd, table);
	else if (ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd(table);
	else if (ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd, table);
	else if (ft_strcmp(cmd->cmd, "env"))
		ft_env(table);
	else if (ft_strcmp(cmd->cmd, "export"))
		ft_export(cmd, table);
	else if (ft_strcmp(cmd->cmd, "unset"))
		ft_unset(cmd, table);
	else if (ft_strcmp(cmd->cmd, "exit"))
		ft_exit(cmd, table);
}

void	close_file_descriptor(int **fd, int k)
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

void	creat_pipe(t_table *table, int **fd, int k)
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

void	alloc_and_check_failure(int ***fd, pid_t **pid, t_table **table)
{
	int	i;

	i = -1;
	*pid = (pid_t *)malloc(sizeof(pid_t) * (*table)->count_cmd);
	if (!(*pid))
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	*fd = (int **)malloc(sizeof(int *) * (*table)->count_cmd);
	if (!(*fd))
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (++i < (*table)->count_cmd)
	{
		(*fd)[i] = (int *)malloc(sizeof(int) * 2);
		if (!(*fd)[i])
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}
}

void	execute_for_cmd(t_cmd *cmd, t_table *table)
{
	int		k;
	int		**fd;
	pid_t	*pid;

	alloc_and_check_failure(&fd, &pid, &table);
	k = 0;
	if (cmd->is_builtin && !cmd->pipe)
	{
		(1) && (table->tmp_in = dup(0), table->tmp_out = dup(1));
		handle_redir(cmd, table, k, fd);
		execute_built_in(cmd, fd, table, k);
		dup2(table->tmp_in, 0);
		dup2(table->tmp_out, 1);
		(1) && (close(table->tmp_in), close(table->tmp_out), table->tmp_in = 0);
		return ;
	}
	creat_pipe(table, fd, k);
	loop_child(cmd, fd, table, pid);
	wait_all_pid(table, pid, k);
	close_file_descriptor(fd, k);
}
