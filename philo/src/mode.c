/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:28:18 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/30 20:37:32 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	mutex_handler(int status, int mode);
static bool	pthread_handler(int status, int mode);
bool		stimulation_is_finished(t_table	*t, t_mtx *ctl);

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
              does not need to join with it.

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
		return (write(2, "Invalid argument\n", 17), false);
	else if (status == EINVAL && mode == INIT)
		return (write(2, "Invalid argument\n", 17), false);
	else if (status == EDEADLK)
		return (write(2, "Deadlock detected\n", 18), false);
	else if (status == EPERM)
		return (write(2, "Operation not permitted\n", 24), false);
	else if (status == ENOMEM)
		return (write(2, "Out of memory\n", 14), false);
	else if (status == EBUSY)
		return (write(2, "Resource busy", 13), false);
	else
		return (write(2, "Unknown error\n", 14), false);
}

static bool	pthread_handler(int status, int mode)
{
	if (status == 0)
		return (true);
	else if (status == EAGAIN)
		return (write(2, "Resource temporarily unavailable\n", 33), false);
	else if (status == EPERM)
		return (write(2, "Operation not permitted\n", 24), false);
	else if (status == EINVAL && mode == CREATE)
		return (write(2, "Invalid argument\n", 17), false);
	else if (status == EINVAL && (mode == JOIN || mode == DETACH))
		return (write(2, "Invalid argument\n", 17), false);
	else if (status == ESRCH)
		return (write(2, "No such thread\n", 15), false);
	else if (status == EDEADLK)
		return (write(2, "Deadlock detected\n", 18), false);
	else
		return (false);
}

bool	put_action(t_philo *p, char *text, t_mtx *ctl)
{
	size_t	timestamp;

	if (stimulation_is_finished(p->table, ctl))
		return (false);
	mutex_mode(ctl, LOCK);
	timestamp = get_time_ms() - p->table->since_start;
	if (p->table->is_finished == true)
		return (mutex_mode(ctl, UNLOCK), false);
	printf("%zu %zu %s\n", timestamp, p->id, text);
	mutex_mode(ctl, UNLOCK);
	return (true);
}
