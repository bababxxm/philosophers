/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:41:01 by sklaokli          #+#    #+#             */
/*   Updated: 2025/01/13 07:29:27 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/include/libft.h"

# include <pthread.h>
# include <sys/time.h>

# define MAX_SEAT 200

typedef struct s_params
{
	size_t	count;
	size_t	die;
	size_t	eat;
	size_t	sleep;
	size_t	meal;
}	t_params;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_status;

typedef struct s_person
{
	size_t		id;
	pthread_t	thread;
	size_t		fork[2];
}	t_person;

typedef struct s_table
{
	size_t	chair[MAX_SEAT];
}	t_table;


typedef struct s_philo
{
	t_params	params;
}	t_philo;

# define ERROR_MSG "Error"

bool	is_invalid_input(char *input);
void	init_data(t_philo *philo, char **params);

#endif