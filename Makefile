# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orantane <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/17 16:20:24 by orantane          #+#    #+#              #
#    Updated: 2019/12/13 20:17:03 by rkyttala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC_NAME = check.c main.c create_arrays.c fill_map.c solve_map.c

OBJ = $(SRC_NAME:%.c=%.o)

LIB = ../libft/libft.a

HEADER = fillit.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	make -C ../libft/
	gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIB) -I $(HEADER)

$(OBJ):
	gcc $(FLAGS) -c $(SRC_NAME)

re: fclean all

clean:
	rm -rf $(OBJ)
	make clean -C ../libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -C ../libft/

.PHONY = all re clean fclean