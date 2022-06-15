/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preed <preed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:31:06 by preed             #+#    #+#             */
/*   Updated: 2021/11/29 22:27:55 by preed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*cutafter(char *line)
{
	int		i;
	int		*k;
	char	*line2;
	char	*res;

	i = 0;
	k = &i;
	line2 = count(line, k);
	if (!line2)
		return (NULL);
	res = line2;
	while (*line != '\n' && *line != '\0')
		*line2++ = *line++;
	if (i != -1)
	{
		*line2 = '\n';
		*(++line2) = '\0';
	}
	else
		*line2 = '\0';
	return (res);
}

void	cutbefore(char *buf)
{
	char	safe[BUFFER_SIZE + 1];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buf[i] != '\n')
		i++;
	i++;
	while (buf[i] != '\0')
	{
		safe[j] = buf[i];
		i++;
		j++;
	}
	ft_strlcpylen(buf, safe, j + 1);
}

char	*join(char *new, char *line, char *buf)
{
	new = ft_strjoin(line, buf);
	free(line);
	if (!new)
		return (NULL);
	return (new);
}

char	*loop(int fd, char *line, char *buf, char *new)
{
	int		j;

	line = ft_strjoin(buf, "");
	if (!line)
		return (NULL);
	while (!check(buf))
	{
		j = read(fd, buf, BUFFER_SIZE);
		if (!j)
		{
			*buf = 0;
			return (line);
		}
		buf[j] = 0;
		if (j == -1)
		{
			free(line);
			return (NULL);
		}
		new = join(new, line, buf);
		line = new;
	}
	return (new);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	static char	*line;
	static char	*new;
	static int	k;

	if (!k)
		if (read(fd, buf, BUFFER_SIZE) == -1)
			return (NULL);
	if (!check(buf))
	{
		new = loop(fd, line, buf, new);
		line = cutafter(new);
		free(new);
	}
	else
		line = cutafter(buf);
	if (buf[0] != 0)
		cutbefore(buf);
	k = -1;
	if (!ft_strlcpylen(0, line, 0))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
