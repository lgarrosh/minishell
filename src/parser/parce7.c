/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:15:10 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/13 16:12:31 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prs_handle_subsh_token(t_ll_elem *ptr, t_llist *expanded)
{
	if (prs_expandable(ptr->key))
		return (llist_push(expanded, ptr->key, ft_strcpy((char *)ptr->val)));
	return (llist_push(expanded, ptr->key, ptr->val));
}

int	prs_field_expansion_free(t_llist *chunks, char **word)
{
	if (chunks)
		llist_free(chunks);
	if (*word)
		free(*word);
	return (1);
}

int	prs_field_expansion_copy(t_llist *chunks, char *word)
{
	t_ll_elem		*h;
	unsigned int	i;
	unsigned int	_i;

	h = chunks->head;
	i = 0;
	while (h != NULL)
	{
		_i = ((t_chunk_info *)h->key)->s;
		while (_i < ((t_chunk_info *)h->key)->e)
			word[i++] = ((char *)h->val)[_i++];
		h = h->next;
	}
	return (0);
}

void	prs_pattern_match_while(const char *pattern,
	const char *str, char **dp)
{
	int		i;
	int		j;
	int		strl;
	int		ptrl;

	i = 1;
	ptrl = ft_strlen(pattern);
	strl = ft_strlen(str);
	while (i < ptrl + 1)
	{
		j = 1;
		while (j < strl + 1)
		{
			if (pattern[i - 1] == '*')
				dp[i][j] = (dp[i - 1][j] || dp[i][j - 1]);
			else if (str[j - 1] == pattern[i - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = 0;
			++j;
		}
		++i;
	}
}

int	prs_aep_bool(struct dirent *dirf, const char *word)
{
	return (((word[0] == '.' && dirf->d_name[0] == '.')
			|| (word[0] != '.' && dirf->d_name[0] != '.'))
		&& prs_asterisk_pattern_matches(word, dirf->d_name));
}
