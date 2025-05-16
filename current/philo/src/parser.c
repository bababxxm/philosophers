/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:15:19 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/16 22:40:29 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *ptr);
char	*ft_strskip(char *s, char *set, bool is_in_set);

static bool	parse_int(size_t *ptr, char *str, int max)
{
	long	nbr;
	char	*start;

	if (!str)
		return (false);
	str = ft_strskip(str, WHITESPACE, true);
	if (*str == '+')
		str++;
	start = str;
	str = ft_strskip(str, "0123456789", true);
	if (str == start)
		return (false);
	str = ft_strskip(str, WHITESPACE, true);
	if (*str != '\0')
		return (false);
	nbr = ft_atol(start);
	if (nbr < 0 || nbr > max)
		return (false);
	*ptr = (size_t)nbr;
	return (true);
}

static bool	parse_args(t_table *t, int ac, char **av)
{
	if (!parse_int(&t->philo_count, av[0], MAX_PHILO))
		return (false);
	if (!parse_int(&t->time_to_die, av[1], MAX_MS))
		return (false);
	if (!parse_int(&t->time_to_eat, av[2], MAX_MS))
		return (false);
	if (!parse_int(&t->time_to_sleep, av[3], MAX_MS))
		return (false);
	if (ac != 5)
		t->meals_for_each = 0;
	else
	{
		if (!parse_int(&t->meals_for_each, av[4], MAX_MS))
			return (false);
	}
	return (true);
}

bool	parser(t_table *t, int ac, char **av)
{
	int	idx;

	if (ac != 4 && ac != 5)
		return (false);
	idx = 0;
	while (idx < ac)
	{
		if (av[idx][0] == '\0')
			return (false);
		idx++;
	}
	if (!parse_args(t, ac, av))
		return (false);
	return (true);
}
