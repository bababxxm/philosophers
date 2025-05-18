/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stimulation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:03:51 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/18 16:54:20 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	start_stimulation(t_table *t)
{
	size_t	idx;
	t_philo	*philo;

	idx = 0;
	t->since_start = get_time_ms();
	while (idx < t->philo_count)
	{
		philo = &t->philo[idx];
		philo->since_last_meal = t->since_start;
		if (!pthread_mode(&philo->thread, philo_routine, philo, CREATE))
			return (false);
		idx++;
	}
	idx = 0;
	while (idx < t->philo_count)
	{
		philo = &t->philo[idx];
		if (!pthread_mode(&philo->thread, NULL, NULL, JOIN))
			return (false);
		idx++;
	}
	return (true);
}

void	monitor_stimulation(t_table *t)
{
	(void)t;
	return ;
}

void	end_stimulation(t_table *t)
{
	(void)t;
	return ;
}
