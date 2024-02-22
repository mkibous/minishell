/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exe_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:42:02 by aitaouss          #+#    #+#             */
/*   Updated: 2024/02/22 15:53:45 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execute_part(t_cmd *cmd, char **env)
{
	int flag = 0;
	int pipefd[2];
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid_t pid = fork();
		if (pid == 0)
		{
			char *argv[] = {cmd->cmd, NULL};
			if (cmd->next)
				dup2(pipefd[1], 1);
			creat_shild(cmd, pipefd, cmd->argv);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(pipefd[1]);
		}
		cmd = cmd->next;
	}
	return 0;
}