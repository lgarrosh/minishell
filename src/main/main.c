/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 12:31:06 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/13 16:01:10 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*_ft_readline(const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}

void	main_pre(t_llist **tokens, char **line, char *argv[], int argc)
{
	(void)argv;
	(void)argc;
	signal(SIGINT, handler);
	errno = 0;
	*tokens = llist_new(llist_int_kcmp, NULL, free);
	*line = _ft_readline(MINIS_PROMPT);
}

void	main_post(t_llist *tokens)
{
	llist_free(tokens);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_info	info;
	t_llist	*tokens;

	if (ft_initial(&info, envp))
		return (EXIT_FAILURE);
	while (info.exit_f)
	{
		main_pre(&tokens, &line, argv, argc);
		if (line && *line)
		{
			if (lexer(tokens, line) == 0)
				parse(tokens, &info);
			free(line);
		}
		else if (line == NULL)
			info.exit_f = 0;
		main_post(tokens);
	}
	write(STDOUT_FILENO, "exit\n", 5);
	ft_destroy(&info);
	return (g_exit);
}
