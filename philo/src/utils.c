/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:28:30 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/31 13:53:32 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (res < INT_MIN || res > INT_MAX)
			return (-1);
		ptr++;
	}
	return (sign * res);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strskip(char *s, char *set, bool is_in_set)
{
	if (!s)
		return (NULL);
	if (is_in_set)
	{
		while (*s && ft_strchr(set, *s))
			s++;
		return (s);
	}
	else
	{
		while (*s && !ft_strchr(set, *s))
			s++;
		return (s);
	}
}

size_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((size_t)tv.tv_sec * 1000 + (size_t)tv.tv_usec / 1000);
}

void	sleep_ms(size_t ms)
{
	size_t	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
		usleep(100);
}
