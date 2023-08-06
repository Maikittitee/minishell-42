NAME = minishell

INCLUDE = minishell.h

#### libft ###
LIBFT_HEAD = -I$(LIBFT_DIR)
LIBFT_DIR = libft/

### readline ###
RD_HEAD = -I$(RD_DIR)include
RD_DIR = /usr/local/Cellar/readline/8.2.1/

### lexer ###
LEXER_DIR = lexer/

LEXER_FUNCT	= valid_quote.c \
			valid_token.c \
			trim_qoute.c \
			expand.c \
			break_input.c

### parser ###
PARSER_DIR = parser/

PARSER_FUNCT = parser.c

### utils ###
UTILS_DIR = utils/

UTILS_FUNCT = skip_operator.c \
			ft_isquote.c \
			ft_isrdir.c \
			ft_isarg.c \
			ft_isspace.c \
			token.c \
			scmd.c \
			scmd2.c \
			check_var.c \
			restr.c

EXE_DIR = exe/

EXE_FUNCT = exe.c\
			do_exe.c\
			cmd.c\
			exe_free.c\
			pipe.c\
			fork.c\
			cmd_utils.c\
			heredoc.c\
			fd.c\
			fd_utils.c\
			buin_utils.c\
			buin_pwd_env_cd_exit.c\
			env.c\
			buin_unset.c\
			buin_export.c\
			var.c \
			buin_echo.c \
			error.c \
			env2.c \
			exe_utils.c\
			parentnchild.c

# mexe : mv $(EXE_FUNCT) exec
### flags ###
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
RDFLAGS = -L$(RD_DIR)lib -lreadline
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

SRCS = $(addprefix $(UTILS_DIR), $(UTILS_FUNCT)) \
		$(addprefix $(LEXER_DIR), $(LEXER_FUNCT)) \
		$(addprefix $(PARSER_DIR), $(PARSER_FUNCT)) \
		$(addprefix $(EXE_DIR), $(EXE_FUNCT)) \
		main.c \
		signal.c

CC = cc

OBJS = $(SRCS:.c=.o)

%o: %c $(INCLUDE)
	$(CC) $(CFLAGS) $(LIBFT_HEAD) $(RD_HEAD) -c $< -o $@

.PHONY: all clean fclean re val

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(RDFLAGS) -o $(NAME)

clean:
	@make fclean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

val:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes ./minishell