/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkibous <mkibous@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:25:10 by aitaouss          #+#    #+#             */
/*   Updated: 2024/03/28 03:36:48 by mkibous          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H


// hello
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
	char			*pwd_env;
	int				exit_status;
	int				fd_hredoc;
	int				tmp_in;
	int				tmp_out;
	int				red;
} t_table;

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

//mkibous header
typedef struct s_cmd
{
	char			*line;
	char			*path;
	int				count_cmd;
	int				pipe;
	int				is_builtin;
	char			**redir;
	char			*diretcory;
	char			*cmd;
	int				echo_new_line;
	char			**argv;
	char			**file;
	int 			in;
	int 			out;
	t_table			*table;
	t_state			state;
	t_elem			*elem;
	struct s_cmd	*next;
	struct s_cmd	*prev;
} t_cmd;

//mkibous variables
typedef struct s_vars
{
	bool echo;
	bool spaces;
	bool redir;
	bool n;
	bool boolien;
	bool prev_is_redir;
	int size;
	int Q;
	int DQ;
	int closedQ;
	int i;
	int l;
	int j;
	int rdrs;
	t_cmd *l_cmd;
	t_elem *last;
} t_vars;


// Function For Execute
void    execute_cmd(t_cmd *cmd, int **fd_s, int k, t_table *table);
void	execute_for_cmd(t_cmd *cmd, t_table *table);
void	execute_built_in(t_cmd *cmd, int **fd, t_table *tale, int k);
int		check_access(char *command, t_cmd *cmd, t_table *table);
void	ft_putstr2d_fd(char **str, int fd);
int		ft_strlen_until_equal(char *str);
int		heredoc(t_cmd *cmd, int red);

// functions utils export
void	ft_add_env(char **env, char *str, int *fd);
char	**ft_add_env2(char **env, char *str);
int		check_if_exist(char *str, char **env, int flag);
char	**join_2ds(char **join, char **to_join);

// heredoc
int		heredoc(t_cmd *cmd, int red);

// function built-in
void	ft_cd(t_cmd *cmd, t_table *table);
void    ft_pwd(t_table *table);
void	ft_env(t_table *table);
void	ft_echo(t_cmd *cmd, t_table *table);
void	ft_exit(t_cmd *cmd, t_table *table);
void	ft_export(t_cmd *cmd, t_table *table);
void	ft_unset(t_cmd *cmd, t_table *table);

// functions child
void	loop_child(t_cmd *cmd, int **fd, t_table *table, pid_t pid[]);
void	close_file_descriptor(int **fd, int k);
void	wait_all_pid(t_table *table, pid_t pid[], int k);

//function redir
void	handle_redir(t_cmd *cmd, t_table *table, int k, int **fd);

// Utils Function
char    **ft_split(char const *s, char c);
int	    ft_strcmp(char *str, char *str2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(char *str, char *str2);
void	ft_putstr2d_fd(char **str, int fd);
int		ft_strlen_2d(char **str);
int		ft_strlen_until_equal(char *str);
void	ft_putstr2d_fd(char **str, int fd);
int		ft_strlen_2d(char **str);
int		search_for_path(t_table *table);
char	**copy_the_env(char **env);

// askari functions
void 	sig_handler(int signum);
void	ft_free(char **str);
void	ft_parsing(char *line, t_cmd **cmd, t_table *table, pid_t pid);
t_elem	*ft_lstnew(char *content);
void	ft_lstadd_back(t_elem **lst, t_elem *new);
t_elem	*ft_lstlast(t_elem *lst);
t_cmd	*ft_lstnew_cmd(char *content);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_state(char *line, t_vars *vars, t_elem **elem, pid_t pid);
void	ft_token(t_elem *elem);
int	ft_else_token(t_elem *elem);
int	ft_chek_if_escape(char c);
int	ft_listing(char *str, t_elem **elem);
char	*put_env(t_elem *elem, char **env, int last_exit);
void	ft_envr(t_elem *elem, char **env, int last_exit);
int	ft_count_env(char **env);
int	env_len(char *str);
char	**env_copy(char **envp);
int	ft_comp_n(char *str, t_elem *elem);
void	ft_count_echo_spaces(t_vars *vars, t_elem *elem);
void	echo_spaces(t_vars *vars, t_elem *elem);
void	fill_redir_file(t_elem *elem, t_vars *vars, t_cmd **cmd);
void	ft_allocate_redir(t_elem *elem, t_vars *vars);
int	ft_chek_quotes(t_elem *elem, int *b, int *Q);
int	chek_prev(t_elem *elem);
int	ft_chek(t_elem *elem);
char	*ft_get_escape(char c, t_state state);
void	ft_join(t_elem *elem);
int	len(char *str);
int	ft_count_argv(t_elem *elem, int *redirs);
void	get_cmd(t_elem *elem, t_vars *vars, t_cmd **cmd);
void	ft_cmd(t_cmd **cmd, t_elem *elem, char **env, int last_exit);
void elem_free(t_elem *elem);
//push
#endif