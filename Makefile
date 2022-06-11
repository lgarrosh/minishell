NAME = minishell

LIBA_D = liba/
GNL_D = gnl/
HEAD_D = headers/
SRC_D = src/
PARSE_D = parser/
OBJ_D = obj/
EXEC_D = execution/

LIBA_LIB = $(LIBA_D)libft.a
LIBA_HEAD = $(LIBA_D)libft.h
HEADERS = $(HEAD_D)minishell.h $(HEAD_D)get_next_line.h

FLAGS = -Wall -Wextra -Werror

SRC_F = env.c free.c main.c env_oper.c
GNL_F = get_next_line.c
PARSE_F =
EXEC_F =
ALL_SRC := $(addprefix $(SRC_D), $(SRC_F) $(GNL_D)$(GNL_F) $(PARSE_F) $(EXEC_F))

OBJ_SRC = $(addprefix $(SRC_D)$(OBJ_D), $(SRC_F:.c=.o))
OBJ_GNL = $(addprefix $(SRC_D)$(OBJ_D)$(GNL_D), $(GNL_F:.c=.o))
OBJ_PARSE = $(addprefix $(SRC_D)$(OBJ_D)$(PARSE_D), $(PARSE_F:.c=.o))
OBJ_EXEC = $(addprefix $(SRC_D)$(OBJ_D)$(EXEC_D), $(EXEC_F:.c=.o))
OBJS := $(OBJ_F) $(OBJ_GNL) $(OBJ_EXEC) $(OBJ_PARSE)

all: $(NAME)

$(NAME): $(OBJ_D) $(LIBA_LIB) $(OBJS) $(HEADERS) $(LIBA_HEAD) Makefile
	cc $(FLAGS) $(OBJS) -o $(NAME) $(LIBA_LIB) -I $(HEADERS)

$(OBJ_D):
	@mkdir -p $(SRC_D)$(OBJ_D)

$(OBJS)*.o: $(ALL_SRC) $(HEAD_D)*.h
	@echo $(OBJS)
	cc $(FLAGS) -I $(HEAD_D) -I $(LIBA_HEAD) -o $@ -c $<

$(LIBA_LIB):
	@make -C $(LIBA_D) --no-print-directory

clean:
	rm -rfv $(OBJ_D)
	@make -C $(LIBA_D) clean --no-print-directory

fclean: clean
	rm -rfv $(NAME)
	@make -C $(LIBA_D) fclean --no-print-directory

re: fclean all
