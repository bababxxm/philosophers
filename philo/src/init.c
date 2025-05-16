/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:18:12 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/16 22:39:21 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Arguments:
	1. philo_count         (1 <= count <= MAX_PHILO)
	2. time_to_die         (0-800 ms)
	3. time_to_eat         (0-800 ms)
	4. time_to_sleep       (0-800 ms)
	5. meals_for_each      (optional, default = 0)
*/

bool	init_table(t_table *t)
{
	(void)t;
	return (true);
}

bool	init(t_table *t, int ac, char **av)
{
	if (!parser(t, ac, av))
		return (false);
	if (!init_table(t))
		return (false);
	return (true);
}
