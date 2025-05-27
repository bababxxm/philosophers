/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdanchal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:37:18 by kdanchal          #+#    #+#             */
/*   Updated: 2024/02/14 14:03:13 by kdanchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
  

size_t	ft_time_now_ms(void)
{
	struct timeval	t;
	size_t			time_now_ms;

	gettimeofday(&t, NULL);
	time_now_ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time_now_ms);
}

void	ft_mirco_sleep(size_t time)
{
	size_t	start;

	start = ft_time_now_ms();
	while (ft_time_now_ms() < (start + time))
		usleep(20);
}

int	main()
{
	struct	timeval	 a;
	
	gettimeofday(&a, NULL); // (sec+usec ,timezone)
	printf("tv_sec  = %ld\n", a.tv_sec);
	printf("tv_usec = %ld\n", a.tv_usec);

	// usleep(10000);
	ft_mirco_sleep(10);
	printf("			usleep\n");

	gettimeofday(&a, NULL);
	printf("tv_sec = %ld\n", a.tv_sec);
	printf("tv_usec = %ld\n", a.tv_usec);



	printf("\n\n===test2=====\n");
	long 	t1_sec;
	long	t1_usec;
	long 	t2_sec;
	long	t2_usec;
	
	gettimeofday(&a, NULL);
	t1_sec = a.tv_sec;
	t1_usec = a.tv_usec;
	printf("t1_sec  = %ld\n", t1_sec);
	printf("t1_usec = %ld\n", t1_usec);

	usleep(500000);
	// ft_mirco_sleep(500);
	printf("			usleep==========\n");

	gettimeofday(&a, NULL);
	t2_sec = a.tv_sec;
	t2_usec = a.tv_usec;
	printf("t2_sec = %ld\n", t2_sec);
	printf("t2_usec = %ld\n", t2_usec);


	printf("t2-t1_sec = %ld\n",  t2_sec  - t1_sec);
	printf("t2-t1_usec = %ld\n", t2_usec - t1_usec);

	



	
}
