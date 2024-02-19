SRCS = main.c
CC = cc
CFLAGS = -Wall -Wextra 
FLAGS = -lreadline
RM = rm -f
NAME = minishell
LIBFT = libft/libft.a
PRINT = printf/libftprintf.a
OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(PRINT)
	$(CC) $(CFLAGS) $(FLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(PRINT)

$(LIBFT): ./libft/Makefile
	cd libft && make

$(PRINT): ./printf/Makefile
	cd printf && make

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(OBJ)

clean_libft:
	cd libft && make clean
	cd printf && make clean

fclean: clean fclean_libft
	$(RM) $(NAME)

fclean_libft:
	cd libft && make fclean
	cd printf && make fclean

re: fclean all