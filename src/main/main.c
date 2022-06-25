/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:54:56 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/06/25 18:18:47 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char **env)
{
	t_bash	*info;

	info = ft_init_bash(env);
	main_loop(info);
}

void	main_loop(t_bash *info)
{
	char	*str;

	while (!info->stop)
	{
		write (1, "minishell > ", 12);
		str = get_next_line(0);
		printf("...%s...\n", str);
		// ft_parser(info, str);
		// execution(info);
	}
}

int	main(int argc, char **argv, char **env)
{
	pipex(argc, argv, env);
	(void)argv;
	minishell(env);
	return (0);
}