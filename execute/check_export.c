/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:52:29 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/20 14:33:34 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_plus(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			count++;
		i++;
	}
	return (count);
}

int	equal_before_plus(char *str)
{
	int	i;
	int	equal;

	equal = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			equal++;
		if (str[i] == '+' && equal)
			return (1);
		i++;
	}
	return (0);
}

int	check_if_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '+')
				return (0);
		}
		i++;
	}
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	if (str[i] == '+')
	{
		if (str[i + 1] && str[i + 1] == '=')
			return (1);
	}
	return (0);
}

int	check_if_correct(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (0);
	while (str[i])
	{
		if (str[i] == '+' && str[i - 1] != '=')
			return (1);
		i++;
	}
	return (0);
}
