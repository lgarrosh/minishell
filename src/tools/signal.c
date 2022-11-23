/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:51:46 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/12 19:10:41 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b\n", 5);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	handler_in_executor(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		write(2, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		(void)sig;
		write(2, "Quit: 3\n", 8);
	}
}

void	handler_in_heredoc(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	exit(130);
}
