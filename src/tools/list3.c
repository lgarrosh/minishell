/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:03:00 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/12 19:04:31 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	llist_int_kcmp(const void *k1, const void *k2)
{
	if ((long)k1 == (long)k2)
		return (0);
	if ((long)k1 < (long)k2)
		return (-1);
	return (1);
}

int	llist_str_kcmp(const void *k1, const void *k2)
{
	return (ft_strcmp((const char *)k1, (const char *)k2));
}

void	llist_free_wrapper(void *llist)
{
	llist_free((t_llist *)llist);
}
