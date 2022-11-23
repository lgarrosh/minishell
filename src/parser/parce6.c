/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:13:46 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/13 16:12:25 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prs_alloc_ci(t_chunk_info **ci, unsigned int i, unsigned int j)
{
	*ci = prs_chunk_info_new(i, j);
	if (*ci == NULL)
		return (ft_error(1,
				"minishell: alloc chunk info", 1, 0));
	return (0);
}

int	prs_field_expansion_prep(t_llist *str, t_info *info,
		t_llist *chunks, t_expi *ei)
{
	t_chunk_info	*ci;
	t_ll_elem		*h;

	h = str->head;
	ci = NULL;
	while (h != NULL)
	{
		if ((long)h->key == LX_FIELD || ei->f)
		{
			if (prs_alloc_ci(&ci, 0, ft_strlen((char *)h->val)))
				return (1);
			ei->size += ci->e;
			if (llist_push(chunks, ci, h->val))
				return (prs_fecc_return(ci));
		}
		else if (prs_field_exp_collect_chunks((char *)h->val,
				info, chunks, &(ei->size)))
			return (1);
		h = h->next;
	}
	ei->f = 0;
	return (0);
}

int	prs_fecc_return(t_chunk_info *ci)
{
	free(ci);
	return (ft_error(1,
			"minishell: expand envp var", 1, 0));
}

t_llist	*prs_asterisk_expansion(const char *word)
{
	if (!ft_strcontains(word, '*'))
		return (NULL);
	if (ft_strcontains(word, '/'))
		return (NULL);
	return (prs_asterisk_expansion_pwd(word));
}

int	prs_expandable(void *key)
{
	int	k;

	k = (long)key;
	return (k == LX_WORD || k == LX_EXP_FIELD
		|| k == LX_FIELD);
}
