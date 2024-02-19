/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:00:49 by mkibous           #+#    #+#             */
/*   Updated: 2024/02/19 19:20:02 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int sigfalg = 0;
void sig_handler(int signum)
{
    sigfalg = 1;
}
void ft_readline(void)
{
    char *line;
    if(sigfalg == 0)
        line = readline("minishell➤ ");
    else
        (1) && (sigfalg = 0, line = readline("\nminishell➤ "));
    if(!line)
        exit(0);
    free(line);
}
int main ()
{

    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error setting up SIGINT signal handler");
        return 1;
    }
    ft_readline();
    while (1)
    {
        if(sigfalg == 1)
        {
            ft_readline();
        }
    }
}
