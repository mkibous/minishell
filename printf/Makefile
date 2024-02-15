
SRCS =	ft_hexad.c ft_printf.c ft_putchar.c ft_putnbr.c ft_putstr.c \
		ft_putu.c ft_putupx.c ft_putx.c ft_arg.c
NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra
LIBC = ar rc
RM = rm -f
OBJ = $(SRCS:.c=.o)
all: $(NAME)

$(NAME): $(OBJ)
	$(LIBC) $(NAME) $(OBJ)

%.o : %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean