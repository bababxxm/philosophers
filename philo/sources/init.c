/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:43:54 by sklaokli          #+#    #+#             */
/*   Updated: 2025/01/12 00:20:33 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_data(t_philo *philo, char **params)
{
	philo->params.count = ft_atoi(params[1]);
	philo->params.die = ft_atoi(params[2]);
	philo->params.eat = ft_atoi(params[3]);
	philo->params.sleep = ft_atoi(params[4]);
	if (!params[5])
		philo->params.meal = 0;
	else if (params[5])
		philo->params.meal = ft_atoi(params[5]);
	printf("%zu %zu %zu %zu %zu\n", philo->params.count, philo->params.die,
		philo->params.eat, philo->params.sleep, philo->params.meal);
}
