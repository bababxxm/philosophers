/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:15:19 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/31 13:33:24 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	broadcast(char *str);
long	ft_atol(const char *ptr);
char	*ft_strskip(char *s, char *set, bool is_in_set);

static bool	parse_int(size_t *ptr, char *str, int min, int max)
{
	long	nbr;
	char	*start;

	if (!str)
		return (false);
	str = ft_strskip(str, WHITESPACE, true);
	start = str;
	str = ft_strskip(str, "-+", true);
	str = ft_strskip(str, "0123456789", true);
	if (str == start)
		return (broadcast("non-numeric arguments not provided"));
	str = ft_strskip(str, WHITESPACE, true);
	if (*str != '\0')
		return (broadcast("non-numeric arguments not allowed"));
	nbr = ft_atol(start);
	if (nbr < min || nbr > max)
		return (false);
	*ptr = (size_t)nbr;
	return (true);
}

static bool	parse_args(t_table *t, int ac, char **av)
{
	if (!parse_int(&t->philo_count, av[0], 1, MAX_PHILO))
		return (broadcast(
				"invalid value for philo_count: expected 1-200 philos"));
	if (!parse_int(&t->time_to_die, av[1], MIN_MS, MAX_MS))
		return (broadcast(
				"invalid value for time_to_die: expected 60-800 ms"));
	if (!parse_int(&t->time_to_eat, av[2], MIN_MS, MAX_MS))
		return (broadcast(
				"invalid value for time_to_eat: expected 60-800 ms"));
	if (!parse_int(&t->time_to_sleep, av[3], 1, MAX_MS))
		return (broadcast(
				"invalid value for time_to_eat: expected 60-800 ms"));
	if (ac != 5)
		t->meals_for_each = -1;
	else
	{
		if (!parse_int(&t->meals_for_each, av[4], 1, MAX_MEALS))
			return (broadcast(
					"invalid value for meals_count: expected 1-200 meals"));
	}
	return (true);
}

bool	parser(t_table *t, int ac, char **av)
{
	int	idx;

	if (ac != 4 && ac != 5)
		return (broadcast("invalid arguments: expected 4 or 5 arguments"));
	idx = 0;
	while (idx < ac)
	{
		if (av[idx][0] == '\0')
			return (broadcast("empty arguments not allowed"));
		idx++;
	}
	if (!parse_args(t, ac, av))
		return (false);
	return (true);
}

bool	broadcast(char *str)
{
	write(2, "philo: ", 7);
	while (*str)
		write(2, str++, 1);
	write(2, "\n", 1);
	return (false);
}
