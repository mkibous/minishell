/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:00:49 by mkibous           #+#    #+#             */
/*   Updated: 2024/02/22 03:35:32 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_handler(int signum)
{
	if (signum == SIGINT)
		ft_printf("\nminishell ➤");
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
int main()
{
	char *line;
	t_cmd *cmd;

	cmd = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		line = readline("minishell ➤");
		if(line)
		{
			add_history(line);
			ft_tokenizing(line, &cmd);
			ft_cmd_free(&cmd);
		}
		if (!line)
			exit(0);
		free(line);
	}
	
}
