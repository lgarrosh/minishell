#ifndef STRUCT_H
# define STRUCT_H

# include <unistd.h>

typedef struct s_env //переменные окружения
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	**envp;
}			t_pipex;

typedef struct s_line //строка напечатаная пользователем 
{
	int		nbr_cmd;
}				t_line;

typedef struct s_bash //вся основная тнформация программы
{
	t_env	**env_list;
	int		stop;
}				t_bash;

#endif