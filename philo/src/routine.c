/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:48:06 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/27 22:58:30 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_action(t_philo *p, char *text, t_mtx *ctl)
{
	size_t	now;

	mutex_mode(ctl, LOCK);
	if (p->table->is_finished != false)
		return (mutex_mode(ctl, UNLOCK), false);
	now = get_time_ms() - p->table->since_start;
	printf("%zu %zu %s\n", now, p->id, text);
	mutex_mode(ctl, UNLOCK);
	return (true);
}


void	philo_think(t_philo *p, t_mtx *ctl)
{
	print_action(p, "is thinking", ctl);
}

void	take_forks(t_philo *p, t_mtx *left, t_mtx *right, t_mtx *ctl)
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

bool	philo_eat(t_philo *p, t_mtx *ctl)
{
	t_fork	*f;

	mutex_mode(ctl, LOCK);
	if (p->table->is_finished != false)
		return (mutex_mode(ctl, UNLOCK), false);
	mutex_mode(ctl, UNLOCK);
	f = p->table->fork;
	if (p->id % 2 == 0)
		sleep_ms(1);
	take_forks(p, &f[p->fork[0]].mutex, &f[p->fork[1]].mutex, ctl);
	p->since_last_meal = get_time_ms();
	print_action(p, "is eating", ctl);
	sleep_ms(p->table->time_to_eat);
	mutex_mode(&f[p->fork[0]].mutex, UNLOCK);
	mutex_mode(&f[p->fork[1]].mutex, UNLOCK);
	return (true);
}

void	philo_sleep(t_philo *p, t_mtx *ctl)
{
	// (void)ctl;
	// mutex_mode(ctl, LOCK);
	// if (p->table->is_finished != false)
	// 	return ;
	// mutex_mode(ctl, UNLOCK);
	print_action(p, "is sleeping", ctl);
	sleep_ms(p->table->time_to_sleep);
}

void	*philo_routine(void *params)
{
	t_philo	*p;

	p = (t_philo *)params;
	while (p->table->is_finished != true)
	{
		if (!philo_eat(p, &p->table->control))
			return (NULL);
		philo_sleep(p, &p->table->control);
		// philo_think(p, &p->table->control);
	}
	return (NULL);
}

// void	*philo_routine(void *params)
// {
// 	// t_fork	*f;
// 	t_philo	*p;

// 	p = (t_philo *)params;
// 	printf("id: %zu, l: %zu, r: %zu\n",
// 		p->id, p->fork[0], p->fork[1]);
// 	// f = p->table->fork;
// 	// t_mtx *control = p->table->control;
// 	// if (p->id % 2 == 0)
// 	// 	usleep(100);
// 	// while (p->table->is_finished != true)
// 	// {
// 	// 	// think
// 	// 	mutex_mode(control, LOCK);
// 	// 	philo_action(p, "is thinking");
// 	// 	mutex_mode(control, UNLOCK);

// 	// 	// check if die
// 	// 	if (get_time_ms() - p->since_last_meal < p->table->time_to_die)
// 	// 		return (philo_action(p, "died"), NULL);
		
// 	// 	// pick forks
// 	// 	mutex_mode(&f[p->fork[0]].mutex, LOCK);
// 	// 	philo_action(p, "has taken a fork");
// 	// 	mutex_mode(&f[p->fork[1]].mutex, LOCK);
// 	// 	philo_action(p, "has taken a fork");
		
// 	// 	// eat
// 	// 	philo_action(p, "is eating");
// 	// 	p->since_last_meal = get_time_ms();
// 	// 	p->meals_count++;
// 	// 	mutex_mode(&f[p->fork[0]].mutex, UNLOCK);
// 	// 	mutex_mode(&f[p->fork[1]].mutex, UNLOCK);
// 	// 	sleep_ms(p->table->time_to_eat);

// 	// 	// sleep
// 	// 	mutex_mode(control, LOCK);
// 	// 	philo_action(p, "is sleeping");
// 	// 	mutex_mode(control, UNLOCK);
// 	// 	sleep_ms(p->table->time_to_sleep);
// 	// }	
// 	return (NULL);
// }
