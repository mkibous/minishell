/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 21:51:03 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/28 15:16:54 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_pwd(t_table *table)
{
	char	cwd[1024];
	int		i;

	i = -1;
	while (table->env[++i] && table->gar == 1)
	{
		if (ft_strncmp(table->env[i], "PWD=", 4) == 0)
		{
			ft_putstr_fd(table->env[i] + 4, 1);
			ft_putstr_fd("..", 1);
			ft_putstr_fd("\n", 1);
			return ;
		}
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		table->exit_s = 1;
		return ;
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
}

void	execute_utils(t_cmd *cmd, int k, t_table *table, int **fd_s)
{
	if (cmd->next)
		close(fd_s[k][0]);
	close(fd_s[k][1]);
	table->exit_s = 0;
	if (execve(cmd->path, cmd->argv, table->env) == -1)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		table->exit_s = 127;
		exit(127);
	}
	table->exit_s = 1;
	exit(EXIT_FAILURE);
}

void	for_execute(t_cmd *cmd, t_table *table, int **fd_s, int k)
{
	if (opendir(cmd->cmd) != NULL)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		table->exit_s = 126;
		exit(126);
	}
	if (check_access(cmd->cmd, cmd, table) == 0)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		table->exit_s = 127;
		exit(127);
	}
	else
		execute_utils(cmd, k, table, fd_s);
}

void	execute_cmd(t_cmd *cmd, int **fd_s, int k, t_table *table)
{
	int		i;

	if (table->exit_s == 1)
		return ;
	i = execve(cmd->cmd, cmd->argv, table->env);
	i = 0;
	if (cmd->cmd)
		for_execute(cmd, table, fd_s, k);
}
