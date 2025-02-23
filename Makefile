NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = pipex.c \
		free.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) outfile.txt

re: fclean all

.PHONY: all clean fclean re
