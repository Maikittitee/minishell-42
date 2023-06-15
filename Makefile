NAME = ./exe

CC = cc

FLAGS = -Wall -Werror -Wextra -g 

LIBFT_PATH = lib/libft
SRCS_PATH = 

LIBFT_FLAG = -Llib/libft -lft

LIBFT = $(LIBFT_PATH)/libft.a

SRCS_fILE = exe.c\
			do_exe.c\
			cmd.c 
	 

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_fILE))

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(PRINTF) $(NAME)

$(LIBFT): 
	make -C $(LIBFT_PATH)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(LIBFT_FLAG) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS) $(LIBFT_PATH)/*.o

fclean: clean
	rm -rf $(NAME) $(LIBFT_PATH)/*.a

re: fclean all

.PHONY: clean fclean all re