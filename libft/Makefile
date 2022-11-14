# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 14:47:46 by tsawe07           #+#    #+#              #
#    Updated: 2022/11/14 20:11:44 by gbertin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC=gcc
FLAGS=-Wall -Wextra -Werror
RM=rm -f
SRC=ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c	 \
	ft_memset.c  \
	ft_bzero.c   \
	ft_memcpy.c  \
	ft_memmove.c \
	ft_strdup.c  \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c  \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c  \
	ft_memcmp.c  \
	ft_strnstr.c \
	ft_atoi.c    \
	ft_calloc.c  \
	ft_substr.c  \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c   \
	ft_itoa.c    \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	get_next_line.c \
	get_next_line_utils.c

OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ)
				ar rc $(NAME) $(OBJ)
				ranlib $(NAME)
%.o: %.c 
				$(CC) -I. -o $@ -c $? $(FLAGS)

all: $(NAME)

clean:
				$(RM) $(OBJ)

fclean: clean 
				$(RM) $(NAME)

re: fclean all

.PHONY: clean all fclean re