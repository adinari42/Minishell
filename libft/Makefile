# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adinari <adinari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 21:52:25 by slakner           #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/11/14 18:34:40 by adinari          ###   ########.fr        #
=======
#    Updated: 2022/11/14 18:59:01 by slakner          ###   ########.fr        #
>>>>>>> trying tofix the makefile
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = 	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
<<<<<<< HEAD
		ft_putnbr_fd.c \
=======
		ft_putnbr_fd.c
>>>>>>> trying tofix the makefile
OBJFILES = $(SRCS:.c=.o)
BONUSSRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
BONUSOBJFILES = ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o ft_lstadd_back.o ft_lstdelone.o ft_lstclear.o ft_lstiter.o ft_lstmap.o

NAME = libft.a

all: libft.a

$(NAME): $(OBJFILES)
	ar rc libft.a $(OBJFILES)

./%.o : ./%.c
	$(CC) $(CFLAGS) -c $< -o ./$@

clean:
	rm -f $(OBJFILES) $(BONUSOBJFILES)

fclean:
	rm -f $(OBJFILES) $(BONUSOBJFILES) libft.a

bonus: $(BONUSOBJFILES)
	ar r libft.a $(BONUSOBJFILES)

re:	fclean all