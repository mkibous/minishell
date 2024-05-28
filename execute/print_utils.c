/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:26:04 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/24 17:02:08 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_with_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
}

void	putstr_pro(char *str, char *path)
{
	ft_putstr_fd(str, 2);
	print_with_fd(path, 2);
}

void	put_err(t_table *table, char **the_last, char *err_join, int f)
{
	ft_putstr_fd(err_join, 2);
	ft_putstr_fd(the_last[f - 1], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	table->exit_s = 1;
	if (table->cmd->pipe)
		exit(1);
}
