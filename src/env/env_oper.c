/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_oper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:05:24 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/06/12 18:07:20 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_env(t_env **env_list)
{
	t_env	*node;

	if (env_list)
		node = *env_list;
	else
		node = NULL;
	while (node)
	{
		printf("%s=%s\n", node->name, node->value);
		node = node->next;
	}
}

void	ft_delet_env(t_env **env_list, char *name)
{
	t_env	*tmp;
	t_env	*env;

	if (!env_list || !name)
		return ;
	env = *env_list;
	tmp = env->next;
	if (!(ft_strncmp(env->name, name, ft_strlen(name))))
	{
		ft_free_env_node(env);
		env_list = &tmp;
		return ;
	}
	while (tmp)
	{
		if (!(ft_strncmp(tmp->name, name, ft_strlen(name))))
		{
			env->next = tmp->next;
			ft_free_env_node(tmp);
			return ;
		}
		env = env->next;
		tmp = tmp->next;
	}
}

t_env	**ft_get_env(char **env)
{
	t_env	**env_stack;
	t_env	*envnode;

	envnode = ft_init_env(env);
	env_stack = &envnode;
	return (env_stack);
}
