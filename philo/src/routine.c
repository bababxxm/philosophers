/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:48:06 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/28 18:37:45 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_action(t_philo *p, char *text, t_mtx *ctl);
bool	stimulation_is_finished(t_table	*t, t_mtx *ctl);

static void	take_forks(t_philo *p, t_mtx *left, t_mtx *right, t_mtx *ctl)
{
	if (p->id % 2 == 0)
	{
		mutex_mode(left, LOCK);
		print_action(p, "has taken a fork", ctl);
		mutex_mode(right, LOCK);
		print_action(p, "has taken a fork", ctl);
	}
	else
	{
		mutex_mode(right, LOCK);
		print_action(p, "has taken a fork", ctl);
		mutex_mode(left, LOCK);
		print_action(p, "has taken a fork", ctl);
	}
}

static bool	philo_eat(t_philo *p, t_mtx *ctl)
{
	t_fork	*f;

	if (stimulation_is_finished(p->table, ctl))
		return (false);
	f = p->table->fork;
	if (p->id % 2 == 0)
		usleep(500);
	take_forks(p, &f[p->fork[0]].mutex, &f[p->fork[1]].mutex, ctl);
	p->since_last_meal = get_time_ms();
	print_action(p, "is eating", ctl);
	sleep_ms(p->table->time_to_eat);
	mutex_mode(&f[p->fork[0]].mutex, UNLOCK);
	mutex_mode(&f[p->fork[1]].mutex, UNLOCK);
	return (true);
}

static void	philo_sleep(t_philo *p, t_mtx *ctl)
{
	if (stimulation_is_finished(p->table, ctl))
		return ;
	print_action(p, "is sleeping", ctl);
	sleep_ms(p->table->time_to_sleep);
}

static void	philo_think(t_philo *p, t_mtx *ctl)
{
	if (stimulation_is_finished(p->table, ctl))
		return ;
	print_action(p, "is thinking", ctl);
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
