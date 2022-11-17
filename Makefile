# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slakner <slakner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/29 16:24:13 by adinari           #+#    #+#              #
#    Updated: 2022/11/17 15:19:52 by slakner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \
		signals.c \
		tokens.c \
		llist.c \
		expand.c \
		quotes.c \
		parse.c \
		exec.c

OBJS	= $(SRCS:.c=.o)
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -O0 -g3
LIBFTDIR = libft
LIBFTOBJS = ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_strlen.o ft_memset.o ft_bzero.o ft_memcpy.o ft_memmove.o ft_strlcpy.o ft_strlcat.o ft_toupper.o ft_tolower.o ft_strchr.o ft_strrchr.o ft_strncmp.o ft_memchr.o ft_memcmp.o ft_strnstr.o ft_atoi.o ft_calloc.o ft_strdup.o ft_substr.o ft_strjoin.o ft_strtrim.o ft_split.o ft_itoa.o ft_strmapi.o ft_striteri.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o
LIBFT	= libft.a
LFLAGS	= -L$(LIBFTDIR) -lft -lreadline
LIBFTHEADERS = $(LIBFTDIR)/libft.h 

all: $(NAME)
			
$(NAME): $(OBJS) $(LIBFTDIR)/$(LIBFT)
	$(CC) $(CFLAGS) -I$(LIBFTHEADERS) $(OBJS) $(LFLAGS)  -o $(NAME)

print-%: 
	@echo $* = $($*)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFTHEADERS) -c $< -o $@

$(LIBFTDIR)/$(LIBFT):
	make -C $(LIBFTDIR)

libftclean:
	make -C $(LIBFTDIR) clean

clean:
	make -C libft clean
	rm -rf $(OBJS) $(LIBFTDIR)/$(LIBFT) $(LIBFTDIR)/$(LIBFTOBJS)

fclean:
	make -C libft fclean
	rm -rf $(OBJS) $(NAME) $(LIBFTDIR)/$(LIBFTOBJS) $(LIBFTDIR)/libft.a

re: fclean all

debugmain: $(OBJS) mlx ft_fractol.h
	$(CC) $(CFLAGS) -O0 -g3 $(OBJS)  $(LFLAGS) -o $(NAME) -fsanitize=address

.PHONY: libft

debug: $(OBJECTS)
	make -C libft
	$(CC) $(CFLAGS) -O0 -g3 $(OBJS) -I$(LIBFTHEADERS) $(LFLAGS) -o $(NAME) -fsanitize=address $(LEAKFLAGS)
