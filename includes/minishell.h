/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:37:38 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/07/06 18:53:35 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdio.h>

# include <readline/readline.h> 
# include <readline/history.h>

// # include <sys/stat.h>
// # include <errno.h>
// # include <termios.h>
// # include <term.h>
// # include <curses.h>
// # include <termcap.h>
// # include <sys/ioctl.h>

# include "libft.h"
# include "get_next_line.h"
# include "struct.h"

// pipex
int		pipex(int argc, char **argv, t_pipex *pip);
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
void	ft_init_bash(t_bash **info, char **env);
void	ft_init_line(t_line **line);
//error
void	ft_error(const char *err);
//parser
void	ft_parser(t_bash *info);
//executr
void	ft_execute(t_bash *info);
//builtins
void	ft_echo(void);
void	ft_cd(void);
void	ft_pwd(void);
void	ft_exit(void);

// printf("\n\n!!!TEST!!!\n\n");

#endif