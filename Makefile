CC = cc
NAME = minishell
SRC = minishell.c ./execute/built_in_cmd.c  ./execute/Exe_file.c ./execute/execute_cmd.c\
	./parsing/ft_tokenizing.c ./parsing/lists.c ./parsing/list_cmd.c utils.c \
	./execute/into_parrent.c ./execute/redir_functions.c ./execute/ft_export.c \

CFLAGS = -Wall -Wextra -g
LIBFT = libft/libft.a
OBJ = $(SRC:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJ) $(LIBFT)
	@echo "\033[92m√\033[0m \033[97m" $<
	@$(CC) -lreadline $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
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