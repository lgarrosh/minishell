# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 17:42:40 by preed             #+#    #+#              #
#    Updated: 2022/07/13 14:55:46 by lgarrosh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
FLAGS		= -Wall -Wextra -Werror

LIBFT		= libft/libft.a
PIPEX		= pipex/pipex.a
INC			= includes/
HEADER		= minishell.h struct.h
HEADERS		= $(addprefix $(INC), $(HEADER))

LIB_DIR		= libft/
PIP_DIR		= pipex/
SRC_D		= src/
OBJ_D		= obj/
MAIN_D		= main

SRC_F 		= $(addprefix $(SRC_D)$(MAIN_D)/, $(MAIN))

MAIN		= minishell.c

OBJ_F 		= $(subst $(SRC_D),$(OBJ_D),$(SRC_F:%.c=%.o)) 

$(OBJ_D)%.o: $(SRC_D)%.c
	$(CC) $(FLAGS) -c $< -o $@  -I$(INC) -I$(LIB_DIR)$(INC) -I$(PIP_DIR)$(INC)

.PHONY: all clean fclean re

all: makelib $(NAME)

$(OBJ_D):
		@mkdir -p $@
		@mkdir -p $(addprefix $@/, $(MAIN_D))

$(NAME): $(OBJ_D) $(OBJ_F) $(LIBFT) $(PIPEX) $(HEADERS) Makefile
	$(CC) $(FLAGS) $(OBJ_F) -o $(NAME) $(LIBFT) $(PIPEX) -I$(INC)

makelib:
	@make -C $(LIB_DIR) --no-print-directory
	@make -C $(PIP_DIR) --no-print-directory

clean:
	@make -C $(LIB_DIR) clean --no-print-directory
	@make -C $(PIP_DIR) clean --no-print-directory
	rm -rfv $(OBJ_D)

fclean: clean
	@make -C $(LIB_DIR) fclean --no-print-directory
	@make -C $(PIP_DIR) fclean --no-print-directory
	rm -rfv $(NAME)

re: fclean all
