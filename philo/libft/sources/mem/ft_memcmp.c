/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:26:42 by sklaokli          #+#    #+#             */
/*   Updated: 2024/12/17 12:19:49 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_memcmp(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (n == 0)
		return (0);
	while (++i < n)
	{
		if (((unsigned char *)dst)[i] != ((unsigned char *)src)[i])
			return (((unsigned char *)dst)[i] - ((unsigned char *)src)[i]);
	}
	return (0);
}
