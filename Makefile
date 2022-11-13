# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adinari <adinari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/29 16:24:13 by adinari           #+#    #+#              #
#    Updated: 2022/11/13 19:14:29 by adinari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = main.c

OBJECTS = $(FILES:.c=.o)

CC = @gcc

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o:%.c
	gcc $(FLAGS) -c $< -o $@

LIBS = libft/libft.a

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