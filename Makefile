CC = cc
NAME = minishell
SRC = minishell.c ./execute/built_in_cmd.c  ./execute/Exe_file.c ./execute/execute_cmd.c\
	./parsing/ft_tokenizing.c ./parsing/lists.c ./parsing/list_cmd.c utils.c \
	./parsing/parsing.c ./parsing/env_functions.c ./parsing/echo_redir_functions.c\
	./parsing/parsing_utils.c\
	./execute/redir_functions.c ./execute/ft_export.c \
	./execute/utils_export.c ./execute/built_in_2.c ./execute/ft_unset.c \
	./execute/child_functions.c ./execute/function_herdoc.c

CFLAGS = -Wall -Wextra -g 
LIBFT = libft/libft.a
OBJ = $(SRC:.c=.o)
READLINE_LIB = $(shell brew --prefix readline)/lib
READLINE_INCLUDES = $(shell brew --prefix readline)/include

all: $(NAME) clean

$(NAME): $(OBJ) $(LIBFT)
	@echo "\033[92m√\033[0m \033[97m" $<
	@$(CC) -lreadline $(CFLAGS) -L $(READLINE_LIB) -o $(NAME) $(OBJ) $(LIBFT)

%.o : %.c
	@$(CC) $(CFLAGS) -I $(READLINE_INCLUDES) -c $< -o $@
$(LIBFT): 
	@cd libft && make

clean:
	@cd libft && make clean
	@rm -f $(OBJ)

fclean: clean
	@cd libft && make fclean
	@echo "\033[0m \033[97mObject Full Cleaned \033[92m√"
	@rm -f $(NAME)

re: fclean all

push:
	@read -p "Enter commit message: " commit_message; \
	git add .; \
	git commit -m "$$commit_message"; \
	git push;

pull:
	@git stash
	@git pull
	@git stash pop
.PHONY: clean fclean re all push