NAME = pipex

CC = gcc

FLAGS = -Wall -Werror -Wextra

SRCS = pipex.c pipex_free_utils.c pipex_utils.c ft_putstr_fd.c ft_split.c ft_strdup.c ft_strjoin.c ft_strnstr.c ft_strtrim.c ft_bzero.c ft_strlen.c ft_memset.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re