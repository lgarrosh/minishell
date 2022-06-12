# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: preed <preed@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 17:42:40 by preed             #+#    #+#              #
#    Updated: 2022/06/12 18:35:11 by preed            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= gcc
FLAGS		= -Wall -Wextra -Werror

LIBFT		= libft/libft.a
INC			= includes/
HEADER		= minishell.h
HEADERS		= $(addprefix $(INC), $(HEADER))

LIB_DIR		= libft/
SRC_D		= src/
OBJ_D		= obj/

SRC_F 		=	$(addprefix src/main/, $(MAIN)) \
				$(addprefix src/env/, $(ENV)) \
				$(addprefix src/execution/, $(EXEC)) \
				$(addprefix src/tools/, $(TOOLS)) \

MAIN		= main.c

ENV			= env.c env_oper.c

EXEC		= executive.c

TOOLS		= free.c

OBJ_F 		= $(subst $(SRC_D),$(OBJ_D),$(SRC_F:%.c=%.o))

$(OBJ_D)%.o: $(SRC_D)%.c
	$(CC) $(FLAGS) -c $< -o $@  -I$(INC)

.PHONY: all clean fclean re

all: makelib $(NAME)

$(OBJ_D):
		@mkdir -p $@
		@mkdir -p $(addprefix $@/, main env execution tools)

$(NAME): $(OBJ_D) $(OBJ_F) $(LIBFT) $(HEADERS) Makefile
	$(CC) $(FLAGS) $(OBJ_F) -o $(NAME) $(LIBFT) -I$(INC)

makelib:
	@make -C $(LIB_DIR) bonus --no-print-directory

clean:
	@make -C $(LIB_DIR) clean --no-print-directory
	rm -rfv $(OBJ_D)

fclean: clean
	rm -rfv $(NAME) $(LIBFT)

re: fclean all
