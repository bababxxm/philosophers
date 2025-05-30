/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:48:06 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/30 17:29:31 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	put_action(t_philo *p, char *text, t_mtx *ctl);
bool	stimulation_is_finished(t_table	*t, t_mtx *ctl);

static void	get_forks(t_philo *p, t_mtx *ctl, int mode)
{
	t_fork	*f;

	f = p->table->fork;
	if (mode == GET_FORKS)
	{
		if (p->id % 2 == 0)
		{
			mutex_mode(&f[p->fork[0]].mutex, LOCK);
			put_action(p, "has taken a fork", ctl);
			mutex_mode(&f[p->fork[1]].mutex, LOCK);
			put_action(p, "has taken a fork", ctl);
		}
		else
		{
			mutex_mode(&f[p->fork[1]].mutex, LOCK);
			put_action(p, "has taken a fork", ctl);
			mutex_mode(&f[p->fork[0]].mutex, LOCK);
			put_action(p, "has taken a fork", ctl);
		}
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
	else if (p->is_full == true || p->is_dead == true)
		return (false);
	if (p->id % 2 == 0)
		usleep(100);
	get_forks(p, ctl, GET_FORKS);
	p->since_last_meal = get_time_ms();
	put_action(p, "is eating", ctl);
	sleep_ms(p->table->time_to_eat);
	p->meals_count++;
	mutex_mode(ctl, LOCK);
	p->is_full = (p->meals_count == p->table->meals_for_each);
	mutex_mode(ctl, UNLOCK);
	get_forks(p, ctl, RELEASE_FORKS);
	return (true);
}

static void	philo_sleep(t_philo *p, t_mtx *ctl)
{
	if (stimulation_is_finished(p->table, ctl))
		return ;
	else if (p->is_full == true || p->is_dead == true)
		return ;
	put_action(p, "is sleeping", ctl);
	sleep_ms(p->table->time_to_sleep);
}

static void	philo_think(t_philo *p, t_mtx *ctl)
{
	if (stimulation_is_finished(p->table, ctl))
		return ;
	else if (p->is_full == true || p->is_dead == true)
		return ;
	put_action(p, "is thinking", ctl);
}

void	*philo_routine(void *params)
{
	t_philo	*p;
	t_table	*t;

	p = (t_philo *)params;
	t = p->table;
	while (!stimulation_is_finished(t, &t->control))
	{
		if (!philo_eat(p, &t->control))
			return (NULL);
		philo_sleep(p, &t->control);
		philo_think(p, &t->control);
	}
	return (NULL);
}
