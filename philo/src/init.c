/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:18:12 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/27 20:20:35 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Arguments:
	1. philo_count         (1 <= count <= MAX_PHILO)
	2. time_to_die         (0-800 ms)
	3. time_to_eat         (0-800 ms)
	4. time_to_sleep       (0-800 ms)
	5. meals_for_each      (optional, default = 0)
*/

bool	init_fork_and_philo(t_table *t)
{
	size_t	idx;

	idx = 0;
	while (idx < t->philo_count)
	{
		t->fork[idx].id = idx;
		if (!mutex_mode(&t->fork[idx].mutex, INIT))
			return (false);
		t->philo[idx].id = idx;
		t->philo[idx].table = t;
		t->philo[idx].meals_count = 0;
		t->philo[idx].since_last_meal = 0;
		t->philo[idx].fork[0] = idx;
		if (idx == 0)
			t->philo[idx].fork[1] = t->philo_count - 1;
		else
			t->philo[idx].fork[1] = idx - 1;
		t->philo[idx].is_full = false;
		idx++;
	}
	return (true);
}

bool	init_table(t_table *t)
{
	t->since_start = 0;
	t->is_finished = false;
	if (!mutex_mode(&t->control, INIT))
		return (false);
	t->philo = malloc(sizeof(t_philo) * t->philo_count);
	if (!t->philo)
		return (false);
	t->fork = malloc(sizeof(t_fork) * t->philo_count);
	if (!t->fork)
		return (false);
	if (!init_fork_and_philo(t))
		return (false);
	return (true);
}

bool	init(t_table *t, int ac, char **av)
{
	if (!parser(t, ac, av))
		return (false);
	if (!init_table(t))
		return (false);
	return (true);
}
