/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:15:25 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/06/25 18:05:10 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_nl(char *str)
{
	if (str)
	{
		while (*str)
		{
			if (*str == '\n')
				return (1);
			str++;
		}
	}
	return (0);
}

char	*str_join(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	if (s1)
		while (s1[++i])
			str[i] = s1[i];
	else
		i = 0;
	if (s2)
		while (s2[++j])
			str[i + j] = s2[j];
	else
		j = 0;
	str[i + j] = '\0';
	if (s1)
		free(s1);
	return (str);
}

char	*trim_rem(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	i++;
	while (str[i + j])
	{
		str[j] = str[i + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_line(char *str)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	new_line = (char *)malloc(i + 1);
	if (!new_line)
		return (NULL);
	while (str[j] != '\n' && str[j] != '\0')
	{
		new_line[j] = str[j];
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}
