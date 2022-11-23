/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:53:16 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/13 16:12:15 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prs_is_delim_token(void *tok_key)
{
	const int	k = (long)tok_key;

	return (k == LX_IF_AND || k == LX_IF_OR);
}

static int	prs_collect_tokens(t_llist *group,
				t_ll_elem **ptr, long *type, int *lvl)
{
	while (NULL != *ptr && (*ptr)->key == LX_SEP)
		*ptr = (*ptr)->next;
	while (NULL != *ptr && ((*lvl > 0 || !prs_is_delim_token((*ptr)->key))))
	{
		(*lvl) += ((long)(*ptr)->key == LX_PARN_L);
		(*lvl) -= ((long)(*ptr)->key == LX_PARN_R);
		(*type) |= (*lvl > 0) << 5;
		(*type) |= ((long)(*ptr)->key == LX_PIPE && *lvl == 0) << 6;
		if (llist_push(group, (*ptr)->key, (*ptr)->val))
			return (ft_error(1, "minishell: prs_collect_tokens", 1, 0));
		*ptr = (*ptr)->next;
	}
	return (0);
}

static int	prs_check_syntax(t_llist *groups)
{
	t_ll_elem	*ptr;
	int			mode;
	int			expected;

	expected = 0;
	ptr = groups->head;
	while (NULL != ptr)
	{
		if (expected == 0 && prs_is_delim_token(ptr->key))
			return (ft_error(1,
					"minishell: syntax error near token `||' or `&&'", 0, 258));
		else
			expected = 1;
		if (expected == 1 && prs_is_delim_token(ptr->key))
		{
			expected = 0;
			mode = (long)ptr->key;
		}
		ptr = ptr->next;
	}
	if (expected == 0)
		return (ft_error(1,
				"minishell: syntax error near token `||' or `&&'", 0, 258));
	return (0);
}

static int	prs_group(t_llist *groups, t_llist *tokens)
{
	t_ll_elem	*ptr;
	t_llist		*group;
	long		type;
	int			lvl;

	ptr = tokens->head;
	while (NULL != ptr)
	{
		group = llist_new(NULL, NULL, NULL);
		if (NULL == group)
			return (ft_error(1, "minishell: prs_group", 1, 0));
		type = PRS_SIMPLE;
		lvl = 0;
		if (prs_collect_tokens(group, &ptr, &type, &lvl))
			return (1);
		if (lvl && prs_handle_group1(group))
			return (ft_error(1,
					"minishell: syntax error near token `(' or `)'", 0, 258));
		if (prs_handle_group0(groups, group, ptr, type))
			return (1);
		if (NULL != ptr)
			ptr = ptr->next;
	}
	return (0);
}

int	parse(t_llist *tokens, t_info *info)
{
	t_llist		*groups;

	groups = llist_new(NULL, NULL, llist_free_wrapper);
	if (NULL == groups)
		return (1);
	if (prs_group(groups, tokens))
		return (prs_dstr(groups));
	if (groups->size == 0)
	{
		llist_free(groups);
		return (0);
	}
	if (prs_check_syntax(groups))
		return (prs_dstr(groups));
	if (prs_logexec(groups, info))
		return (prs_dstr(groups));
	llist_free(groups);
	return (0);
}
