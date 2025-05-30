/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:15:19 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/30 17:33:51 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		return (broadcast(PERR_NBR_NON));
	str = ft_strskip(str, WHITESPACE, true);
	if (*str != '\0')
		return (broadcast(PERR_NBR_NON));
	nbr = ft_atol(start);
	if (nbr < min || nbr > max)
		return (false);
	*ptr = (size_t)nbr;
	return (true);
}

static bool	parse_args(t_table *t, int ac, char **av)
{
	if (!parse_int(&t->philo_count, av[0], 1, MAX_PHILO))
		return (broadcast(PERR_PHI_CNT));
	if (!parse_int(&t->time_to_die, av[1], MIN_MS, MAX_MS))
		return (broadcast(PERR_TME_DIE));
	if (!parse_int(&t->time_to_eat, av[2], MIN_MS, MAX_MS))
		return (broadcast(PERR_TME_EAT));
	if (!parse_int(&t->time_to_sleep, av[3], 1, MAX_MEALS))
		return (broadcast(PERR_TME_SLP));
	if (ac != 5)
		t->meals_for_each = -1;
	else
	{
		if (!parse_int(&t->meals_for_each, av[4], 1, MAX_MS))
			return (broadcast(PERR_MLS_CNT));
	}
	return (true);
}

bool	parser(t_table *t, int ac, char **av)
{
	int	idx;

	if (ac != 4 && ac != 5)
		return (broadcast(PERR_ARG_INV));
	idx = 0;
	while (idx < ac)
	{
		if (av[idx][0] == '\0')
			return (broadcast(PERR_ARG_EMT));
		idx++;
	}
	if (!parse_args(t, ac, av))
		return (false);
	return (true);
}

bool	broadcast(int perrno)
{
	write(2, "philo: ", 7);
	if (perrno == PERR_ARG_NON)
		write(2, "no arguments provided", 21);
	else if (perrno == PERR_ARG_INV)
		write(2, "invalid arguments: expected 4-5 arguments", 41);
	else if (perrno == PERR_ARG_EMT)
		write(2, "empty arguments not allowed", 27);
	else if (perrno == PERR_NBR_NON)
		write(2, "non-numeric arguments not allowed", 33);
	else if (perrno == PERR_PHI_CNT)
		write(2, "invalid value for philo_count: expected 1-200 philos", 52);
	else if (perrno == PERR_TME_DIE)
		write(2, "invalid value for time_to_die: expected 60-800 ms", 49);
	else if (perrno == PERR_TME_EAT)
		write(2, "invalid value for time_to_eat: expected 60-800 ms", 49);
	else if (perrno == PERR_TME_SLP)
		write(2, "invalid value for time_to_sleep: expected 60-800 ms", 51);
	else if (perrno == PERR_MLS_CNT)
		write(2, "invalid value for meals_count: expected 1-200 meals", 51);
	else if (perrno == PERR_MTX_MDE)
		write(2, "unexpected occurs during mutex_mode", 35);
	else if (perrno == PERR_PTH_MDE)
		write(2, "unexpected occurs during pthread_mode", 37);
	return (write(2, "\n", 1), false);
}
