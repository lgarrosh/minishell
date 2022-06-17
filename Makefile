# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arman <arman@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 17:42:40 by preed             #+#    #+#              #
#    Updated: 2022/06/18 02:23:50 by arman            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
FLAGS		= -Wall -Wextra -Werror

LIBFT		= libft/libft.a
INC			= includes/
HEADER		= minishell.h
HEADERS		= $(addprefix $(INC), $(HEADER))

LIB_DIR		= libft/
GNL_D		= gnl/
SRC_D		= src/
OBJ_D		= obj/

SRC_GNL_F	=	$(addprefix gnl/, $(GNL))

SRC_F 		=	$(addprefix src/main/, $(MAIN)) \
				$(addprefix src/env/, $(ENV)) \
				$(addprefix src/execution/, $(EXEC)) \
				$(addprefix src/tools/, $(TOOLS)) \
				$(addprefix src/parser/, $(PARSER)) \

GNL			= get_next_line.c

MAIN		= main.c

ENV			= env.c env_oper.c

EXEC		= executive.c

TOOLS		= free.c init.c error.c

PARSER		= parser.c

OBJ_F 		=	$(subst $(SRC_D),$(OBJ_D),$(SRC_F:%.c=%.o)) 

OBJ_GNL_F 	=	$(addprefix obj/, $(SRC_GNL_F:%.c=%.o))

$(OBJ_D)%.o: $(SRC_D)%.c
	$(CC) $(FLAGS) -c $< -o $@  -I$(INC) -I$(GNL_D) -I$(LIB_DIR)$(INC)

$(OBJ_D)$(GNL_D)%.o: $(GNL_D)%.c
	$(CC) $(FLAGS) -c $< -o $@  -I$(INC) -I$(GNL_D) -I$(LIB_DIR)$(INC)

.PHONY: all clean fclean re

all: makelib $(NAME)

$(OBJ_D):
		@mkdir -p $@
		@mkdir -p $(addprefix $@/, main env execution tools parser gnl)

$(NAME): $(OBJ_D) $(OBJ_F) $(OBJ_GNL_F) $(LIBFT) $(HEADERS) Makefile
	$(CC) $(FLAGS) $(OBJ_F) $(OBJ_GNL_F) -o $(NAME) $(LIBFT) -I$(INC)

makelib:
	@make -C $(LIB_DIR) bonus --no-print-directory

clean:
	@make -C $(LIB_DIR) clean --no-print-directory
	rm -rfv $(OBJ_D)

fclean: clean
	rm -rfv $(NAME) $(LIBFT)

re: fclean all
