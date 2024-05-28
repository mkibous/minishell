/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:25:37 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/28 13:34:00 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	for_init(t_table *table)
{
	table->gar = 0;
	table->garbage = malloc(sizeof(char *) * 255);
	table->alpha = getcwd(NULL, 0);
	table->declare_x = NULL;
	table->last_arg = ft_strdup("mini");
	table->pwd_env = NULL;
	table->exit_s = 0;
	table->tmp_in = 0;
	table->tmp_out = 0;
	table->flag = 0;
	table->flag_old = 0;
	table->i = 0;
	table->check = 0;
	table->flag_unset = 0;
	table->j = 0;
	table->s = 0;
	table->l = 0;
	table->get_out = 0;
	table->v = 0;
	table->set_flag = 0;
}

void	loop_inside_init(t_table *table, char **envp, int i, int shlvl)
{
	char	*tmp;

	while (envp[i])
	{
		if (ft_strncmp(envp[i], "_=", 2) == 0)
			table->env[i] = ft_strdup("_=/usr/bin/env");
		else
		{
			if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			{
				shlvl = ft_atoi(envp[i] + 6, 0);
				shlvl++;
				table->shllvl = shlvl;
				free(envp[i]);
				tmp = ft_itoa(shlvl);
				envp[i] = ft_strjoin("SHLVL=", tmp);
				free(tmp);
			}
			table->env[i] = ft_strdup(envp[i]);
		}
		i++;
	}
	table->env[i] = NULL;
}

t_table	*ft_init_table(char **envp)
{
	t_table		*table;
	int			i;
	int			shlvl;
	char		*tmp;

	tmp = NULL;
	shlvl = 0;
	i = 0;
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->env = (char **)malloc(sizeof(char *) * (255));
	if (!table->env)
		return (NULL);
	table->red = 0;
	if (envp[0] == NULL)
		if_null(table);
	else
		loop_inside_init(table, envp, i, shlvl);
	for_init(table);
	return (table);
}

void	exit_print(void)
{
	ft_putstr_fd("exit", 1);
	ft_putstr_fd("\n", 1);
	exit(0);
}
