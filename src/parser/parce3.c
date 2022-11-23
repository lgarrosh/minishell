/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:10:31 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/13 16:12:19 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prs_handle_token2(t_ll_elem **c, t_cmd_info *info)
{
	if ((long)(*c)->key == LX_REDIR_IN || (long)(*c)->key == LX_REDIR_SOURCE)
	{
		if ((long)(*c)->key == LX_REDIR_SOURCE)
			info->flags |= CMD_INSOURCE;
		else
			info->flags &= ~CMD_INSOURCE;
		*c = prs_next_token(*c);
		if (NULL == *c || (long)(*c)->key != LX_WORD)
			return (ft_error(1, "minishell: error near `<' or `<<'", 0, 258));
		info->in_file = (*c)->val;
		return (0);
	}
	if ((long)(*c)->key == LX_REDIR_OUT || (long)(*c)->key == LX_REDIR_APPEND)
	{
		if ((long)(*c)->key == LX_REDIR_APPEND)
			info->flags |= CMD_APPEND;
		else
			info->flags &= ~CMD_APPEND;
		*c = prs_next_token(*c);
		if (NULL == *c || (long)(*c)->key != LX_WORD)
			return (ft_error(1, "minishell: error near `>' or `>>'", 0, 258));
		info->out_file = (*c)->val;
		return (0);
	}
	return (0);
}

static int	prs_handle_token(t_ll_elem **c, t_cmd_info *info, t_llist *args)
{
	if (NULL == (*c))
		return (ft_error(1, "ur bad >:(", 0, 999));
	if ((long)(*c)->key == LX_PARN_L || (long)(*c)->key == LX_PARN_R)
	{
		info->_shlvl += ((long)(*c)->key == LX_PARN_L)
			+ (-1) * ((long)(*c)->key == LX_PARN_R);
		info->flags |= CMD_SUBSHELL;
		if ((info->_shlvl == 1 && (long)(*c)->key == LX_PARN_L)
			|| (info->_shlvl == 0 && (long)(*c)->key == LX_PARN_R))
			return (0);
	}
	if ((long)(*c)->key == LX_SEP && info->_shlvl == 0)
		return (0);
	if ((info->flags & CMD_SUBSHELL)
		&& info->_shlvl == 0 && (long)(*c)->key == LX_WORD)
		return (ft_error(1,
				"minishell: unexpected token after `(subshell)'", 0, 258));
	if (((long)(*c)->key == LX_WORD
		|| info->_shlvl > 0) && llist_push(args, (*c)->key, (*c)->val))
		return (ft_error(1,
				"minishell: prs_handle_token", 1, 0));
	if (info->_shlvl > 0)
		return (0);
	return (prs_handle_token2(c, info));
}

int	prs_group_cmd(t_ll_elem *h, t_llist *cmds)
{
	t_cmd_info	*info;
	t_llist		*args;

	prs_alloc_cmd_info(&info);
	args = llist_new(NULL, NULL, NULL);
	if (!info || !args)
		return (ft_error(1, "minishell: prs_group_cmd", 1, 0));
	while (h && ((long)h->key != LX_PIPE || info->_shlvl))
	{
		if (prs_handle_token(&h, info, args))
			return (prs_group_cmd_ret1(info, args));
		h = h->next;
	}
	if ((args->size == 0 && info->out_file == NULL && info->in_file == NULL))
		return (prs_group_cmd_ret2(info, args));
	if (h == NULL || (long)h->key == LX_PIPE)
	{
		if (llist_push(cmds, args, info))
			return (prs_group_cmd_ret3(info, args));
		return (0);
	}
	llist_free(args);
	free(info);
	return (1);
}

pid_t	prs_handle_group(int type, t_llist *group, t_info *info)
{
	t_llist	*expanded;
	t_group	*cmds;
	pid_t	pid;

	pid = -1;
	expanded = prs_expand(group, info);
	if (expanded)
	{
		cmds = ft_group_new(type);
		if (NULL == cmds)
			return (-1);
		if (prs_prepare_group(expanded, cmds))
			return (prs_handle_dstr(cmds, expanded));
		if (prs_handle_heredoc(cmds))
			return (prs_handle_dstr(cmds, expanded));
		pid = executor(cmds, info);
		llist_free(expanded);
		ft_group_free(cmds);
	}
	return (pid);
}

int	prs_logexec(t_llist *groups, t_info *info)
{
	t_ll_elem	*ptr;
	int			expect;
	int			sig;
	pid_t		pid;

	expect = 0;
	ptr = groups->head;
	while (NULL != ptr)
	{
		if (expect == 0)
		{
			pid = prs_handle_group((long)ptr->key, ptr->val, info);
			if (pid < 0)
				return (1);
			if (pid > 0)
				prs_waitall(pid, &sig);
			expect = 1;
		}
		else if (prs_logexec_bonus(ptr, &expect))
			return (0);
		ptr = ptr->next;
	}
	return (0);
}
