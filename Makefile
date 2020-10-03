# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/21 17:14:22 by dmetallo          #+#    #+#              #
#    Updated: 2020/09/21 17:14:27 by dmetallo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_LIB 		= libft/libft.a

HEADER_NAME		= lemin.h
NAME			= lem-in

INC_DIR 		= ./includes/
INC_LIB_FT 		= ./libft/
SRC_DIR 		= ./src/
OBJ_DIR 		= ./obj/

SRC_NAME		= dop_func.c alg.c bfs.c check_usefull.c find.c forks.c \
					link_operation.c links.c move_ants.c new_parser.c paths.c \
					utils.c room.c main.c init.c

HEADER 			= $(addprefix $(INC_DIR), $(HEADER_NAME))
SRC				= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ				= $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

CC				= gcc
FLAGS			= -Wall -Wextra -Werror
GCC_LIBFT 		= -L ./libft -lft

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(NAME_LIB) $(HEADER)
	$(CC) $(GCC_LIBFT) $(addprefix -I, $(INC_DIR)) $(OBJ) $(FLAGS) -o $(NAME) libft/libftprintf.a

$(OBJ_DIR):
	mkdir -p obj

$(NAME_LIB):
	make -C libft/

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) -c -I $(INC_DIR) -I $(INC_LIB_FT) $(FLAGS) $< -o $@

clean:
	/bin/rm -rf $(OBJ_DIR)
	make clean -C libft/

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C libft/

re: fclean all
