/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:59:11 by sklaokli          #+#    #+#             */
/*   Updated: 2025/01/13 07:28:44 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static	int	istrim(const char c, const char *set)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char	*res;
	char	*start;
	char	*end;

	if (!s || !set)
		return (0);
	start = (char *)s;
	end = start + ft_strlen(s) - 1;
	while (*start && istrim(*start, set))
		++start;
	while (*start && istrim(*end, set))
		--end;
	res = ft_substr(start, 0, end - start + 1);
	return (res);
}
