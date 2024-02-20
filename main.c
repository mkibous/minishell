/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:00:49 by mkibous           #+#    #+#             */
/*   Updated: 2024/02/20 10:40:41 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int sigflag = 0;
void sig_handler(int signum)
{
	if (signum == SIGINT)
		sigflag = 1;
	if (signum == SIGQUIT)
		sigflag = 2;
}
void ft_readline(void)
{
	char *line;
	if (sigflag == 0)
		line = readline("minishell➤ ");
	else if (sigflag == 1)
		(1) && (sigflag = 0, line = readline("\nminishell➤ "));
	if (sigflag == 2)
		line = readline("");
	if(line)
		ft_tokenizing(line);
	if (!line && sigflag == 0)
		exit(0);
	free(line);
}
int main()
{
	struct sigaction sa;
	sa.sa_handler = sig_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Error setting up SIGINT signal handler");
		return 1;
	}
	ft_readline();
	while (1)
	{
		if (sigflag == 1)
		{
			ft_readline();
		}
	}
}
