/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:29:47 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/08/12 15:30:13 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == ' '
		|| c == '\n'
		|| c == '\t'
		|| c == '\r'
		|| c == '\v'
		|| c == '\f');
}

char	*ft_substr(const char *s, unsigned long begin, unsigned long n)
{
	char			*str;
	char			fail;
	unsigned int	i;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	str[n] = '\0';
	i = 0;
	fail = 0;
	while (s && s[i] && i != begin)
		++i;
	if (i < begin)
		fail = 1;
	while (!fail && s && s[i] && (i - begin < n))
	{
		str[i - begin] = s[i];
		++i;
	}
	while (begin + n != i)
		str[i++] = '\0';
	return (str);
}

int	ft_isalnum(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

void	*ft_free_char2dem(char **arr, int m)
{
	int		i;

	if (NULL == arr)
		return (NULL);
	i = 0;
	if (m == -1)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
		return (NULL);
	}
	while (i < m)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char	**ft_malloc_char2dem(int m, int n)
{
	int		i;
	char	**arr;

	if (m == 0 || n == 0)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * m);
	if (NULL == arr)
		return (NULL);
	i = 0;
	while (i < m)
	{
		arr[i] = (char *)malloc(sizeof(char *) * n);
		if (NULL == arr[i])
			return (ft_free_char2dem(arr, i));
		++i;
	}
	return (arr);
}
