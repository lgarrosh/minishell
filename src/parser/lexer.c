/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:53:53 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/13 16:00:43 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_lx_is_special(const char c)
{
	return (c == '|'
		|| c == '>'
		|| c == '<'
		|| c == '&'
		|| c == '('
		|| c == ')');
}

static int	_lx_handle_char(t_llist *tokens, const char *line, unsigned long *i)
{
	unsigned long	t;

	if (line[*i] == '\'' || line[*i] == '\"')
	{
		if (_lx_case_quotes(tokens, line, *i, &t))
			return (ft_error(1, "minishell: lexer", 1, 0));
		if (t == 0)
			return (ft_error(1, "minishell: lexer: unclosed single or"
					" double quotes", 0, 0));
		*i += t + 1;
	}
	else if (line[*i] && _lx_is_special(line[*i]))
	{
		if (_lx_case_metachar(tokens, line, *i, &t))
			return (1);
		*i += t + 1;
	}
	else if (line[*i])
	{
		if (_lx_case_word(tokens, line, *i, &t))
			return (ft_error(1, "minishell: lexer", 1, 0));
		*i += t;
	}
	return (0);
}

int	lexer(t_llist *tokens, const char *line)
{
	unsigned long	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] && ft_isspace(line[i]) && llist_push(tokens,
				(int *)LX_SEP, NULL))
			return (ft_error(1, "minishell: lexer", 1, 0));
		while (line[i] && ft_isspace(line[i]))
			++i;
		if (_lx_handle_char(tokens, line, &i))
			return (1);
	}
	return (0);
}
