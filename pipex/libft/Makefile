# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adinari <adinari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 22:43:50 by adinari           #+#    #+#              #
#    Updated: 2022/10/24 19:46:10 by adinari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS=    ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_strchr.c ft_strdup.c \
	ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
	ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_substr.c \
	ft_tolower.c ft_toupper.c ft_strmapi.c ft_striteri.c\
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	ft_strtrim.c ft_split.c
BONUSSRC=   ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
	ft_lstmap.c

OBJS=$(SRCS:.c=.o)
BONUSOBJS=$(BONUSSRC:.c=.o)

CC = gcc -g
CFLAG = -Wall -Wextra -Werror

all: $(NAME)

%.o:%.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)

bonus : $(BONUSOBJS) $(OBJS)
	@ar rc $(NAME) $(BONUSOBJS)

clean:
	@rm -f $(OBJS) $(BONUSOBJS)

fclean: clean
	@rm -f $(NAME)

re: @fclean all
.PHONY: all clean fclean re