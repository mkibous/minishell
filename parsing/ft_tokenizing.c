/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:44:32 by mkibous           #+#    #+#             */
/*   Updated: 2024/05/28 14:37:43 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	word_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			count++;
		}
		i += len(str + i);
	}
	return (count);
}

void	env(char **str, t_table *table, t_vars *vars)
{
	char	*tmp;
	char	*tmp2;
	char	*env;
	char	**envp;

	envp = env_copy(table->env);
	tmp = ft_substr(*str, 0, len(*str));
	tmp2 = ft_substr(*str, len(*str), ft_strlen(*str));
	vars->tmp = tmp2;
	env = put_env(tmp, envp, table, vars);
	if (ft_strncmp(env, "$", 1) == 0)
		vars->exp = 1;
	vars->env = word_count(env);
	free(tmp);
	free(*str);
	*str = ft_strjoin(env, tmp2);
	free(tmp2);
	free(env);
	ft_free(envp);
}

char	*ft_list_content(char **str, t_elem **elem, int *i, t_vars *vars)
{
	char	*content;
	int		*l;

	l = vars->len;
	(*l) = len(*str);
	if (vars->exp == 1)
		(*l) = 1;
	content = (char *)malloc((*l) + 1);
	if (content == NULL)
		return (NULL);
	if (ft_lstlast(*elem) && ((*str[(*i)] == '"'
				&& ft_lstlast(*elem)->content[0] == '"')
			|| (*str[(*i)] == '\'' && ft_lstlast(*elem)->content[0] == '\'')))
	{
		ft_lstadd_back(elem, ft_lstnew(ft_strdup("")));
		ft_lstlast(*elem)->state = IN_DQUOTE;
		ft_lstlast(*elem)->type = WORD;
	}
	while ((*i) < (*l))
		(1) && (content[(*i)] = (*str)[(*i)], (*i)++);
	content[(*i)] = '\0';
	return (content);
}

int	ft_listing(char **str, t_elem **elem, t_table *table, t_vars *vars)
{
	int		i;
	int		l;
	char	*content;
	char	*tmp;
	char	*tmp2;

	i = 0;
	(1) && (vars->exp = 0, vars->len = &l);
	tmp = ft_substr(*str, 0, vars->i);
	tmp2 = ft_substr(*str, vars->i, ft_strlen(*str));
	free(*str);
	*str = ft_strdup(tmp2);
	free(tmp2);
	while ((*str)[i] == '$' && vars->q == 0 && vars->redir == 0
			&& vars->env == 0)
		env(str, table, vars);
	content = ft_list_content(str, elem, &i, vars);
	ft_lstadd_back(elem, ft_lstnew(content));
	tmp2 = ft_strjoin(tmp, *str);
	free(*str);
	*str = ft_strdup(tmp2);
	free(tmp2);
	free(tmp);
	return (l);
}
