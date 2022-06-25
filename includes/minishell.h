/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:37:38 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/06/25 18:14:41 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdio.h>
// # include <sys/stat.h>
// # include <errno.h>
// # include <termios.h>
// # include <term.h>
// # include <curses.h>
// # include <termcap.h>
// # include <sys/ioctl.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_env //переменные окружения
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_pipex
{
	pid_t	*pid;
	int		*pipe;
	int		infile;
	int		outfile;
	int		nbr_cmd;
	char	**commands;
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

// pipex
int		pipex(int argc, char *argv[], char *envp[]);

//main
void	minishell(char **env);
void	main_loop(t_bash *info); //основной цикл программы
//free
void	ft_free_env_stack(t_env **env);
void	ft_free_env_node(t_env *env);
//env
t_env	**ft_get_env(char **env);
t_env	*ft_env_init(char **env);
void	ft_env_export(t_env **env_list, char *name, char *value);
void	ft_env_put(t_env **env_list);
void	ft_env_unset(t_env **env_list, char *name);
void	ft_env_put_name(t_env *env, char *name);
t_env	*ft_if_name_in_env(t_env **stack, char *name);
//init
t_bash	*ft_init_bash(char **env);
//error
void	ft_error(const char *err);

// printf("\n\n!!!TEST!!!\n\n");

#endif