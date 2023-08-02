# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 14:31:53 by ksaelim           #+#    #+#              #
#    Updated: 2023/08/02 12:54:41 by ksaelim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS	= -Wall -Werror -Wextra

SRCS	= ft_isalpha.c \
	ft_isdigit.c \
	  ft_isalnum.c \
	  ft_isascii.c \
	  ft_isprint.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_strlen.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strncmp.c \
	  ft_strlcpy.c \
	  ft_strlcat.c \
	  ft_strdup.c \
	  ft_bzero.c \
	  ft_calloc.c \
	  ft_strnstr.c \
	  ft_memset.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_strjoin.c \
	  ft_atoi.c \
	  ft_itoa.c \
	  ft_calloc.c \
	  ft_substr.c \
	  ft_strtrim.c \
	  ft_strmapi.c \
	  ft_striteri.c \
	  ft_split.c \
	  get_next_line.c \
	  get_next_line_utils.c \
	  ft_strndup.c \
	  ft_strcmp.c \
	  ft_atol.c

BONUS_SRCS	= ft_lstsize.c \
		  ft_lstnew.c \
		  ft_lstadd_front.c \
		  ft_lstadd_back.c \
		  ft_lstlast.c \
		  ft_lstclear.c \
		  ft_lstdelone.c \
		  ft_lstiter.c \
		  ft_lstmap.c

OBJS	= $(SRCS:.c=.o)
BONUS_OBJS    = $(BONUS_SRCS:.c=.o)
NAME	= libft.a

%o : %c
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

bonus: $(BONUS_OBJS)
	ar -rcs $(NAME) $(BONUS_OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re bonus
