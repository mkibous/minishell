/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:00:49 by mkibous           #+#    #+#             */
/*   Updated: 2024/02/19 22:56:58 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int sigfalg = 0;
void sig_handler(int signum)
{
    if(signum == SIGINT)
        sigfalg = 1;
}
void ft_readline(void)
{
    char *line;
    if(sigfalg == 0)
        line = readline("minishell➤ ");
    else
        (1) && (sigfalg = 0, line = readline("\nminishell➤ "));
    if(!line && sigfalg == 0)
        exit(0);
    ft_printf("%s", line);
    free(line);
}
int main ()
{

    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1
            ||sigaction(SIGQUIT, &sa, NULL) == -1) {
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
