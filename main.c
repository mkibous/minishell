/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:00:49 by mkibous           #+#    #+#             */
/*   Updated: 2024/02/22 02:11:44 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_handler(int signum)
{
	if (signum == SIGINT)
		ft_printf("\nminishell ➤");
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
		}
		if (!line)
			exit(0);
		free(line);
	}
	
}
