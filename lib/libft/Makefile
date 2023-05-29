# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/31 17:25:19 by ktunchar          #+#    #+#              #
#    Updated: 2023/03/26 01:43:20 by ktunchar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memcmp.c ft_memset.c \
ft_strchr.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_memmove.c ft_memcpy.c ft_strlcat.c \
ft_putstr_fd.c ft_putchar_fd.c ft_putnbr_fd.c ft_calloc.c ft_strdup.c ft_memchr.c ft_strnstr.c ft_substr.c ft_itoa.c ft_strjoin.c \
ft_putendl_fd.c ft_split.c ft_strmapi.c ft_striteri.c ft_strtrim.c get_next_line.c get_next_line_utils.c

OBJS := $(SRCS:.c=.o)

BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstsize.c ft_lstlast.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

BONUS_OBJS = $(BONUS:%.c=%.o)

all: $(NAME)

.c.o:
	gcc -Wall -Wextra -Werror -c $< -o $(<:.c=.o)
$(NAME): $(OBJS) $(BONUS_OBJS)
	ar -rcs $(NAME) $(OBJS)
clean:
	rm -f $(OBJS) $(BONUS_OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all clean

bonus:	$(OBJS) $(BONUS_OBJS)
		ar -rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY: clean fclean all re bonus
