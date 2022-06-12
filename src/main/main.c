/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:54:56 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/06/12 18:08:27 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char **env)
{
	(void)env;
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	minishell(env);
	return (0);
}
