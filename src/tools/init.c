/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:25:19 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/06/15 18:19:59 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bash	*ft_init_bash(char **env)
{
	t_bash	*info;

	info = (t_bash *)ft_calloc(sizeof(t_bash), 1);
	info->env_list = ft_get_env(env);
	info->stop = 0;
	return (info);
}
