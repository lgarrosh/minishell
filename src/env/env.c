/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:02:33 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/12 14:36:27 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_envp(t_llist *l, char *envp[])
{
	char			*key;
	char			*val;
	unsigned int	i;

	if (!envp || !*envp || !l)
		return (-1);
	i = 0;
	while (envp[i])
	{
		if (ft_strslice(envp[i], "=", &key, &val))
			return (ft_error(1, "minishell: ft_parse_envp", 1, 0));
		if (llist_push(l, key, val))
			return (ft_error(1, "minishell: ft_parse_envp", 1, 0));
		++i;
	}
	return (0);
}

char	**ft_compose_envp(t_llist *env)
{
	char			**envp;
	unsigned int	i;
	t_ll_elem		*ptr;

	envp = (char **)malloc(sizeof(char *) * (env->size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	ptr = env->head;
	envp[env->size] = NULL;
	while (i < env->size)
	{
		envp[i] = ft_strjoin2(ptr->key, ptr->val, '=', 1);
		if (!envp[i])
			return (_ft_strdestroy2(envp, i));
		ptr = ptr->next;
		++i;
	}
	return (envp);
}
