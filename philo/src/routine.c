/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:48:06 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/18 15:27:07 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *p, t_mtx *control)
{
	(void)p;
	(void)control;
	return ;
}

bool	philo_eat(t_philo *p, t_mtx *control)
{
	t_fork	*f;

	(void)control;
	f = p->table->fork;
	mutex_mode(&f[p->fork[0]].mutex, LOCK);
	mutex_mode(&f[p->fork[1]].mutex, LOCK);
	p->since_last_meal = get_time_ms();
	printf("eat");
	mutex_mode(&f[p->fork[0]].mutex, UNLOCK);
	mutex_mode(&f[p->fork[1]].mutex, UNLOCK);
	return (true);
}

void	philo_sleep(t_philo *p, t_mtx *control)
{
	(void)p;
	(void)control;
	return ;
}

void	*philo_routine(void *params)
{
	t_philo	*p;

	p = (t_philo *)params;
	while (p->table->is_finished != true)
	{
		philo_think(p, p->table->control);
		if (!philo_eat(p, p->table->control))
			break ;
		philo_sleep(p, p->table->control);
	}	
	return (NULL);
}