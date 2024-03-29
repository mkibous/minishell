/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:24:57 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/29 23:23:10 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// table len
int g_status = 0;
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
		free(envp[i]);
		i++;
	}
	table->env[i] = NULL;
	table->alpha = getcwd(NULL, 0);
	table->declare_x = NULL;
	table->trash = NULL;
	table->pwd_env = NULL;
	table->exit_status = 0;
	table->fd_hredoc = 0;
	table->tmp_in = 0;
	table->tmp_out = 0;
	table->red = -1;
	return (table);
}

// For signal
void sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_status == 2)
		{
			g_status = 1;
			printf("\n");
			return;
		}
		printf("\n");
        rl_on_new_line();
        rl_replace_line("", 1);
        rl_redisplay();
	}
}

// For free
void ft_cmd_free(t_cmd **cmd)
{
	t_elem	*tmp;
	t_elem	*tmp2;
	t_cmd	*tmp_cmd;

	tmp = NULL;
	if((*cmd))
		tmp = (*cmd)->elem;
	while (tmp)
	{
		if (tmp->content)
			free(tmp->content);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	while ((*cmd))
	{
		if((*cmd)->cmd)
			free((*cmd)->cmd);
		if ((*cmd)->argv)
			ft_free((*cmd)->argv);
		if((*cmd)->file)
			ft_free((*cmd)->file);
		if((*cmd)->redir)
			ft_free((*cmd)->redir);
		tmp_cmd = (*cmd)->next;
		free(*cmd);
		(*cmd) = tmp_cmd;
	}
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

pid_t ft_get_pid()
{
	pid_t pid;

	pid = 0;
	pid = fork();
	if (pid < 1)
		exit(0);
	pid--;
	return(pid); 
}

// alloc with protection
char **alloc_env(char **env)
{
	int i;
	char **new_env;
	char	*tmp;
	char	*tmp2;
	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		tmp2 = ft_strdup(env[i]);
		if (!tmp)
			return (NULL);
		tmp = ft_strjoin("declare -x ", tmp2);
		if (!tmp)
			return (free(tmp2), NULL);
		free(tmp2);
		new_env[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	f()
{
	// check leaks
	system("leaks minishell");
}
int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	t_table	*table;
	int		rr;
	char **allocation;
	pid_t pid;

	(void)argc;
	(void)argv;
	cmd = NULL;
	pid =  ft_get_pid();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	rl_catch_signals = 0;
	allocation = the_twode(envp);
	table = ft_init_table(allocation);
	table->var = "➜  minishell ";
	table->declare_x = alloc_env(table->env);
	table->pwd_env = getcwd(NULL, 0);
	while (1)
	{
		g_status = 0;
		rr = rand() % 2;
		if (rr)	
			line = readline(GREEN"➜  "RED""BOLD"minishell "RESET);
		else
			line = readline(RED"➜  "RED""BOLD"minishell "RESET);
		if(line)
		{
			add_history(line);
			if (line[0] != '\0')
				ft_parsing(line, &cmd, table, pid);
			ft_built_in(&cmd, table);
			if (cmd)
				execute_for_cmd(cmd, table);
			ft_cmd_free(&cmd);
		}
		if (!line)
		{
			ft_putstr_fd("exit", 1);
			ft_putstr_fd("\n", 1);
			exit(0);
		}
		free(line);
	}
}
