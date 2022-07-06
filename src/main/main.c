/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:54:56 by preed             #+#    #+#             */
/*   Updated: 2022/07/06 15:54:41 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char **env)
{
	t_bash	*info;

	ft_init_bash(&info, env);
	main_loop(info);
}

void	main_loop(t_bash *info)
{
	t_line	*line;

	ft_init_line(&line);
	info->line = line;
	while (!info->stop)
	{
		write (1, "minishell > ", 12);
		line->cmd_line = get_next_line(0);
		ft_parser(info);
		ft_execute(info);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pip;

	pip.envp = env;
	pip.infile = NULL;
	pip.outfile = NULL;
	pipex(argc, argv, &pip);
	minishell(env);
	return (0);
}
