NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilibrary/libft
RM = rm -rf

SRCS = pipex.c
OBJS = $(SRCS:.c=.o)

LIBFT = library/libft/libft.a
LIB_DIR = library

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIB_DIR)/libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIB_DIR)/libft fclean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) outfile.txt

re: fclean all

.PHONY: all clean fclean re
