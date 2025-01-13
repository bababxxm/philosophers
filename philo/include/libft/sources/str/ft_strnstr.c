/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:27:19 by sklaokli          #+#    #+#             */
/*   Updated: 2025/01/13 07:28:39 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*find)
		return ((char *)str);
	if (n == 0)
		return (NULL);
	while (str[i] && i < n)
	{
		j = 0;
		while ((str[i + j] == find[j]) && str[i + j] && (i + j < n))
		{
			j++;
			if (!find[j])
				return ((char *)str + i);
		}
		i++;
	}
	return (NULL);
}
