/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:24:57 by aitaouss          #+#    #+#             */
/*   Updated: 2024/02/26 03:11:40 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// table len
int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

// init table
t_table	*ft_init_table(char **envp)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->env = (char **)malloc(sizeof(char *) * (ft_tablen(envp) + 1));
	if (!table->env)
		return (NULL);
	while (envp[i])
	{
		table->env[i] = ft_strdup(envp[i]);
		i++;
	}
	table->env[i] = NULL;
	return (table);
}

// For signal
void sig_handler(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd(GREEN"➜  "YELLOW""BOLD"minishell "RESET, 1);
}

// For free
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

// ft_builtin
void	ft_built_in(t_cmd **cmd, t_table *table)
{
	t_cmd	*tmp;
	
	tmp = *cmd;
	table->count_cmd = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->cmd, "cd") || ft_strcmp(tmp->cmd, "pwd") ||
			ft_strcmp(tmp->cmd, "echo") || ft_strcmp(tmp->cmd, "env") ||
			ft_strcmp(tmp->cmd, "export") || ft_strcmp(tmp->cmd, "unset"))
			tmp->is_builtin = 1;
		table->count_cmd++;
		tmp = tmp->next;
	} 
}
int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	t_table	*table;
	int		rr;

	(void)argc;
	(void)argv;
	cmd = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	table = ft_init_table(envp);
	while (1)
	{
		rr = rand() % 2;
		if (rr)		
			line = readline(GREEN"➜  "YELLOW""BOLD"minishell "RESET);
		else
			line = readline(RED"➜  "YELLOW""BOLD"minishell "RESET);
		if(line)
		{
			ft_exit(&line);
			if (ft_strcmp(line, "clear") == 1)
			{
				ft_putstr_fd(CLEAR, 1);
				continue;
			}
			add_history(line);
			ft_tokenizing(line, &cmd);
			ft_built_in(&cmd, table);
			if (cmd)
				execute_for_cmd(cmd, table);
			ft_cmd_free(&cmd);
		}
		if (!line)
		{
			free(line);
			exit(0);
		}
		free(line);
	}
}
