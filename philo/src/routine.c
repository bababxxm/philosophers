/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:48:06 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/18 16:54:56 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	philo_think(t_philo *p, t_mtx *control)
// {
// 	(void)p;
// 	(void)control;
// 	return ;
// }

// bool	philo_eat(t_philo *p, t_mtx *control)
// {
// 	t_fork	*f;

// 	(void)control;
// 	f = p->table->fork;
// 	mutex_mode(&f[p->fork[0]].mutex, LOCK);
// 	mutex_mode(&f[p->fork[1]].mutex, LOCK);
// 	p->since_last_meal = get_time_ms();
// 	printf("eat");
// 	mutex_mode(&f[p->fork[0]].mutex, UNLOCK);
// 	mutex_mode(&f[p->fork[1]].mutex, UNLOCK);
// 	return (true);
// }

// void	philo_sleep(t_philo *p, t_mtx *control)
// {
// 	(void)p;
// 	(void)control;
// 	return ;
// }

// philo_think(p, p->table->control);
// if (!philo_eat(p, p->table->control))
// 	break ;
// philo_sleep(p, p->table->control);

void	philo_action(t_philo *p, char *text)
{
	size_t	now;

	now = get_time_ms();
	printf("%d %d %s\n", (int)now, (int)p->id, text);
}

void	*philo_routine(void *params)
{
	t_fork	*f;
	t_philo	*p;

	p = (t_philo *)params;
	f = p->table->fork;
	t_mtx *control = p->table->control;
	if (p->id % 2 == 0)
		usleep(100);
	while (p->table->is_finished != true)
	{
		// think
		mutex_mode(control, LOCK);
		philo_action(p, "is thinking");
		mutex_mode(control, UNLOCK);

		// check if die
		if (get_time_ms() - p->since_last_meal < p->table->time_to_die)
			return (philo_action(p, "died"), NULL);
		
		// pick forks
		mutex_mode(&f[p->fork[0]].mutex, LOCK);
		philo_action(p, "has taken a fork");
		mutex_mode(&f[p->fork[1]].mutex, LOCK);
		philo_action(p, "has taken a fork");
		
		// eat
		philo_action(p, "is eating");
		p->since_last_meal = get_time_ms();
		p->meals_count++;
		mutex_mode(&f[p->fork[0]].mutex, UNLOCK);
		mutex_mode(&f[p->fork[1]].mutex, UNLOCK);
		sleep_ms(p->table->time_to_eat);

		// sleep
		mutex_mode(control, LOCK);
		philo_action(p, "is sleeping");
		mutex_mode(control, UNLOCK);
		sleep_ms(p->table->time_to_sleep);
	}	
	return (NULL);
}
