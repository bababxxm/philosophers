/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:41:04 by sklaokli          #+#    #+#             */
/*   Updated: 2025/01/13 02:58:35 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	clear()
{
	
}

void	philosohers()
{
	
}

void	init(t_philo *philo, char **params)
{
	init_data(philo, params);
}

void	parser(int argc, char *argv[])
{
	int	i;

	if ((argc != 5 && argc != 6) || ft_is_invalid_argv(argc, argv))
		ft_exit(ERROR_MSG, EXIT_FAILURE);
	i = 0;
	while (argv[++i])
		if (is_invalid_input(argv[i]))
			ft_exit(ERROR_MSG, EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_philo	philo;

	parser(argc, argv);
	init(&philo, argv);
	// philosophers();
	// clear();
}