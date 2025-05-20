/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:28:18 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/20 12:27:40 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	mutex_handler(int status, int mode);
static bool	pthread_handler(int status, int mode);

/*

   Mutex operations:

   LOCK     - Locks a mutex to ensure that only one thread can access
              a critical section of code at a time. If the mutex is already
              locked, the calling thread will wait until it becomes available.

   UNLOCK   - Unlocks a mutex that was previously locked by the same thread.
              This allows other threads to acquire the mutex and enter the
              critical section.

   INIT     - Initializes a mutex before it is used. This sets up the internal
              structures needed for the mutex to function properly.

   DESTROY  - Destroys a mutex when it is no longer needed.
   			  This frees any resources associated with the mutex.

   Thread operations:

   CREATE   - Creates a new thread to run a specified function concurrently
              with the calling thread.

   JOIN     - Waits for a specified thread to finish executing. This blocks
              the calling thread until the target thread terminates.

   DETACH   - Marks a thread as detached, meaning it will clean up its own
              resources automatically when it finishes. The calling thread
              does not need to join with it. Done using pthread_detach().

*/

bool	mutex_mode(t_mtx *mutex, int mode)
{
	int	status;

	if (mode == INIT)
		status = pthread_mutex_init(mutex, NULL);
	else if (mode == LOCK)
		status = pthread_mutex_lock(mutex);
	else if (mode == UNLOCK)
		status = pthread_mutex_unlock(mutex);
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
		return (printf("Invalid argument\n"), false);
	else if (status == EINVAL && mode == INIT)
		return (printf("Invalid argument\n"), false);
	else if (status == EDEADLK)
		return (printf("Deadlock detected\n"), false);
	else if (status == EPERM)
		return (printf("Operation not permitted\n"), false);
	else if (status == ENOMEM)
		return (printf("Out of memory\n"), false);
	else if (status == EBUSY)
		return (printf("Resource busy"), false);
	else
		return (printf("Unknown error\n"), false);
}

static bool	pthread_handler(int status, int mode)
{
	if (status == 0)
		return (true);
	else if (status == EAGAIN)
		return (printf("Resource temporarily unavailable\n"), false);
	else if (status == EPERM)
		return (printf("Operation not permitted\n"), false);
	else if (status == EINVAL && mode == CREATE)
		return (printf("Invalid argument\n"), false);
	else if (status == EINVAL && (mode == JOIN || mode == DETACH))
		return (printf("Invalid argument\n"), false);
	else if (status == ESRCH)
		return (printf("No such thread\n"), false);
	else if (status == EDEADLK)
		return (printf("Deadlock detected\n"), false);
	else
		return (false);
}
