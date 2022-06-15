/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:31:02 by preed             #+#    #+#             */
/*   Updated: 2022/06/15 19:27:55 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check(char *buf)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			n++;
		i++;
	}
	return (n);
}

char	*count(char *line, int *k)
{
	int	a;

	if (!line)
		return (NULL);
	while (line[*k] != '\n' && line[*k] != '\0')
		(*k)++;
	if (line[*k] == '\n')
		return (malloc(*k + 2));
	else
	{
		a = *k;
		*k = -1;
		return (malloc(a + 1));
	}
}

size_t	ft_strlcpylen(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
	{
		if (!src)
			return (0);
		while (*src)
		{
			i++;
			src++;
		}
		return (i);
	}
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (1);
}
