/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce11.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:20:02 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/13 16:12:46 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prs_only_empty_var(t_llist *str, char **word, t_expi *ei)
{
	t_ll_elem	*h;

	if (ei->size == 0)
	{
		h = str->head;
		while (h)
		{
			if ((long)h->key != LX_WORD)
				return ;
			h = h->next;
		}
		free(*word);
		*word = NULL;
	}
}
