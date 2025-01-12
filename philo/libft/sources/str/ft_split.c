/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:59:21 by sklaokli          #+#    #+#             */
/*   Updated: 2024/12/17 12:40:21 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_wordcount(char *s, char sep)
{
	int	wc;

	if (!s)
		return (0);
	wc = 0;
	while (*s)
	{
		if (*s != sep && (*(s + 1) == sep || *(s + 1) == '\0'))
			wc++;
		s++;
	}
	return (wc);
}

static int	ft_split_strlen(char *s, char sep)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (*s && *s != sep)
	{
		len++;
		s++;
	}
	return (len);
}

static char	*ft_split_str(char *s, int len)
{
	int		i;
	char	*res;

	if (!s)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
		res[i++] = *s++;
	res[i] = '\0';
	return (res);
}

char	**ft_split(char *s, char sep)
{
	int		len;
	int		idx;
	char	**split;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (ft_wordcount(s, sep) + 1));
	if (!split)
		return (NULL);
	idx = 0;
	while (*s)
	{
		if (*s != sep)
		{
			len = ft_split_strlen(s, sep);
			split[idx] = ft_split_str(s, len);
			if (!split[idx])
				return (ft_split_free(split), NULL);
			s += len - 1;
			idx++;
		}
		s++;
	}
	split[idx] = NULL;
	return (split);
}
