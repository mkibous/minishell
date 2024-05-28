/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_herdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:14:53 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/21 11:48:11 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	search_for_herdoc(t_cmd *cmd, int *flag, t_table *table)
{
	int	i;

	i = 0;
	while (cmd->redir[i])
	{
		if (ft_strncmp(cmd->redir[i], "<<", 2) == 0)
		{
			check_if_redir_in(cmd, &cmd->in, table, i);
			*flag = 1;
		}
		i++;
	}
}

void	sig_hand(int signum)
{
	extern int	g_status;

	if (signum == SIGINT || signum == SIGQUIT)
	{
		exit(1);
	}
}

void	for_put_env(char **line, t_cmd *cmd, char **env, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*value;

	while ((*line)[i])
	{
		if ((*line)[i] == '$')
		{
			free(cmd->elem->content);
			tmp = ft_substr((*line), 0, i);
			cmd->table->l = len((*line) + i);
			cmd->elem->content = ft_substr((*line), i, cmd->table->l);
			tmp2 = ft_substr((*line), i + cmd->table->l,
					ft_strlen((*line) + i + cmd->table->l));
			value = put_env(cmd->elem->content, env, cmd->table, NULL);
			(*line) = ft_strjoin(tmp, value);
			i = ft_strlen(*line);
			(*line) = ft_strjoin((*line), tmp2);
		}
		else if ((*line)[i])
			i++;
	}
}

void	for_herdoc(t_cmd *cmd, int *fd, char *line, int red)
{
	if_in_herdoc(cmd);
	while (1)
	{
		line = readline("> ");
		if (!line || (line[0] == '\0' && cmd->file[red][0] == '\0'))
			break ;
		if (ft_strlen(line) == 0)
		{
			print_with_fd(line, fd[1]);
			free(line);
			continue ;
		}
		if (ft_strncmp(line, cmd->file[red], ft_strlen(cmd->file[red])) == 0
			&& cmd->file[red][0] != '\0'
				&& ft_strlen(line) == ft_strlen(cmd->file[red]))
		{
			free(line);
			break ;
		}
		ft_put_env(&line, cmd);
		print_with_fd(line, fd[1]);
		free(line);
	}
}

int	heredoc(t_cmd *cmd, int red)
{
	int		fd[2];
	char	*line;

	line = NULL;
	pipe(fd);
	for_herdoc(cmd, fd, line, red);
	close(fd[1]);
	return (fd[0]);
}
