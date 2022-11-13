# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slakner <slakner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/29 16:24:13 by adinari           #+#    #+#              #
#    Updated: 2022/11/13 23:21:23 by slakner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main.c \
		signals.c \
		tokens.c \
		llist.c

OBJECTS = $(FILES:.c=.o)

CC = @gcc

FLAGS = -Wall -Werror -Wextra
all: $(NAME)

%.o:%.c
	gcc $(FLAGS) -O0 -g -c $< -o $@

LIBS = libft/libft.a

$(NAME): $(OBJECTS)
	make -C libft
	$(CC) $(OBJECTS) $(LIBS) -o $(NAME)  -lreadline 

clean:
	@cd libft && make clean
	@rm -rf $(OBJECTS)


fclean: clean
	@cd libft && make fclean
	@rm -rf $(NAME) *.o

re: fclean all

debug: $(OBJECTS)
	make -C libft
	$(CC) $(FLAGS) -O0 -g $(OBJECTS) $(LFLAGS) $(LIBS) -o $(NAME) -fsanitize=address $(LEAKFLAGS) -lreadline
