/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:25:44 by sklaokli          #+#    #+#             */
/*   Updated: 2024/12/17 12:26:22 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

long	ft_atol(const char *ptr)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while ((*ptr >= 9 && *ptr <= 13) || (*ptr == 32))
		ptr++;
	if (*ptr == '-' || *ptr == '+')
	{
		if (*ptr == '-')
			sign = -1;
		ptr++;
	}
	while (*ptr >= '0' && *ptr <= '9')
	{
		res = (res * 10) + (*ptr - '0');
		ptr++;
	}
	return (sign * res);
}
