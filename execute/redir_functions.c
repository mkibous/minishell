/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:18:43 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/23 01:20:23 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_if_redir_in(t_cmd *cmd, int *fd_in, t_table *table, int i)
{
	if (*fd_in != 0)
		close(*fd_in);
	if (ft_strncmp(cmd->redir[i], "<", ft_strlen(cmd->redir[i])) == 0)
		*fd_in = open(cmd->file[i], O_RDONLY);
	else if (ft_strncmp(cmd->redir[i], "<<", ft_strlen(cmd->redir[i])) == 0)
		*fd_in = heredoc(cmd, i);
	if (*fd_in == -1)
	{
		perror("open");
		table->exit_status = 1;
		exit(1);
	}
}

void	check_if_redir_out(t_cmd *cmd, int *fd_out, t_table *table, int i)
{
	int	len1;

	len1 = ft_strlen(cmd->redir[i]);
	if (*fd_out != 1)
		close(*fd_out);
	if (ft_strncmp(cmd->redir[i], ">", len1) == 0)
		*fd_out = open(cmd->file[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (ft_strncmp(cmd->redir[i], ">>", len1) == 0)
		*fd_out = open(cmd->file[i], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (*fd_out == -1)
	{
		perror("open");
		table->exit_status = 1;
		exit(1);
	}
}

void	for_handle_redir(t_cmd *cmd, t_table *table, int k, int **fd)
{
	int	i;

	i = 0;
	while (cmd->redir[i])
	{
		if (ft_strncmp(cmd->redir[i], "<", 1) == 0
			|| ft_strncmp(cmd->redir[i], "<<", 2) == 0)
		{
			check_if_redir_in(cmd, &cmd->in, table, i);
			if (cmd->next)
				cmd->out = fd[k + 1][1];
		}
		else if (ft_strncmp(cmd->redir[i], ">", 1) == 0
			|| ft_strncmp(cmd->redir[i], ">>", 2) == 0)
		{
			check_if_redir_out(cmd, &cmd->out, table, i);
			if (cmd->in == 0)
			{
				if (cmd->prev)
					cmd->in = fd[k][0];
			}
		}
		i++;
	}
}

void	handle_redir(t_cmd *cmd, t_table *table, int k, int **fd)
{
	cmd->in = 0;
	cmd->out = 1;
	if (cmd->redir)
		for_handle_redir(cmd, table, k, fd);
	else
	{
		if (k > 0)
			cmd->in = fd[k][0];
		if (cmd->next)
			cmd->out = fd[k + 1][1];
	}
	dup2(cmd->in, 0);
	dup2(cmd->out, 1);
	if (cmd->in != 0)
		close(cmd->in);
	if (cmd->out != 1)
		close(cmd->out);
}
