/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:11:23 by aitaouss          #+#    #+#             */
/*   Updated: 2024/02/22 15:56:38 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// function of cd command
void    ft_cd(t_cmd *cmd)
{
	if (cmd->argv[1] == NULL)
		cmd->argv[1] = "/Users/aitaouss";
	chdir(cmd->argv[1]);
	// printf("changed directory to %s\n", path);
}

//function of pwd command
void    ft_pwd()
{
	char    cwd[1024];
	if (!getcwd(cwd, sizeof(cwd)))
		exit(1);
	printf("%s\n", cwd);
	exit(0);
}
