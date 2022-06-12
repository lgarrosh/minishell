/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:37:38 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/06/12 18:36:42 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <sys/stat.h>
# include <errno.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include "../libft/includes/libft.h"
# include "get_next_line.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

//free
void	ft_free_env_stack(t_env **env);
void	ft_free_env_node(t_env *env);
//env
t_env	*ft_init_env(char **env);
void	ft_creatadd_env(t_env **env_list, char *name, char *value);
void	ft_put_env(t_env **env_list);
void	ft_delet_env(t_env **env_list, char *name);

// printf("\n\n!!!TEST!!!\n\n");

#endif