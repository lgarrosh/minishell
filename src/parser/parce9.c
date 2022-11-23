/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:16:55 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/13 16:12:41 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prs_prepare_group(t_llist *expanded, t_group *cmds)
{
	if (cmds->type & PRS_PIPELINE)
		return (prs_group_pipe(expanded, cmds->cmds));
	return (prs_group_cmd(expanded->head, cmds->cmds));
}

int	prs_group_pipe(t_llist *expanded, t_llist *cmds)
{
	t_ll_elem	*curr;

	curr = expanded->head;
	while (curr != NULL)
	{
		if (prs_group_cmd(curr, cmds))
			return (1);
		while (curr != NULL && (long)curr->key != LX_PIPE)
			curr = curr->next;
		if (curr && curr->next == NULL)
			return (ft_error(1, "minishell: parse error near `|'", 0, 258));
		if (curr)
			curr = curr->next;
	}
	return (0);
}

void	prs_waitall(int pid, int *sig)
{
	int		pid2;

	pid2 = 1;
	while (pid2 > 0)
	{
		pid2 = waitpid(0, sig, 0);
		if (pid == pid2)
		{
			g_exit = WEXITSTATUS(*sig);
			if (WIFSIGNALED(*sig))
			{
				g_exit = WTERMSIG(*sig);
				if (g_exit != 131)
					g_exit += 128;
			}
		}
	}
}

int	prs_logexec_bonus(t_ll_elem *ptr, int *expect)
{
	if ((g_exit == 0 && ((long)ptr->key == LX_IF_OR))
		|| (g_exit != 0 && ((long)ptr->key == LX_IF_AND)))
		return (1);
	*expect = 0;
	return (0);
}

void	prs_alloc_cmd_info(t_cmd_info **info)
{
	*info = malloc(sizeof(t_cmd_info));
	if (*info == NULL)
		return ;
	(*info)->in_file = NULL;
	(*info)->out_file = NULL;
	(*info)->flags = 0;
	(*info)->_shlvl = 0;
}
