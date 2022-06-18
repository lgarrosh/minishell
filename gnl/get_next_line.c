/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arman <arman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:31:06 by preed             #+#    #+#             */
/*   Updated: 2022/06/18 02:23:26 by arman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	ft_error(const char *err);

static void	*ft_free(void **ch)
{
	free(*ch);
	*ch = NULL;
	return (NULL);
}

static char	*ft_read(int fd)
{
	char	*ch;
	char	*masiv;
	char	*tmp;
	int		i;

	i = read(fd, masiv = (char *)ft_calloc(1, BUFFER_SIZE + 1), BUFFER_SIZE);
	if (i < 0)
		return (ft_free((void **)&masiv));
	while (!ft_strchr(masiv, 10) && i == BUFFER_SIZE)
	{
		i = read(fd, ch = (char *)ft_calloc(1, BUFFER_SIZE + 1), BUFFER_SIZE);
		if (i < 0)
		{
			ft_free((void **)&ch);
			return (ft_free((void **)&masiv));
		}
		tmp = ft_strjoin(masiv, ch);
		ft_free((void **)&masiv);
		ft_free((void **)&ch);
		masiv = tmp;
	}
	if (ft_strchr(masiv, 10))
		*ft_strchr(masiv, 10) = 0;
	return (masiv);
}

char	*get_next_line(int fd)
{
	char		*buff;

	buff = ft_read(fd);
	if (!buff)
		return (NULL);
	return (buff);
}
