/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arman <arman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:54:56 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/06/15 01:35:27 by arman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char **env)
{
	t_env	**stack;

	stack = ft_get_env(env);
	ft_env_export(stack, "oleg", "lox");
	ft_env_put_name(*stack, "oleg");
	ft_env_unset(stack, "oleg");
	ft_env_put_name(*stack, "oleg");
	ft_free_env_stack(stack);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	minishell(env);
	return (0);
}
