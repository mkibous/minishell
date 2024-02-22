CC = cc
NAME = minishell
SRC = minishell.c ./execute/built_in_cmd.c  ./execute/Exe_file.c ./execute/creat_shild.c\
	./parsing/ft_tokenizing.c ./parsing/lists.c ./parsing/list_cmd.c utils.c
CFLAGS = -Wall -Wextra -fsanitize=address -g
LIBFT = libft/libft.a
OBJ = $(SRC:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJ) $(LIBFT)
	@echo "\033[92m√\033[0m \033[97m" $<
	@$(CC) -lreadline $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(LIBFT): 
	cd libft && make

clean:
	@cd libft && make clean
	@rm -f $(OBJ)

fclean: clean
	@cd libft && make fclean
	@echo "\033[0m \033[97mObject Full Cleaned \033[92m√"
	@rm -f $(NAME)

re: fclean all

push:
	@git add .
	@git commit -m "Automatic commit via make push"
	@git push
