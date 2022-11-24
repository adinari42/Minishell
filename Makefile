# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slakner <slakner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/29 16:24:13 by adinari           #+#    #+#              #
#    Updated: 2022/11/24 18:21:44 by slakner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \
		signals.c \
		tokens.c \
		ltokens.c \
		expand.c \
		quotes.c \
		parse.c \
		exec.c \
		command.c \
		builtins.c \
		expandvalue.c \
		free.c \
		env.c \
		init.c \
		dlist.c \
		exit.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		execute_line.c
# expand.c

ODIR	= obj
OBJS    = $(addprefix $(ODIR)/, $(SRCS:.c=.o))
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -O0 -g3
IFLAGS	= -Iincludes -I$(LIBFTHEADERS)
LIBFTDIR = libft
LIBFTOBJS = ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_strlen.o ft_memset.o ft_bzero.o ft_memcpy.o ft_memmove.o ft_strlcpy.o ft_strlcat.o ft_toupper.o ft_tolower.o ft_strchr.o ft_strrchr.o ft_strncmp.o ft_memchr.o ft_memcmp.o ft_strnstr.o ft_atoi.o ft_calloc.o ft_strdup.o ft_substr.o ft_strjoin.o ft_strtrim.o ft_split.o ft_itoa.o ft_strmapi.o ft_striteri.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o
LIBFT	= libft.a
LFLAGS	= -L$(LIBFTDIR) -lft -lreadline
LIBFTHEADERS = $(LIBFTDIR)/libft.h 

all: $(NAME)
			
$(NAME): $(OBJS) $(LIBFTDIR)/$(LIBFT)
	$(CC) $(CFLAGS) -I$(LIBFTHEADERS) $(OBJS) $(LFLAGS) $(IFLAGS)  -o $(NAME)

print-%: 
	@echo $* = $($*)

$(ODIR):
	mkdir -p $(ODIR)
	mkdir -p $(ODIR)/gnl

$(ODIR)/%.o: %.c $(ODIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

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

debugmain: $(OBJS) 
	$(CC) $(CFLAGS) -O0 -g3 $(OBJS)  $(LFLAGS) -o $(NAME) -fsanitize=address

.PHONY: libft

debug: $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) -O0 -g3 $(OBJS) -I$(LIBFTHEADERS) $(LFLAGS) -o $(NAME) -fsanitize=address $(LEAKFLAGS)
