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

static void	ft_free(void **ch)
{
	free(*ch);
	*ch = NULL;
}

static char	*ft_read(int fd)
{
	char	*ch;
	char	*masiv;
	int		i;

	masiv = (char *)ft_calloc(1, BUFFER_SIZE + 1);
	if (!masiv)
		return (NULL);
	i = read(fd, masiv, BUFFER_SIZE);
	while (!ft_strchr(masiv, 10) && i == BUFFER_SIZE)
	{
		ch = (char *)ft_calloc(1, BUFFER_SIZE + 1);
		i = read(fd, ch, BUFFER_SIZE);
		if (i < 0)
		{
			ft_free((void **)&ch);
			ft_free((void **)&masiv);
			return (NULL);
		}
		masiv = ft_strjoin(masiv, ch);
		ft_free((void **)&ch);
	}
	return (masiv);
}

char	*get_next_line(int fd)
{
	char		*buff;

	buff = ft_read(fd);
	return (buff);
}