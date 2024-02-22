/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:25:10 by aitaouss          #+#    #+#             */
/*   Updated: 2024/02/22 23:49:53 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <termcap.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <termios.h>
# include <stdbool.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"
# define W "\033[0;37m"

typedef enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
} t_token;

typedef enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
} t_state;

// Linked list for the cmd
// typedef struct s_cmd
// {
// 	char            *pipe;
// 	char			*cmd;
// 	char            *path;
// 	bool            is_builtin;
// 	char            *diretcory;
// 	char            *str;
// 	char			*flag;
// 	char            **argv;
// 	struct s_cmd	*next;
// }				t_cmd;

//askari header
typedef struct s_cmd
{
	char			*path;
	bool			pipe;
	bool			is_builtin;
	char			*redir;
	char			*diretcory;
	bool			env;
	char			*cmd;
	char			**argv;
	char			*file;
	struct s_cmd	*next;
	struct s_cmd	*prev;
} t_cmd;

typedef struct s_elem
{
	char			*content;
	int				len;
	t_token			type;
	t_state			state;
	struct s_elem   *next;
	struct s_elem   *prev;
}	t_elem;

void	execute_test(char *path, char *cmd, char *where);
void    ft_cd(t_cmd *cmd);
void    ft_pwd();
char    **ft_split(char const *s, char c);
int	    ft_strcmp(char *str, char *str2);
t_cmd	*get_cmd(char *cmd, char *path, bool is_builtin);
t_cmd	*the_list(char **splited);
size_t	ft_strlen(const char *s);
int		check_access(char *command, t_cmd *cmd);
// void    execute_pipeline(t_cmd *cmd);
int 	execute_part(t_cmd *cmd, char **env);
t_cmd	*list_test(void);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
void    creat_shild(t_cmd *cmd, int pipefd[2], char **argv);

// askari functions
void sig_handler(int signum);
void	ft_free(char **str);
void ft_tokenizing(char *line, t_cmd **cmd);
void ft_readline(void);
t_elem	*ft_lstnew(char *content);
void	ft_lstadd_back(t_elem **lst, t_elem *new);
void	ft_lstadd_front(t_elem **lst, t_elem *new);
int	ft_lstsize(t_elem *lst);
t_elem	*ft_lstlast(t_elem *lst);
t_cmd	*ft_lstnew_cmd(char *content);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void	ft_lstadd_front_cmd(t_cmd **lst, t_cmd *new);
int	ft_lstsize_cmd(t_cmd *lst);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);

#endif