/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:18:43 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/05 21:48:09 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_out_append(t_cmd *cmd, int i)
{
	int	fd;

	fd = open(cmd->file[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd->file[i], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

void	redir_out(t_cmd *cmd, int i)
{
	int	fd;

	fd = open(cmd->file[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd->file[i], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

void	redir_in(t_cmd *cmd, int i)
{
	int	fd;

	fd = open(cmd->file[i], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd->file[i], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
}