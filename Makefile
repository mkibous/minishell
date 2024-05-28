CC = cc
NAME = minishell
SRC = minishell.c ./execute/built_in_cmd.c  ./execute/Exe_file.c ./execute/execute_cmd.c\
	./parsing/ft_tokenizing.c ./parsing/lists.c ./parsing/list_cmd.c utils.c \
	./parsing/parsing.c ./parsing/env_functions.c ./parsing/echo_redir_functions.c\
	./parsing/parsing_utils.c ./parsing/count.c ./parsing/ft_tokenizing_utils.c\
	./execute/redir_functions.c ./execute/ft_export.c \
	./execute/utils_export.c ./execute/built_in_2.c ./execute/ft_unset.c \
	./execute/child_functions.c ./execute/function_herdoc.c utils_2.c \
	utils_3.c utils_4.c ./execute/utils_export_2.c ./execute/utils_export_3.c\
	./execute/utils_herdoc.c ./execute/built_in_3.c ./execute/check_export.c \
	./execute/print_utils.c double_p.c env_utils.c init_table.c

CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
HEADER = minishell.h
OBJ = $(SRC:.c=.o)
READLINE_LIB = $(shell brew --prefix readline)/lib
READLINE_INCLUDES = $(shell brew --prefix readline)/include

all: make_libft $(NAME)

make_libft:
	@cd libft && make

$(NAME): $(OBJ) 
	@echo "\033[92m√\033[0m \033[97m" $<
	@$(CC) -lreadline $(CFLAGS) -L $(READLINE_LIB) -o $(NAME) $(OBJ) $(LIBFT)

%.o : %.c  $(HEADER) $(LIBFT)
	@$(CC) $(CFLAGS) -I $(READLINE_INCLUDES) -c $< -o $@

clean:
	@cd libft && make clean
	@rm -f $(OBJ)

fclean: clean
	@cd libft && make fclean
	@echo "\033[0m \033[97mObject Full Cleaned \033[92m√"
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all push