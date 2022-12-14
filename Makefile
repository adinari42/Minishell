# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adinari <adinari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/29 16:24:13 by adinari           #+#    #+#              #
#    Updated: 2022/12/31 05:33:41 by slakner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	main.c \
		signals.c \
		tokens.c \
		ltokens.c \
		quotes.c \
		parse.c \
		command.c \
		builtins.c \
		expandvalue.c \
		free.c \
		env.c \
		init.c \
		dlist.c \
		exit.c \
		execute_line.c \
		spaces.c \
		string_utils.c \
		pipes.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c\
		init_fd.c\
		init_fd_utils.c\
		builtin_helpers.c\
		env2.c\
		builtins2.c\
		error.c\
		heredoc_signals.c\
		free2.c\
		input.c\
		cmd_param.c\
		fork_and_exec.c


ODIR	= obj
OBJS    = $(addprefix $(ODIR)/, $(SRCS:.c=.o))
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
IFLAGS	= -Iincludes -I$(LIBFTDIR) -I${HOME}/.brew/opt/readline/include/
LIBFTDIR = libft
LIBFTOBJS = ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_strlen.o ft_memset.o ft_bzero.o ft_memcpy.o ft_memmove.o ft_strlcpy.o ft_strlcat.o ft_toupper.o ft_tolower.o ft_strchr.o ft_strrchr.o ft_strncmp.o ft_memchr.o ft_memcmp.o ft_strnstr.o ft_atoi.o ft_calloc.o ft_strdup.o ft_substr.o ft_strjoin.o ft_strtrim.o ft_split.o ft_itoa.o ft_strmapi.o ft_striteri.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o
LIBFT	= libft.a
LFLAGS	= -L$(LIBFTDIR) -lft -L${HOME}/.brew/opt/readline/lib -lreadline
LEAKFLAGS = -LLeakSanitizer -llsan -lc++

all: $(NAME)

# $(NAME): ${HOME}/.brew ${HOME}/.brew/opt/readline $(OBJS) $(LIBFTDIR)/$(LIBFT)
# 	$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

$(NAME): $(OBJS) $(LIBFTDIR)/$(LIBFT)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)


debug: ${HOME}/.brew ${HOME}/.brew/opt/readline $(OBJS) $(LIBFTDIR)/$(LIBFT)
	$(CC) $(CFLAGS) -g3 -O0 -fsanitize=address $(LEAKFLAGS) $(IFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

# print-%: 
# 	@echo $* = $($*)


$(ODIR)/%.o: %.c
	@mkdir -p $(ODIR)
	@mkdir -p $(ODIR)/gnl
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFTDIR)/$(LIBFT):
	make -C $(LIBFTDIR)

${HOME}/.brew:
 	@test -f ${HOME}/.brew/bin/brew && curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

${HOME}/.brew/opt/readline: 
	brew install readline
	brew link --force readline

libftclean:
	make -C $(LIBFTDIR) clean

clean:
	make -C libft clean
	rm -rf $(OBJS) $(LIBFTDIR)/$(LIBFT) $(LIBFTDIR)/$(LIBFTOBJS)

fclean:
	make -C libft fclean
	rm -rf $(OBJS) $(NAME) $(LIBFTDIR)/$(LIBFTOBJS) $(LIBFTDIR)/libft.a

re: fclean all

.PHONY: libft

