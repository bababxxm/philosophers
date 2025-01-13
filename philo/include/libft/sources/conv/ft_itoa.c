/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:59:33 by sklaokli          #+#    #+#             */
/*   Updated: 2024/12/17 12:17:18 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int num)
{
	char	*res;
	int		len;
	long	n;

	n = num;
	len = ft_intlen(n);
	res = (char *) malloc(len + 1);
	if (!res)
		return (NULL);
	res[len--] = '\0';
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		n = -n;
		res[0] = '-';
	}
	while (n > 0)
	{
		res[len--] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}
