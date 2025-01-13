/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:59:45 by sklaokli          #+#    #+#             */
/*   Updated: 2024/12/17 12:18:15 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*res;

	i = -1;
	len = ft_strlen(s);
	if (!s)
		return (NULL);
	res = (char *) malloc(len + 1);
	if (!res)
		return (NULL);
	while (++i < len)
		res[i] = f(i, s[i]);
	res[i] = '\0';
	return (res);
}
