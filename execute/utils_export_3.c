/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:16:28 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/24 18:25:50 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alpha_num(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '\0' || str[0] == '=')
		return (-1);
	if (ft_isdigit(str[0]))
		return (-1);
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '=' && str[i] != '_')
			return (-1);
	}
	return (0);
}

void	free_fd_and_pid(int **fd, pid_t *pid)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	free(pid);
}

void	utils_util_dec(t_table *table, char **tmp_argv, int i, t_cmd *cmd)
{
	char	**new_env;

	*tmp_argv = ft_strjoin("declare -x ", cmd->argv[i]);
	new_env = ft_add_env2(table->declare_x, *tmp_argv);
	free(*tmp_argv);
	sort_double_pointer_2(new_env, ft_strlen_2d(new_env));
	table->declare_x = new_env;
}

void	if_in_herdoc(t_cmd *cmd)
{
	if (cmd->pipe || !cmd->is_builtin)
	{
		signal(SIGINT, sig_hand);
		signal(SIGQUIT, sig_hand);
		rl_catch_signals = 1;
	}
}

void	exit_state_in_child(t_cmd *cmd, t_table *table, int number)
{
	table->exit_s = number;
	if (cmd->pipe)
		exit(number);
}
