NAME = minishell

CC = cc

FLAGS = -Wall -Werror -Wextra -g

LIBFT_PATH = lib/libft
SRCS_PATH = 

LIBFT_FLAG = -Llib/libft -lft

LIBFT = $(LIBFT_PATH)/libft.a

SRCS_fILE = exe.c\
			do_exe.c\
			cmd.c\
			exe_free.c\
			pipe.c\
			fork.c\
			cmd_utils.c\
			heredoc.c\
			fd.c\
			file_utils.c\
			buin_utils.c\
			buin_pwd_env_cd.c\
			env.c\
			buin_unset.c\
			buin_export.c
	 

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_fILE))

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(PRINTF) $(NAME)

$(LIBFT): 
	make -C $(LIBFT_PATH)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -lreadline $(LIBFT_FLAG) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS) $(LIBFT_PATH)/*.o

fclean: clean
	rm -rf $(NAME) $(LIBFT_PATH)/*.a

re: fclean all

test:
	gcc test.c $(LIBFT_PATH)/*.c

.PHONY: clean fclean all re