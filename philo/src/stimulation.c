/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stimulation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:03:51 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/18 15:30:43 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_stimulation(t_table *t)
{
	// size_t	idx;

	// idx = 0;
	t->time_since_start = get_time_ms();
	// while (idx < t->philo_count)
	// {
	// 	t->philo[idx].since_last_meal = t->time_since_start;
	// 	if (!mutex_mode(&t->fork[idx].mutex, INIT))
	// 		return (false);
	// 	if (!pthread_mode(&t->philo[idx].thread, NULL, t, CREATE))
	// 		return (false);
	// 	idx++;
	// }
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
