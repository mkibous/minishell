/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:18:43 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/28 13:36:49 by aitaouss         ###   ########.fr       */
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
		table->get_out = 1;
		perror("open");
		table->exit_s = 1;
		if (cmd->pipe || !cmd->is_builtin)
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
		table->get_out = 1;
		perror("open");
		table->exit_s = 1;
		if (cmd->pipe || !cmd->is_builtin)
			exit(1);
	}
}

void	loop_handle_redir(t_cmd *cmd, int k, int **fd, int flag)
{
	int	i;

	(1) && (i = -1, cmd->table->get_out = 0);
	while (cmd->redir[++i] && cmd->table->get_out == 0)
	{
		if (flag == 1 && i == 0)
		{
			if (cmd->next)
				cmd->out = fd[k][1];
		}
		if (ft_strncmp(cmd->redir[i], "<", ft_strlen(cmd->redir[i])) == 0
			|| (ft_strncmp(cmd->redir[i], "<<", ft_strlen(cmd->redir[i]))
				== 0 && flag == 0))
		{
			check_if_redir_in(cmd, &cmd->in, cmd->table, i);
			if (cmd->next)
				cmd->out = fd[k][1];
		}
		else if (ft_strncmp(cmd->redir[i], ">", ft_strlen(cmd->redir[i])) == 0
			|| ft_strncmp(cmd->redir[i], ">>", ft_strlen(cmd->redir[i])) == 0)
		{
			check_if_redir_out(cmd, &cmd->out, cmd->table, i);
			condition_flag_herdoc(cmd, k, fd);
		}
	}
}

void	for_handle_redir(t_cmd *cmd, int k, int **fd)
{
	int	i;
	int	flag;

	flag = 0;
	i = -1;
	loop_handle_redir(cmd, k, fd, flag);
}

void	handle_redir(t_cmd *cmd, int k, int **fd)
{
	cmd->in = 0;
	cmd->out = 1;
	if (cmd->redir)
		for_handle_redir(cmd, k, fd);
	else
	{
		if (k > 0)
			cmd->in = fd[k - 1][0];
		if (cmd->next)
			cmd->out = fd[k][1];
	}
	dup2(cmd->in, 0);
	dup2(cmd->out, 1);
	if (cmd->in != 0)
		close(cmd->in);
	if (cmd->out != 1)
		close(cmd->out);
}
