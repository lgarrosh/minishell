/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:56:10 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/12 15:29:27 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *s)
{
	int		i;

	i = 0;
	while (s && s[i])
		++i;
	return (i);
}

char	*ft_strcpy(const char *s)
{
	char		*copy;
	const int	length = ft_strlen(s);
	int			i;

	if (!s)
		return (NULL);
	copy = (char *)malloc(sizeof(char) * (length + 1));
	if (copy)
	{
		i = length;
		copy[length] = '\0';
		while (i--)
			copy[i] = s[i];
	}
	return (copy);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (*s1 && *s2 && *s1 == *s2)
		s1 += (++s2 || 1);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_strslice(const char *s, const char *delim, char **a, char **b)
{
	int		j;
	int		i;

	if (!s || !delim)
		return (-1);
	j = 0;
	while (s[j] && !ft_strcontains(delim, s[j]))
		++j;
	i = j;
	*a = (char *)malloc(sizeof(char) * (j + 1));
	if (!a)
		return (1);
	while (i--)
		(*a)[i] = s[i];
	(*a)[j] = '\0';
	if (s[j] == '\0')
		*b = NULL;
	else
		*b = ft_strcpy(s + j + 1);
	if (b)
		return (0);
	free(*a);
	return (1);
}

char	*ft_strjoin2(const char *s1, const char *s2, char d, char isd)
{
	const int	size = ft_strlen(s1) + ft_strlen(s2) + 1 + (isd != 0);
	char		*str;
	int			i;

	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		str[i++] = *s1++;
	if (isd)
		str[i++] = d;
	while (s2 && *s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}
