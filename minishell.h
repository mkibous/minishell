#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <signal.h>
#include <unistd.h>
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
	HERE_DOC, //
	DREDIR_OUT,
} t_token;

typedef enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
} t_state;

typedef struct s_elem
{
	char			*content;
	int				len;
	t_token			type;
	t_state			state;
	struct s_elem   *next;
	struct s_elem   *prev;
}	t_elem;

void	ft_free(char **str);
void	ft_tokenizing(char *line);
void ft_readline(void);
t_elem	*ft_lstnew(char *content);
void	ft_lstadd_back(t_elem **lst, t_elem *new);
void	ft_lstadd_front(t_elem **lst, t_elem *new);
int	ft_lstsize(t_elem *lst);
t_elem	*ft_lstlast(t_elem *lst);

#endif