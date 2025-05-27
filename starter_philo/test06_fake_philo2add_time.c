
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>


size_t	ft_time_now_ms(void)
{
	struct timeval	t;
	size_t			time_now_ms;

	gettimeofday(&t, NULL);
	time_now_ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time_now_ms);
}

void	ft_usleep(size_t time)
{
	size_t	start;

	start = ft_time_now_ms();
	while (ft_time_now_ms() < (start + time))
		usleep(1);
}



typedef struct s_philo
{
	int				order;
	int				fork_l;
	int				fork_r;
	long			time_last_meal;

	pthread_t		th;

	struct 	s_data	*d;
}	t_philo;



typedef struct s_data
{
	int			nb_human;
	// int		time_die;
	// int		time_eat;
	// int		time_sleep;
	// int		how_meal_full;
	long		time_start;
	
	pthread_mutex_t		*mutex_fork;
	pthread_mutex_t		mutex_control;

	struct 	s_philo		*p;
}	t_data;





void	*ft_routine(void *arg)
{
	t_philo		*p;
	p	 = (t_philo	 *)arg;
	long		now;


	// pthread_mutex_lock(&p->d->mutex_control);
	// printf("start_	order=%d ,fork_l=%d, fork_r=%d\n", p->order ,p->fork_l,p->fork_r);
	// usleep(600);
	// printf("finish_	order=%d ,fork_l=%d, fork_r=%d\n", p->order ,p->fork_l,p->fork_r);
	// pthread_mutex_unlock(&p->d->mutex_control);

	// printf("		time %lu\n", now - p->d->time_start);

	ft_usleep(1000);
	now = ft_time_now_ms();

	printf("%lu   Philo no.%d go to Rong_A\n",now - p->d->time_start , p->order);
	if ( p->order % 2 == 0) // ku
	{
		ft_usleep(100);
		now = ft_time_now_ms();

		printf("%lu   Philo no.%d 	go to pa_kapao\n",now - p->d->time_start ,p->order);
		pthread_mutex_lock(&p->d->mutex_fork[p->fork_r]);
		printf("%lu   Philo no.%d 		taken fork right (fork_r=%d)\n",now - p->d->time_start , p->order, p->fork_r);
		pthread_mutex_lock(&p->d->mutex_fork[p->fork_l]);
		printf("%lu   Philo no.%d 		taken fork left	 (fork_l=%d)\n",now - p->d->time_start , p->order, p->fork_l);

		ft_usleep(200);
		now = ft_time_now_ms();
		printf("%lu   Philo no.%d 			eat========\n",now - p->d->time_start , p->order);

		pthread_mutex_unlock(&p->d->mutex_fork[p->fork_r]);
		pthread_mutex_unlock(&p->d->mutex_fork[p->fork_l]);
	}


	if ( p->order % 2 != 0) // kee
	{
		ft_usleep(900);
		now = ft_time_now_ms();

		printf("%lu   Philo no.%d 	go to pa_kapao\n",now - p->d->time_start , p->order);
		pthread_mutex_lock(&p->d->mutex_fork[p->fork_l]);
		printf("%lu   Philo no.%d 		taken fork left  (fork_l=%d)\n",now - p->d->time_start , p->order, p->fork_l);
		pthread_mutex_lock(&p->d->mutex_fork[p->fork_r]);
		printf("%lu   Philo no.%d 		taken fork right (fork_r=%d)\n",now - p->d->time_start , p->order, p->fork_r);
		
		ft_usleep(200);
		now = ft_time_now_ms();
		printf("%lu   Philo no.%d 			eat========\n",now - p->d->time_start , p->order);

		pthread_mutex_unlock(&p->d->mutex_fork[p->fork_r]);
		pthread_mutex_unlock(&p->d->mutex_fork[p->fork_l]);
	}
	return(0);

}



int	main()
{
	t_data		*d;
	d = malloc(sizeof(t_data));
	bzero(d,sizeof(t_data));

	d->nb_human				=	5;
	// d->time_die			=	200;
	// d->time_eat			=	200;
	// d->time_sleep		=	100;
	// d->how_meal_full		=	7;
	d->time_start			= 	ft_time_now_ms();


	pthread_mutex_init(&d->mutex_control, NULL);
	d->mutex_fork = malloc(sizeof(pthread_mutex_t) * d->nb_human);
	pthread_mutex_init(&d->mutex_fork[0], NULL);
	pthread_mutex_init(&d->mutex_fork[1], NULL);
	pthread_mutex_init(&d->mutex_fork[2], NULL);
	pthread_mutex_init(&d->mutex_fork[3], NULL);
	pthread_mutex_init(&d->mutex_fork[4], NULL);
	

	d->p = malloc(sizeof(t_philo) * d->nb_human);
	int	i = 0;
	while ( i < d->nb_human)
	{
		d->p[i].order			= i+1;
		d->p[i].fork_l			= i;
		d->p[i].fork_r			= (i+1) % (d->nb_human);
		d->p[i].time_last_meal	= ft_time_now_ms();
		d->p[i].d				=d;
		i++;
	}


	pthread_create( &d->p[0].th, NULL, ft_routine ,&d->p[0]	);
	pthread_create( &d->p[1].th, NULL, ft_routine ,&d->p[1]	);
	pthread_create( &d->p[2].th, NULL, ft_routine ,&d->p[2]	);
	pthread_create( &d->p[3].th, NULL, ft_routine ,&d->p[3]	);
	pthread_create( &d->p[4].th, NULL, ft_routine ,&d->p[4]	);


	// pthread_create( &d->p[3].th, NULL, ft_routine ,&d->p[0]	);
	// pthread_create( &d->p[3].th, NULL, ft_routine ,&d->p[1]	);
	// pthread_create( &d->p[3].th, NULL, ft_routine ,&d->p[2]	);
	// pthread_create( &d->p[3].th, NULL, ft_routine ,&d->p[4]	);
	// pthread_create( &d->p[3].th, NULL, ft_routine ,&d->p[4]	);


	// pthread_create( &d->p[0].th, NULL, ft_routine ,&d->p[0]	);
	// pthread_create( &d->p[1].th, NULL, ft_routine ,&d->p[0]	);
	// pthread_create( &d->p[2].th, NULL, ft_routine ,&d->p[0]	);
	// pthread_create( &d->p[3].th, NULL, ft_routine ,&d->p[0]	);
	// pthread_create( &d->p[4].th, NULL, ft_routine ,&d->p[0]	);



    pthread_join(d->p[0].th, NULL);
    pthread_join(d->p[1].th, NULL);
    pthread_join(d->p[2].th, NULL);
    pthread_join(d->p[3].th, NULL);
    pthread_join(d->p[4].th, NULL);

    
	pthread_mutex_destroy(&d->mutex_fork[0]);
	pthread_mutex_destroy(&d->mutex_fork[1]);
	pthread_mutex_destroy(&d->mutex_fork[2]);
	pthread_mutex_destroy(&d->mutex_fork[3]);
	pthread_mutex_destroy(&d->mutex_fork[4]);
    

    pthread_mutex_destroy(&d->mutex_control);
    free(d->mutex_fork);
    free(d->p);
    free(d);
	
}
