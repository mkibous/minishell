/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 21:51:03 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/27 15:57:27 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//function of pwd command
void	ft_pwd(t_table *table)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		table->exit_status = 1;
		exit(1);
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
}

void	for_execute(t_cmd *cmd, t_table *table, int **fd_s, int k)
{
	if (check_access(cmd->cmd, cmd, table) == 0)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		table->exit_status = 127;
		exit(127);
	}
	else
	{
		if (cmd->next)
			close(fd_s[k][0]);
		close(fd_s[k][1]);
		table->exit_status = 0;
		if (execve(cmd->path, cmd->argv, table->env) == -1)
		{
			ft_putstr_fd("msh: ", 2);
			ft_putstr_fd(cmd->cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			table->exit_status = 127;
			exit(127);
		}
		table->exit_status = 1;
		exit(EXIT_FAILURE);
	}
}

// creat shild with pipe and use execve
void	execute_cmd(t_cmd *cmd, int **fd_s, int k, t_table *table)
{
	int	i;

	execve(cmd->cmd, cmd->argv, table->env);
	i = 0;
	if (cmd->cmd)
		for_execute(cmd, table, fd_s, k);
}
