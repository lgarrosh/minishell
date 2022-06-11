/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:08:18 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/06/06 13:41:45 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/get_next_line.h"
#include "../liba/libft.h"

static void	ft_free(void **ch)
{
	free(*ch);
	*ch = NULL;
}

long int	ft_read(char **buff, long int i, int fd)
{
	char	*ch;

	while (!ft_strchr(*buff, 10) && i == BUFFER_SIZE)
	{
		ch = (char *)ft_calloc(1, BUFFER_SIZE + 1);
		i = read(fd, ch, BUFFER_SIZE);
		if (**buff == 0 && i == 0)
			i = -1;
		if (i == -1)
		{
			ft_free((void **)&ch);
			ft_free((void **)buff);
			return (-1);
		}
		*buff = ft_strjoin(buff, ch);
		ft_free((void **)&ch);
	}
	return (i);
}

char	*ft_new_buff(char *buff)
{
	char	*nb;
	int		size;
	int		i;

	size = 0;
	while (buff[size] != 10)
		size++;
	nb = (char *)ft_calloc(1, ft_strlen(buff) - size);
	if (!nb)
	{
		ft_free((void **)&buff);
		return (NULL);
	}
	i = 0;
	while (buff[i + size + 1] != 0)
	{
		nb[i] = buff[i + size + 1];
		i++;
	}
	ft_free((void **)&buff);
	return (nb);
}

char	*ft_line(char **buff)
{
	char	*line;
	size_t	size;

	size = 0;
	if (ft_strchr(buff[0], 10))
	{
		while (buff[0][size] != '\n')
			size++;
	}
	else
		size = ft_strlen(buff[0]) - 1;
	line = (char *)ft_calloc(1, size + 2);
	if (!line)
	{
		ft_free((void *)buff);
		return (NULL);
	}
	ft_strlcpy(line, *buff, size + 2);
	if (ft_strchr(buff[0], 10))
		*buff = ft_new_buff(*buff);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*buff;
	char			*ch;
	static long int	i = BUFFER_SIZE;

	if (i == -1)
		return (NULL);
	if (buff == NULL)
		buff = (char *)ft_calloc(1, BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (!ft_strchr(buff, 10) && i == BUFFER_SIZE)
		i = ft_read(&buff, i, fd);
	if (i < 0)
		return (NULL);
	if (!ft_strchr(buff, 10) && i < BUFFER_SIZE)
	{
		ch = ft_line(&buff);
		ft_free((void **)&buff);
		i = -1;
		if (*ch == 0)
			ft_free((void **)&ch);
		return (ch);
	}
	return (ft_line(&buff));
}
