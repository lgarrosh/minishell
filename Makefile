# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 17:42:40 by preed             #+#    #+#              #
#    Updated: 2022/08/13 16:41:24 by lgarrosh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

# for mac
RL_DIR		= /Users/$(USER)/.brew/Cellar/readline/8.1.?

# for ubuntu
# RL_DIR		= /usr/local

CC			= cc
# for mac
CFLAGS		= -Wall -Wextra -Werror -I $(RL_DIR)/include/
FLAGS		=  $(CFLAGS) -lreadline -L $(RL_DIR)/lib/

# for ubuntu
# CFLAGS		= -Wall -Wextra -Werror
# READ_LIB	= -L$(RL_DIR)/lib/ -I$(RL_DIR)/include/ -lreadline

INC			= includes/
HEADER		= minishell.h struct.h
HEADERS		= $(addprefix $(INC), $(HEADER))

SRC_D		= src/
OBJ_D		= obj/

SRC_F 		=	$(addprefix src/main/, $(MAIN)) \
				$(addprefix src/env/, $(ENV)) \
				$(addprefix src/execution/, $(EXEC)) \
				$(addprefix src/tools/, $(TOOLS)) \
				$(addprefix src/parser/, $(PARS)) \

MAIN		= main.c

ENV			= env.c

EXEC		= executive.c builtin.c builtin2.c \
				pipeline.c subshell.c executive2.c \
				executive3.c builtin3.c heredoc.c

TOOLS		= init.c other.c other2.c other3.c \
				list.c list2.c signal.c norm_hacks.c \
				liba.c list3.c other4.c other5.c other6.c \

PARS		= lexer.c lexer2.c parce.c \
				parce2.c parce3.c parce4.c parce5.c \
				parce6.c parce7.c parce8.c parce9.c \
				parce10.c parce11.c

OBJ_F 		=	$(subst $(SRC_D),$(OBJ_D),$(SRC_F:%.c=%.o)) 

$(OBJ_D)%.o: $(SRC_D)%.c
	$(CC) $(CFLAGS) -c $< -o $@  -I$(INC)

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_D):
		@mkdir -p $@
		@mkdir -p $(addprefix $@/, main env execution parser tools)


#for mac
$(NAME): $(OBJ_D) $(OBJ_F) $(HEADERS) Makefile
	$(CC) $(FLAGS) $(OBJ_F) -o $(NAME) -I$(INC)

#for ubuntu
# $(NAME): $(OBJ_D) $(OBJ_F) $(HEADERS) Makefile
	# $(CC) $(CLAGS) $(OBJ_F) -o $(NAME) $(READ_LIB) -I$(INC)

clean:
	rm -rfv $(OBJ_D)

fclean: clean
	rm -rfv $(NAME)

re: fclean all
