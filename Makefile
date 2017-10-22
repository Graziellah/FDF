# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghippoda <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/12 22:31:41 by ghippoda          #+#    #+#              #
#    Updated: 2017/02/17 18:59:30 by ghippoda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCS = ./sources/main.c ./sources/ft_creatmap.c ./sources/dessin.c \
	./sources/ft_draw.c ./sources/ft_init_param.c

FLAGS = -Wall -Wextra -Werror

FLAGS_LBX = -lmlx -framework OpenGL -framework Appkit -L./libft -lft

OBJ = ./sources/main.o ./sources/ft_creatmap.o ./sources/dessin.o \
	  ./sources/ft_draw.o ./sources/ft_init_param.o

HEADER = ./includes/

LIB = libft.a

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS_LBX) $(OBJ) -o $(NAME) 

%o: %c
	make -C libft
	gcc $(FLAGS) -I$(HEADER) -o $@ -c $<

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C libft

re: fclean all
