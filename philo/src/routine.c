/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:48:06 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/31 14:43:30 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	put_action(t_philo *p, char *text, t_mtx *ctl);
bool	stimulation_is_finished(t_table	*t, t_mtx *ctl);

static void	get_forks(t_philo *p, t_mtx *ctl, int mode)
{
	t_fork	*f;

	f = p->table->fork;
	if (mode == GET_FORKS && p->id % 2 != 0)
	{
		mutex_mode(&f[p->fork[0]].mutex, LOCK);
		put_action(p, "has taken a fork", ctl);
		mutex_mode(&f[p->fork[1]].mutex, LOCK);
		put_action(p, "has taken a fork", ctl);
	}
	else if (mode == GET_FORKS && p->id % 2 == 0)
	{
		mutex_mode(&f[p->fork[1]].mutex, LOCK);
		put_action(p, "has taken a fork", ctl);
		mutex_mode(&f[p->fork[0]].mutex, LOCK);
		put_action(p, "has taken a fork", ctl);
	}
	else if (mode == RELEASE_FORKS)
	{
		mutex_mode(&f[p->fork[0]].mutex, UNLOCK);
		mutex_mode(&f[p->fork[1]].mutex, UNLOCK);
	}
}

static bool	philo_eat(t_philo *p, t_mtx *ctl)
{
	if (stimulation_is_finished(p->table, ctl))
		return (false);
	mutex_mode(ctl, LOCK);
	if (p->is_full == true || p->is_dead == true)
		return (mutex_mode(ctl, UNLOCK), false);
	mutex_mode(ctl, UNLOCK);
	if (p->id % 2 == 0)
		usleep(100);
	get_forks(p, ctl, GET_FORKS);
	mutex_mode(ctl, LOCK);
	p->since_last_meal = get_time_ms();
	mutex_mode(ctl, UNLOCK);
	put_action(p, "is eating", ctl);
	sleep_ms(p->table->time_to_eat);
	p->meals_count++;
	mutex_mode(ctl, LOCK);
	p->is_full = (p->meals_count == p->table->meals_for_each);
	mutex_mode(ctl, UNLOCK);
	get_forks(p, ctl, RELEASE_FORKS);
	return (true);
}

static bool	philo_sleep(t_philo *p, t_mtx *ctl)
{
	if (stimulation_is_finished(p->table, ctl))
		return (false);
	mutex_mode(ctl, LOCK);
	if (p->is_full == true || p->is_dead == true)
		return (mutex_mode(ctl, UNLOCK), false);
	mutex_mode(ctl, UNLOCK);
	put_action(p, "is sleeping", ctl);
	sleep_ms(p->table->time_to_sleep);
	return (true);
}

static bool	philo_think(t_philo *p, t_mtx *ctl)
{
	if (stimulation_is_finished(p->table, ctl))
		return (false);
	mutex_mode(ctl, LOCK);
	if (p->is_full == true || p->is_dead == true)
		return (mutex_mode(ctl, UNLOCK), false);
	mutex_mode(ctl, UNLOCK);
	put_action(p, "is thinking", ctl);
	sleep_ms(2 * p->table->time_to_eat - p->table->time_to_sleep);
	return (true);
}

void	*philo_routine(void *params)
{
	t_philo	*p;
	t_table	*t;

	p = (t_philo *)params;
	t = p->table;
	if (p->table->philo_count == 1)
		return (put_action(p, "has taken a fork", &t->control), NULL);
	while (!stimulation_is_finished(t, &t->control))
	{
		if (!philo_eat(p, &t->control))
			return (NULL);
		philo_sleep(p, &t->control);
		philo_think(p, &t->control);
	}
	return (NULL);
}
