# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adinari <adinari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/29 16:24:13 by adinari           #+#    #+#              #
#    Updated: 2022/11/20 18:34:07 by slakner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c\
		expandvalue.c \
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
		dlist.c

OBJECTS = $(FILES:.c=.o)

CC = @gcc

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o:%.c
	gcc $(FLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $(ODIR)

$(NAME): $(OBJECTS)
	@cd libft && make
	$(CC) $(OBJECTS) $(LIBS) -o $(NAME)  -lreadline 

clean:
	@cd libft && make clean
	@rm -rf $(OBJECTS)


fclean: clean
	@cd libft && make fclean
	@rm -rf $(NAME) *.o

re: fclean all