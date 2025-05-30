/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:49:45 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/30 20:34:54 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*

Program name:		philo
Turn in files:		Makefile, *.h, *.c, in directory philo/
Makefile:			NAME, all, clean, fclean, re
Arguments:			number_of_philosophers time_to_die time_to_eat
					time_to_sleep [number_of_times_each_philosopher_must_eat]
External functs.:	memset, printf, malloc, free, write,
					usleep, gettimeofday, pthread_create,
					pthread_detach, pthread_join, pthread_mutex_init,
					pthread_mutex_destroy, pthread_mutex_lock,
					pthread_mutex_unlock
Libft authorized:	No
Description:		Philosophers with threads and mutexes

*/

int	main(int ac, char **av)
{
	t_table	t;

	if (!init(&t, ac - 1, av + 1))
		return (1);
	start_stimulation(&t);
	end_stimulation(&t);
	return (0);
}

/*

The specific rules for the mandatory part are:

• Each philosopher should be a thread.
• There is one fork between each pair of philosophers.
Therefore, if there are several philosophers,
each philosopher has a fork on their left side and a fork on their right side.
If there is only one philosopher, there should be only one fork on the table.
• To prevent philosophers from duplicating forks,
you should protect the forks state with a mutex for each of them.

*/

/*
	Test Cases

	Parser part:

	./philo 4 800 200 200
	Expected: Success, parses correctly with 4 philosophers and no meal limit.

	./philo 5 600 150 150 3
	Expected: Success, parses correctly with 5 philosophers and meal limit of 3.

	./philo "   4" "800   " "   200" "200"
	Expected: Success, leading/trailing whitespaces ignored.

	./philo +4 +800 +200 +200
	Expected: Success, plus sign is accepted.

	./philo
	Expected: philo: too few arguments.

	./philo 4 800 200
	Expected: philo: missing arguments.

	./philo 4 800 200 200 3 5
	Expected: philo: too many arguments.

	./philo 4 800 abc 200
	Expected: philo: invalid numeric input.

	./philo four 800 200 200
	Expected: philo: invalid numeric input.

	./philo 0 800 200 200
	Expected: philo: zero philosophers.

	./philo 4 -800 200 200
	Expected: philo: negative numeric input.

	./philo 999999999999999999999999 800 200 200
	Expected: philo: overflow.

	./philo "" 800 200 200
	Expected: philo: empty argument.

	./philo 4 800a 200 200
	Expected: philo: invalid trailing character.

	./philo 201 800 200 200
	Expected: philo: philo_count exceeds MAX_PHILO.

	Execute part:

	./philo 4 800 200 200  
	Expected: All philosophers should eat and sleep without dying.

	./philo 1 800 200 200  
	Expected: Philosopher dies (only one philosopher cannot eat).

	./philo 5 100 200 200  
	Expected: Philosophers may die early due to short time_to_die.

	./philo 5 800 300 300 2  
	Expected: Each philosopher eats exactly 2 times then simulation ends.

	./philo 5 800 300 300 0  
	Expected: philo: invalid meal count (zero times to eat).

	./philo 4 800 200 200  
	Expected: No data race or deadlock occurs.

*/