/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:05:50 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/12 15:02:31 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_llist_destroy_elem(t_llist *list, t_ll_elem *elem, t_ll_elem *prev)
{
	if (prev)
		prev->next = elem->next;
	else
		list->head = elem->next;
	if (NULL != list->key_dstr)
		list->key_dstr(elem->key);
	if (NULL != list->val_dstr)
		list->val_dstr(elem->val);
	free(elem);
	--(list->size);
}

int	llist_del(t_llist *list, const void *key)
{
	t_ll_elem	*ptr;
	t_ll_elem	*prev;

	if (!list)
		return (1);
	if (list->size == 0)
		return (0);
	ptr = list->head;
	prev = NULL;
	while (ptr)
	{
		if (list->key_cmpr(key, ptr->key) == 0)
		{
			_llist_destroy_elem(list, ptr, prev);
			return (0);
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return (0);
}

void	*llist_getval(t_llist *list, const void *key)
{
	t_ll_elem	*ptr;

	if (!list || list->size == 0)
		return (NULL);
	ptr = list->head;
	while (ptr)
	{
		if (list->key_cmpr(key, ptr->key) == 0)
			return (ptr->val);
		ptr = ptr->next;
	}
	return (NULL);
}

int	llist_haskey(t_llist *list, const void *key)
{
	t_ll_elem	*ptr;

	ptr = list->head;
	while (ptr)
	{
		if (list->key_cmpr(ptr->key, key) == 0)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}
