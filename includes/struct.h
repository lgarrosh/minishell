/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:14:43 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/13 15:38:39 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define LX_SEP				0
# define LX_WORD			1
# define LX_PARN_L			2
# define LX_PARN_R			3
# define LX_FIELD			4
# define LX_IF_OR			5
# define LX_IF_AND			6
# define LX_REDIR_OUT		7
# define LX_REDIR_IN		8
# define LX_REDIR_APPEND	9
# define LX_REDIR_SOURCE	10
# define LX_EXP_FIELD		11
# define LX_PIPE			12
# define LX_NCONST			13

# define MINIS_PROMPT "minishell> "

# define CMD_APPEND 0b001
# define CMD_INSOURCE 0b010
# define CMD_SUBSHELL 0b100

# define PRS_SIMPLE		0b0010000
# define PRS_PIPELINE	0b1000000
# define PRS_SUBSHELL	0b0100000

int								g_exit;

typedef struct s_linked_list	t_llist;
typedef struct s_info			t_info;

typedef int						(*t_builtin_ptr)(t_llist *, t_info *);
typedef int						(*t_llist_key_comparator_ptr)(const void *k1,
					const void *k2);
typedef void					(*t_llist_key_destructor_ptr)(void *key);
typedef void					(*t_llist_val_destructor_ptr)(void *val);

struct s_info
{
	char						exit_f;
	char						envp_f;
	char						**envp;
	char						*g_exit_str;
	char						*reserved_words[7];
	t_builtin_ptr				f_ptrs[7];
	t_llist						*envp_list;
};

typedef struct s_cmd_info
{
	char	*in_file;
	char	*out_file;
	char	*delim;
	int		flags;
	int		_shlvl;
}	t_cmd_info;

typedef struct s_group
{
	int			type;
	t_llist		*cmds;
	t_llist		*files;
}	t_group;

typedef struct s_fd
{
	int		pfd[2];
	int		fds[2];
}	t_fd;

typedef struct s_expi
{
	unsigned int	size;
	int				f;
}	t_expi;

typedef struct s_llist_element
{
	void	*key;
	void	*val;
	void	*next;
}	t_ll_elem;

struct s_linked_list
{
	t_ll_elem					*head;
	t_llist_key_comparator_ptr	key_cmpr;
	t_llist_key_destructor_ptr	key_dstr;
	t_llist_val_destructor_ptr	val_dstr;
	unsigned int				size;
};

typedef struct s_chunk_info
{
	unsigned int	s;
	unsigned int	e;
}	t_chunk_info;

typedef struct s_fpack1
{
	t_chunk_info	*ci;
	unsigned int	*i;
	unsigned int	*size;
}	t_fpack1;

#endif