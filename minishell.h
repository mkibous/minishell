/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:25:10 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/07 22:13:14 by mkibous          ###   ########.fr       */
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
# define BOLD "\033[1m"

// useful define
# define CLEAR "\033[2J\033[H"
# define UP "\033[A"
# define DOWN "\033[B"
# define RIGHT "\033[C"
# define LEFT "\033[D"
# define BACKSPACE 127
# define CTRL_D 4

// Token
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

// State
typedef enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
} t_state;

// table
typedef struct s_table
{
	char			*var;
	char			**env;
	int				count_cmd;
	char			*name;
	char			*value;
	int				signe;
	char			*alpha;
	char			**declare_x;
	char			**trash;
} t_table;

//askari header
typedef struct s_cmd
{
	char			*line;
	char			*path;
	int				count_cmd;
	bool			pipe;
	bool			is_builtin;
	char			**redir;
	char			*diretcory;
	bool			env;
	char			*cmd;
	bool			echo_new_line;
	char			**argv;
	char			**file;
	struct s_cmd	*next;
	struct s_cmd	*prev;
} t_cmd;

// Linked list for the token
typedef struct s_elem
{
	char			*content;
	int				len;
	t_token			type;
	t_state			state;
	pid_t			pid;
	struct s_elem   *next;
	struct s_elem   *prev;
}	t_elem;

// Function For Execute
void    execute_cmd(t_cmd *cmd, int fd[][2], char **argv, int k);
void	execute_for_cmd(t_cmd *cmd, t_table *table);
void	execute_built_in(t_cmd *cmd, int fd[][2], t_table *tale, int k);
int		check_access(char *command, t_cmd *cmd);
void    into_parrent(t_cmd *cmd, int pid[], int k, t_table *table, char buf[]);
void	ft_putstr2d_fd(char **str, int fd);

// function built-in
void    ft_cd(t_cmd *cmd, t_table *table);
void    ft_pwd(t_cmd *cmd);
void	ft_env(t_table *table, t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	ft_exit();
void	ft_export(t_cmd *cmd, t_table *table);
void	ft_unset(t_cmd *cmd, t_table *table);

//function redir
void	redir_out_append(t_cmd *cmd, int i);
void	redir_out(t_cmd *cmd, int i);
void	redir_in(t_cmd *cmd, int i);

// Utils Function
char    **ft_split(char const *s, char c);
int	    ft_strcmp(char *str, char *str2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(char *str, char *str2);
void	ft_putstr2d_fd(char **str, int fd);
int		ft_strlen_2d(char **str);

// askari functions
void 	sig_handler(int signum);
void	ft_free(char **str);
void 	ft_tokenizing(char *line, t_cmd **cmd, char **envp, pid_t pid);
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