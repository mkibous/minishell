/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:24:57 by aitaouss          #+#    #+#             */
/*   Updated: 2024/02/23 00:29:12 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_handler(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd(GREEN"\nminishell$ "RESET, 1);
}

void ft_cmd_free(t_cmd **cmd)
{
	while ((*cmd))
	{
		// free((*cmd)->cmd);
		ft_free((*cmd)->argv);
		//free((*cmd)->file);
		(*cmd) = (*cmd)->next;
	}
	free(*cmd);
	(*cmd) = NULL;
}

// MIne
// int	ft_strcmp(char *str, char *str2)
// {
// 	int i;

// 	i = 0;
// 	while (str[i] && str2[i])
// 	{
// 		if (str[i] != str2[i])
// 			return (0);
// 		i++;
// 	}
// 	if (str[i] != str2[i])
// 		return (0);
// 	return (1);
// }

int main(int argc, char **argv, char **envp)
{
	char *line;
	t_cmd *cmd;

	// (void)argc;
	// (void)argv;
	cmd = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	
	while (1)
	{
		line = readline(GREEN"minishell$ "RESET);
		if(line)
		{
			add_history(line);
			ft_tokenizing(line, &cmd);
			execute_part(cmd, envp);
			ft_cmd_free(&cmd);
		}
		if (!line)
			exit(0);
		free(line);
	}
	
}