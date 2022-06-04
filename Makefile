NAME = minishell

LIBA_D = liba/
HEAD_D = headers/
SRC_D = src/
OBJ_D = obj/

LIBA_LIB = $(LIBA_D)libft.a
LIBA_HEAD = $(LIBA_D)libft.h
HEADERS = $(HEAD_D)minishell.h

FLAGS = -Wall -Wextra -Werror

SRC_F = env.c free.c main.c env_oper.c
OBJ_F = $(addprefix $(OBJ_D), $(SRC_F:.c=.o))

all: $(NAME)

$(OBJ_D):
		@mkdir -p $@

$(NAME): $(OBJ_D) $(OBJ_F) $(LIBA_LIB) Makefile $(HEADERS) $(LIBA_HEAD)
	cc $(FLAGS) $(OBJ_F) -o $(NAME) $(LIBA_LIB) -I $(HEADERS)

$(OBJ_D)%.o: $(SRC_D)%.c $(HEAD_D)*.h
	cc $(FLAGS) -I $(HEAD_D) -I $(LIBA_HEAD) -o $@ -c $<

$(LIBA_LIB):
	@make -C $(LIBA_D) --no-print-directory
	@make -C $(LIBA_D) bonus --no-print-directory

clean:
	rm -rfv $(OBJ_D)
	@make -C $(LIBA_D) clean --no-print-directory

fclean: clean
	rm -rfv $(NAME)
	@make -C $(LIBA_D) fclean --no-print-directory

re: fclean all
