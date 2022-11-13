# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adinari <adinari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 21:17:31 by adinari           #+#    #+#              #
#    Updated: 2022/10/22 21:15:19 by adinari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

FILES = pipex.c\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c\
		process_utils.c\
		utils2.c\

OBJECTS = $(FILES:.c=.o)

# LIBFT = libft/libft.a

# @make -C ./libft

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o:%.c
	@gcc $(FLAGS) -c $< -o $@

LIBS = libft/libft.a

$(NAME): $(OBJECTS)
	@cd libft && make
	@gcc $(OBJECTS) $(LIBS) -o $(NAME) 

clean:
	@rm -rf $(OBJECTS)
	@cd libft && make clean

fclean: clean
	@rm -rf $(NAME) *.o
	@cd libft && make fclean

re: fclean all