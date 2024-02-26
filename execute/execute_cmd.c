/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 21:51:03 by aitaouss          #+#    #+#             */
/*   Updated: 2024/02/25 04:01:16 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// creat shild with pipe and use execve
void    execute_cmd(t_cmd *cmd, int fd[][2], char **argv, int k)
{
	execve(cmd->cmd, argv, NULL);
	if (check_access(cmd->cmd, cmd) == 0)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	else
	{
		if (cmd->next)
			close(fd[k][0]);
		close(fd[k][1]);
		if(execve(cmd->path, argv, NULL) == -1)
			perror("execve");
		exit(EXIT_FAILURE);
	}
}
