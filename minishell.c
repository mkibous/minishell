/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:24:57 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/06 01:09:09 by aitaouss         ###   ########.fr       */
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
	table->alpha = getcwd(NULL, 0);
	return (table);
}

// For signal
void sig_handler(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd(GREEN"\n➜  "RED""BOLD"minishell "RESET, 1);
}

// For free
void ft_cmd_free(t_cmd **cmd)
{
	while ((*cmd))
	{
		// free((*cmd)->cmd);
		if ((*cmd)->cmd)
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
			ft_strcmp(tmp->cmd, "export") || ft_strcmp(tmp->cmd, "unset") || ft_strcmp(tmp->cmd, "exit"))
			tmp->is_builtin = 1;
		table->count_cmd++;
		tmp = tmp->next;
	} 
}
char **the_twode(char **twode)
{
	int index = 0;
	while (twode[index])
	{
		twode[index] = ft_strdup(twode[index]);
		index++;
	}
	twode[index] = NULL;
	return (twode);
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	t_table	*table;
	int		rr;
	char **allocation;

	(void)argc;
	(void)argv;
	cmd = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	allocation = the_twode(envp);
	table = ft_init_table(allocation);
	table->var = "➜  minishell ";
	while (1)
	{
		rr = rand() % 2;
		if (rr)		
			line = readline(GREEN"➜  "RED""BOLD"minishell "RESET);
		else
			line = readline(RED"➜  "RED""BOLD"minishell "RESET);
		if(line)
		{
			add_history(line);
			if (line[0] != '\0')
				ft_tokenizing(line, &cmd, table->env);
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
