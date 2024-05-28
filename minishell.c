/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:24:57 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/28 13:38:29 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (!g_status || g_status == 5)
		{
			g_status = 5;
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_status == 2 || g_status == 4)
		{
			g_status = 1;
			printf("\n");
		}
	}
	if (signum == SIGQUIT)
	{
		if (g_status == 2)
		{
			g_status = 4;
			printf("Quit: 3\n");
		}
	}
}

void	ft_free_elem(t_elem **elem)
{
	t_elem	*tmp;
	t_elem	*tmp2;

	tmp = *elem;
	while (tmp)
	{
		if (tmp->content)
			free(tmp->content);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*elem = NULL;
}

void	ft_cmd_free(t_cmd **cmd)
{
	t_elem	*tmp;
	t_cmd	*tmp_cmd;

	tmp = NULL;
	if ((*cmd))
		ft_free_elem(&(*cmd)->elem);
	while ((*cmd))
	{
		if ((*cmd)->cmd)
			free((*cmd)->cmd);
		if ((*cmd)->argv)
			ft_free((*cmd)->argv);
		if ((*cmd)->file)
			ft_free((*cmd)->file);
		if ((*cmd)->redir)
			ft_free((*cmd)->redir);
		tmp_cmd = (*cmd)->next;
		free(*cmd);
		(*cmd) = tmp_cmd;
	}
	(*cmd) = NULL;
}

void	while_true(t_table *table, t_cmd *cmd, char *line)
{
	while (1)
	{
		exit_status(table, g_status);
		g_status = 0;
		line = readline(RED"➜  "RED""BOLD"minishell "RESET);
		exit_status(table, g_status);
		if (line)
		{
			add_history(line);
			if (line[0] != '\0')
				ft_parsing(line, &cmd, table);
			ft_built_in(&cmd, table);
			if (cmd)
				(1) && (table->exit_s = 0, exe_cmd(cmd, table), table->v = 0);
			if (g_status == 1)
				table->exit_s = 130;
			if (g_status == 4)
				table->exit_s = 131;
			g_status = 0;
			ft_cmd_free(&cmd);
		}
		if (!line)
			exit_print();
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	t_table	*table;
	pid_t	pid;

	line = NULL;
	if (isatty(0) == 0)
		return (0);
	(void)argc;
	(void)argv;
	cmd = NULL;
	g_status = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	rl_catch_signals = 0;
	envp = remove_old_pwd(envp);
	table = ft_init_table(envp);
	table->declare_x = alloc_env(table->env);
	table->pwd_env = getcwd(NULL, 0);
	table->pid = ft_get_pid();
	pid = table->pid;
	while_true(table, cmd, line);
}
