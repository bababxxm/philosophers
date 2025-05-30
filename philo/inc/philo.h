/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:49:55 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/30 17:05:20 by sklaokli         ###   ########.fr       */
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
# define MIN_MS 60
# define MAX_MS 800
# define MAX_MEALS 200

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;
typedef pthread_t		t_pth;

typedef enum e_philo_errno
{
	PERR_ARG_NON,
	PERR_ARG_INV,
	PERR_ARG_EMT,
	PERR_NBR_NON,
	PERR_PHI_CNT,
	PERR_TME_DIE,
	PERR_TME_EAT,
	PERR_TME_SLP,
	PERR_MLS_CNT,
	PERR_MTX_MDE,
	PERR_PTH_MDE
}	t_philo_errno;

typedef enum e_mutex_mode
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}	t_mutex_mode;

typedef enum e_pthread_mode
{
	CREATE,
	JOIN,
	DETACH
}	t_pthread_mode;

typedef enum e_fork_actions
{
	GET_FORKS,
	RELEASE_FORKS
}	e_fork_actions;

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
	bool		is_dead;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	t_fork	*fork;
	t_philo	*philo;
	t_mtx	control;
	size_t	philo_count;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	meals_for_each;
	size_t	since_start;
	size_t	philo_meals_count;
	bool	all_philos_are_full;
	bool	is_finished;
}	t_table;

bool	parser(t_table *t, int ac, char **av);
bool	init(t_table *t, int ac, char **av);
bool	mutex_mode(t_mtx *mutex, int mode);
bool	pthread_mode(t_pth *thread, void *(*f)(void *), void *data, int mode);
void	*philo_routine(void *params);
bool	start_stimulation(t_table *t);
void	monitor_stimulation(t_table *t);

size_t	get_time_ms(void);
void	sleep_ms(size_t ms);
bool	broadcast(int perrno);

#endif