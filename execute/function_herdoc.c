/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_herdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:14:53 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/28 17:27:02 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void sig_hand(int signum)
{
	if (signum == SIGINT)
	{
		exit(1);
	}
}
void ft_put_env(char **line, t_cmd *cmd)
{
	int	i;
	char	**env;
	int l;
	char *tmp;
	char *tmp2;
	char *value;

	i = 0;
	l = 0;
	if(cmd->state == IN_QUOTE || ft_strchr(*line, '$') == NULL)
		return ;
	env = env_copy(cmd->table->env);
	while ((*line)[i])
	{
		if((*line)[i] == '$')
		{
			free(cmd->elem->content);
			tmp = ft_substr((*line), 0, i);
			l = len((*line) + i);
			cmd->elem->content = ft_substr((*line), i, l);
			tmp2 = ft_substr((*line), i + l, ft_strlen((*line) + i + l));
			value = put_env(cmd->elem, env, cmd->table->exit_status);
			(*line) = ft_strjoin(tmp, value);
			(*line) = ft_strjoin((*line), tmp2);
			i += l;
		}
		if((*line)[i])
			i++;
	}
}
void	for_herdoc(t_cmd *cmd, int *fd, char *line, int red)
{
	signal(SIGINT, sig_hand);
	rl_catch_signals = 1;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strlen(line) == 0)
		{
			ft_putstr_fd(line, fd[1]);
			ft_putstr_fd("\n", fd[1]);
			free(line);
			continue ;
		}
		if (ft_strncmp(line, cmd->file[red], ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		ft_put_env(&line, cmd);
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
}

int	heredoc(t_cmd *cmd, int red)
{
	int		fd[2];
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	pipe(fd);
	for_herdoc(cmd, fd, line, red);
	close(fd[1]);
	return (fd[0]);
}
