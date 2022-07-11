# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 17:42:40 by preed             #+#    #+#              #
#    Updated: 2022/07/11 17:34:33 by lgarrosh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
FLAGS		= -Wall -Wextra -Werror

LIBFT		= libft/libft.a
INC			= includes/
HEADER		= minishell.h struct.h
HEADERS		= $(addprefix $(INC), $(HEADER))

LIB_DIR		= libft/
SRC_D		= src/
OBJ_D		= obj/

SRC_F 		=	$(addprefix src/main/, $(MAIN)) \
				$(addprefix src/env/, $(ENV)) \
				$(addprefix src/execution/, $(EXEC)) \
				$(addprefix src/tools/, $(TOOLS)) \
				$(addprefix src/parser/, $(PARSER)) \
				$(addprefix src/builtins/, $(BUILT))
				$(addprefix src/terminal/, $(BUILT))

MAIN		= main.c

OBJ_F 		=	$(subst $(SRC_D),$(OBJ_D),$(SRC_F:%.c=%.o)) 

$(OBJ_D)%.o: $(SRC_D)%.c
	$(CC) $(FLAGS) -c $< -o $@  -I$(INC) -I$(GNL_D) -I$(LIB_DIR)$(INC) -I$(PIP_DIR)$(INC)

.PHONY: all clean fclean re

all: makelib $(NAME)

$(OBJ_D):
		@mkdir -p $@
		@mkdir -p $(addprefix $@/, main)

$(NAME): $(OBJ_D) $(OBJ_F) $(LIBFT) $(HEADERS) Makefile
	$(CC) $(FLAGS) $(OBJ_F) -o $(NAME) $(LIBFT) -I$(INC)

makelib:
	@make -C $(LIB_DIR) bonus --no-print-directory

clean:
	@make -C $(LIB_DIR) clean --no-print-directory
	rm -rfv $(OBJ_D)

fclean: clean
	@make -C $(LIB_DIR) fclean --no-print-directory
	rm -rfv $(NAME)

re: fclean all
