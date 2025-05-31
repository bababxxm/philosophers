/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:49:45 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/31 14:48:24 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	t;

	if (!init(&t, ac - 1, av + 1))
		return (1);
	start_stimulation(&t);
	end_stimulation(&t);
	return (0);
}
