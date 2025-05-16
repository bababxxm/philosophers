/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:28:18 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/16 22:42:46 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	mutex_handler(int status, int mode);
static bool	pthread_handler(int status, int mode);

/*

	Enum for mutex operations:
	LOCK     - Lock a mutex.
	UNLOCK   - Unlock a mutex.
	INIT     - Initialize a mutex.
	DESTROY  - Destroy a mutex.

	Enum for thread operations:
	CREATE   - Create a thread.
	JOIN     - Join (wait for) a thread.
	DETACH   - Detach a thread.

*/

bool	mutex_mode(t_mtx *mutex, int mode)
{
	int	status;

	if (mode == LOCK)
		status = pthread_mutex_lock(mutex);
	else if (mode == UNLOCK)
		status = pthread_mutex_unlock(mutex);
	else if (mode == INIT)
		status = pthread_mutex_init(mutex, NULL);
	else if (mode == DESTROY)
		status = pthread_mutex_destroy(mutex);
	else
		return (false);
	return (mutex_handler(status, mode));
}

bool	pthread_mode(t_pth *thread, void *(*f)(void *), void *data, int mode)
{
	int	status;

	if (mode == CREATE)
		status = pthread_create(thread, NULL, f, data);
	else if (mode == JOIN)
		status = pthread_join(*thread, NULL);
	else if (mode == DETACH)
		status = pthread_detach(*thread);
	else
		return (false);
	return (pthread_handler(status, mode));
}

/*

	Error codes for mutex operations:
	EINVAL : Invalid argument
	- The mutex is not initialized or attribute is invalid (LOCK, UNLOCK, INIT).
	EDEADLK : Deadlock detected
	- A deadlock condition was detected (LOCK).
	EPERM : Operation not permitted
	- The current thread does not own the mutex (UNLOCK).
	ENOMEM : Out of memory
	- Not enough memory to initialize the mutex (INIT).
	EBUSY : Resource busy
	- Attempt to destroy a locked or in-use mutex (DESTROY).

	Error codes for thread operations:
	EAGAIN : Resource temporarily unavailable
	- Not enough system resources to create another thread (CREATE).
	EPERM : Operation not permitted
	- Operation not permitted; usually due to insufficient privileges.
	EINVAL : Invalid argument
	- Invalid arguments for thread operation (CREATE, JOIN, DETACH).
	ESRCH : No such thread
	- No thread found with the given ID (JOIN, DETACH).
	EDEADLK : 	Deadlock detected
	- Deadlock detected; thread tried to join itself (JOIN).

*/

static bool	mutex_handler(int status, int mode)
{
	if (status == 0)
		return (true);
	else if (status == EINVAL && (mode == LOCK || mode == UNLOCK))
		return (false);
	else if (status == EINVAL && mode == INIT)
		return (false);
	else if (status == EDEADLK)
		return (false);
	else if (status == EPERM)
		return (false);
	else if (status == ENOMEM)
		return (false);
	else if (status == EBUSY)
		return (false);
	else
		return (true);
}

static bool	pthread_handler(int status, int mode)
{
	if (status == 0)
		return (true);
	else if (status == EAGAIN)
		return (false);
	else if (status == EPERM)
		return (false);
	else if (status == EINVAL && mode == CREATE)
		return (false);
	else if (status == EINVAL && (mode == JOIN || mode == DETACH))
		return (false);
	else if (status == ESRCH)
		return (false);
	else if (status == EDEADLK)
		return (false);
	else
		return (true);
}
