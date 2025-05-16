/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:49:55 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/16 22:43:13 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// # ifndef DEBUG
// #  define DEBUG false
// # endif

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <errno.h>

# define WHITESPACE "\t\n\v\f\r "

# define MAX_PHILO 200
# define MAX_MS 800

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;
typedef pthread_t		t_pth;

typedef enum e_mutex_mode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY
}	t_mutex_mode;

typedef enum e_pthread_mode
{
	CREATE,
	JOIN,
	DETACH
}	t_pthread_mode;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_philo_status;

typedef struct s_fork
{
	size_t	id;
	t_mtx	mutex;
}	t_fork;

typedef struct s_philo
{
	size_t		id;
	t_pth		thread;
	size_t		fork[2];
	size_t		meals_count;
	size_t		since_last_meal;
	bool		is_full;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	t_philo	*philo;
	t_fork	*fork;
	size_t	philo_count;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	meals_for_each;
	size_t	time_since_start;
	bool	is_finished;
}	t_table;

bool	parser(t_table *t, int ac, char **av);
bool	init(t_table *t, int ac, char **av);
bool	mutex_mode(t_mtx *mutex, int mode);
bool	pthread_mode(t_pth *thread, void *(*f)(void *), void *data, int mode);

#endif