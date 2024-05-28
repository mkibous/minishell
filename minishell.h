/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:25:10 by aitaouss          #+#    #+#             */
/*   Updated: 2024/05/28 15:38:25 by aitaouss         ###   ########.fr       */
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

# define CLEAR "\033[2J\033[H"
# define UP "\033[A"
# define DOWN "\033[B"
# define RIGHT "\033[C"
# define LEFT "\033[D"
# define BACKSPACE 127
# define CTRL_D 4

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
}	t_token;

typedef struct s_table	t_table;

typedef struct s_elem	t_elem;

typedef struct s_cmd	t_cmd;

typedef struct s_utils	t_utils;

typedef enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
}	t_state;

typedef struct s_garbage
{
	void				*str;
	void				**str2;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_cmd
{
	int				a;
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
	int				in;
	int				out;
	t_table			*table;
	t_state			state;
	t_elem			*elem;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

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
	char			*pwd_env;
	int				exit_s;
	int				tmp_in;
	int				tmp_out;
	int				red;
	char			*last_arg;
	pid_t			pid;
	int				flag;
	int				flag_old;
	char			**tmp_env;
	int				s;
	int				l;
	int				j;
	int				i;
	int				check;
	int				gar;
	int				shllvl;
	int				condition;
	int				get_out;
	int				v;
	int				set_flag;
	t_cmd			*cmd;
	t_utils			*utils;
	t_garbage		*garbage;
	int				flag_unset;
}	t_table;

typedef struct s_utils
{
	int				i;
	int				j;
	int				k;
	int				s;
	int				check;
}	t_utils;

typedef struct s_elem
{
	char			*content;
	int				len;
	t_token			type;
	t_state			state;
	pid_t			pid;
	struct s_elem	*next;
	struct s_elem	*prev;
}	t_elem;

typedef struct s_vars
{
	char	*tmp;
	bool	echo;
	bool	spaces;
	bool	exp;
	int		redir;
	int		nn;
	bool	n;
	bool	boolien;
	bool	prev_is_redir;
	int		size;
	int		q;
	int		dq;
	int		closedq;
	int		i;
	int		l;
	int		j;
	int		*len;
	int		rdrs;
	int		env;
	t_cmd	*l_cmd;
	t_elem	*last;
}	t_vars;

void	execute_cmd(t_cmd *cmd, int **fd_s, int k, t_table *table);
void	exe_cmd(t_cmd *cmd, t_table *table);
void	execute_built_in(t_cmd *cmd, int **fd, t_table *tale, int k);
int		check_access(char *command, t_cmd *cmd, t_table *table);
void	ft_putstr2d_fd(char **str, int fd);
int		len_a_eq(char *str);
int		heredoc(t_cmd *cmd, int red);
char	*add_quotes_to_string(char *str);
void	the_plus(t_cmd *cmd, int i, t_table *table);
void	the_plus_for_declare_x(t_cmd *cmd, int i, t_table *table);

void	ft_add_env(char **env, char *str, int *fd);
char	**ft_add_env2(char **env, char *str);
int		check_if_exist(char *str, char **env, int flag);
char	**join_2ds(char **join, char **to_join);
int		check_access_if(char *command, char **splited);

int		heredoc(t_cmd *cmd, int red);
void	ft_put_env(char **line, t_cmd *cmd);
void	for_put_env(char **line, t_cmd *cmd, char **env, int i);

void	ft_cd(t_cmd *cmd, t_table *table);
void	ft_pwd(t_table *table);
void	ft_env(t_table *table, t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	ft_exit(t_cmd *cmd, t_table *table);
void	ft_export(t_cmd *cmd, t_table *table);
void	ft_unset(t_cmd *cmd, t_table *table);

void	loop_child(t_cmd *cmd, int **fd, pid_t pid[]);
void	close_file_descriptor(int **fd, int k);
void	wait_all_pid(t_table *table, pid_t pid[], int k);

void	handle_redir(t_cmd *cmd, int k, int **fd);

char	**ft_split(char const *s, char c);
int		ft_strcmp(char *str, char *str2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(char *str, char *str2);
void	ft_putstr2d_fd(char **str, int fd);
int		ft_strlen_2d(char **str);
int		len_a_eq(char *str);
void	ft_putstr2d_fd(char **str, int fd);
int		ft_strlen_2d(char **str);
int		search_for_path(t_table *table);
char	**copy_the_env(char **env);
void	*freee(char **string, int index);
int		check_if_there_is_space(char *str);
char	*copy_the_str(char *str, int *s, int flag);
void	malloc_pro(char **str, char **str2, char **str3, char *argv);
void	utils_plus(t_cmd *cmd, char *tmp, char *tmp_2, char *tmp_3);
char	*get_the_argv_before_equal(char *str);
void	utils_plus_declare_x(t_cmd *cmd, char *tmp, char *tmp_2, char *tmp_3);
char	*copy_the_str_without_plus(char *str);
void	help_function(t_cmd *cmd, t_table *table, int i, int check);
void	export_declare_x(t_table *table, t_cmd *cmd);
int		ft_strlen_2d(char **str);
void	search_for_herdoc(t_cmd *cmd, int *flag, t_table *table);
void	check_if_redir_in(t_cmd *cmd, int *fd_in, t_table *table, int i);
int		is_alpha_num(char *str);
char	*get_env_pro(char *str, t_table *table);
int		search_for_home(t_table *table);
void	change_pwd(t_table *table);
int		check_if_correct(char *str);
int		check_if_valid(char *str);
int		check_if_correct(char *str);
void	free_2d(char **str);
int		search_for_home(t_table *table);
void	condition_flag_herdoc(t_cmd *cmd, int k, int **fd);
void	print_with_fd(char *str, int fd);
void	putstr_pro(char *str, char *path);
void	put_err(t_table *table, char **the_last, char *err_join, int f);
char	*copy_s_after_eq(char *str);
void	free_fd_and_pid(int **fd, pid_t *pid);
void	utils_util_dec(t_table *table, char **tmp_argv, int i, t_cmd *cmd);
void	if_in_herdoc(t_cmd *cmd);
void	sig_hand(int signum);
long	ft_atol(char *str);
void	exit_state_in_child(t_cmd *cmd, t_table *table, int number);
void	exit_help(t_cmd *cmd);
char	**loop_unset(t_table *table, char **new_env, int len, int j);

// main functions
int		ft_tablen(char **tab);
void	for_init(t_table *table);
void	loop_inside_init(t_table *table, char **envp, int i, int shlvl);
t_table	*ft_init_table(char **envp);
void	exit_print(void);
int		loop_alloc_env(char **env, int i, char **new_env, int *j);
char	**alloc_env(char **env);
char	**remove_old_pwd(char **env);
void	if_null(t_table *table);
char	**ft_strdup_2d(char **str);
void	ft_built_in(t_cmd **cmd, t_table *table);
char	**the_twode(char **twode);
pid_t	ft_get_pid(void);
void	sort_double_pointer_2(char **array, int size);
void	put_and_exit(t_table *table, t_cmd *cmd, char *path, int flag);

void	sort_double_pointer_2(char **array, int size);
void	sig_handler(int signum);
void	ft_free(char **str);
void	ft_escape(t_elem *elem);
void	ft_parsing(char *line, t_cmd **cmd, t_table *table);
t_elem	*ft_lstnew(char *content);
void	ft_lstadd_back(t_elem **lst, t_elem *new);
t_elem	*ft_lstlast(t_elem *lst);
t_cmd	*ft_lstnew_cmd(char *content);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_state(char **line, t_vars *vars, t_elem **elem, t_table *table);
void	ft_token(t_elem *elem);
int		ft_else_token(t_elem *elem);
int		ft_listing(char **str, t_elem **elem, t_table *table, t_vars *vars);
char	*put_env(char *content, char **env, t_table *table, t_vars *vars);
int		ft_count_env(char **env);
int		env_len(char *str);
char	**env_copy(char **envp);
int		ft_comp_n(char *str);
void	ft_count_echo_spaces(t_vars *vars, t_elem *elem);
void	echo_spaces(t_vars *vars, t_elem *elem);
void	fill_redir_file(t_elem *elem, t_vars *vars, t_cmd **cmd);
void	ft_allocate_redir(t_elem *elem, t_vars *vars, t_cmd **cmd);
int		ft_chek_quotes(t_elem *elem, int *b, int *Q);
int		chek_prev(t_elem *elem);
int		ft_chek(t_elem *elem);
void	ft_join(t_elem *elem);
int		len(char *str);
int		ft_count_argv(t_elem *elem, int *redirs, int rdr);
void	get_cmd(t_elem *elem, t_vars *vars, t_cmd **cmd);
void	ft_cmd(t_cmd **cmd, t_elem *elem, t_table *table);
void	elem_free(t_elem *elem);
void	ft_cmd_free(t_cmd **cmd);
void	ft_free_elem(t_elem **elem);
char	*ft_list_content(char **str, t_elem **elem, int *i, t_vars *vars);
void	last_arg(t_cmd *cmd, t_table *table);
void	ft_newstate(t_elem **elem, t_elem **tmp);
void	exit_status(t_table *table, int status);
#endif