/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stimulation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:03:51 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/30 20:33:46 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	put_action(t_philo *p, char *text, t_mtx *ctl);

bool	start_stimulation(t_table *t)
{
	size_t	idx;
	t_philo	*p;

	idx = 0;
	t->since_start = get_time_ms();
	while (idx < t->philo_count)
	{
		p = &t->philo[idx];
		p->since_last_meal = t->since_start;
		if (!pthread_mode(&p->thread, philo_routine, p, CREATE))
			return (false);
		idx++;
	}
	monitor_stimulation(t);
	idx = 0;
	while (idx < t->philo_count)
	{
		p = &t->philo[idx];
		if (!pthread_mode(&p->thread, NULL, NULL, JOIN))
			return (false);
		idx++;
	}
	return (true);
}

bool	set_stimulation_finished(t_philo *p, t_table *t)
{
	bool	status;

	mutex_mode(&t->control, LOCK);
	p->is_dead = (get_time_ms() - p->since_last_meal > t->time_to_die);
	if (p->is_full == true)
		t->philo_meals_count++;
	t->all_philos_are_full = (t->philo_meals_count == t->philo_count);
	status = (p->is_dead == true || t->all_philos_are_full == true);
	mutex_mode(&t->control, UNLOCK);
	return (status);
}

bool	stimulation_is_finished(t_table	*t, t_mtx *ctl)
{
	bool	status;

	mutex_mode(ctl, LOCK);
	status = t->is_finished;
	mutex_mode(ctl, UNLOCK);
	return (status);
}

void	monitor_stimulation(t_table *t)
{
	size_t	idx;
	t_philo	*p;

	while (1)
	{
		idx = 0;
		t->philo_meals_count = 0;
		while (idx < t->philo_count)
		{
			p = &t->philo[idx];
			if (set_stimulation_finished(p, t) == true)
			{
				if (p->is_dead == true)
					put_action(p, "died", &t->control);
				mutex_mode(&t->control, LOCK);
				t->is_finished = true;
				mutex_mode(&t->control, UNLOCK);
				return ;
			}
			idx++;
		}
		usleep(100);
	}
}

void	end_stimulation(t_table *t)
{
	size_t	idx;

	idx = 0;
	while (idx < t->philo_count)
	{
		if (!mutex_mode(&t->fork[idx].mutex, DESTROY))
			return ;
		idx++;
	}
	free(t->philo);
	free(t->fork);
}
