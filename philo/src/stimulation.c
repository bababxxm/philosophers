/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stimulation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:03:51 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/28 18:37:40 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_action(t_philo *p, char *text, t_mtx *ctl);

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
	bool	is_dead;

	mutex_mode(&t->control, LOCK);
	is_dead = get_time_ms() - p->since_last_meal > t->time_to_die;
	mutex_mode(&t->control, UNLOCK);
	return (is_dead == true);
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
		while (idx < t->philo_count)
		{
			p = &t->philo[idx];
			if (set_stimulation_finished(p, t) == true)
			{
				print_action(p, "is dead", &t->control);
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

bool	print_action(t_philo *p, char *text, t_mtx *ctl)
{
	size_t	now;
	size_t	timestamp;

	if (stimulation_is_finished(p->table, ctl))
		return (false);
	mutex_mode(ctl, LOCK);
	now = get_time_ms();
	if (now < p->table->since_start)
		timestamp = 0;
	else
		timestamp = now - p->table->since_start;
	printf("%zu %zu %s\n", timestamp, p->id, text);
	mutex_mode(ctl, UNLOCK);
	return (true);
}
