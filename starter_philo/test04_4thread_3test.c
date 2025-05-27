

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef struct 		s_data
{
    int 			x;
    pthread_t 		*threads;
    pthread_mutex_t mutex;
} 					t_data;



typedef struct 		s_thread_p //parameter
{
    t_data 			*d;
    int 			th_id;

	
} 					t_thread_p;



void *ft_routine(void *arg)
{
    t_thread_p *p = (t_thread_p *)arg;


    pthread_mutex_lock(&p->d->mutex);
    printf("Thread %d start    x = %d\n", p->th_id, p->d->x);
    p->d->x += 1;
	sleep(1);

    printf("Thread %d leave    x = %d\n", p->th_id, p->d->x);
    pthread_mutex_unlock(&p->d->mutex);


    return NULL;
}



int main()
{
    t_data			*d;
    t_thread_p 		*p;

	d = (t_data *)malloc(sizeof(t_data));
    d->x = 0;
    d->threads = malloc(5 * sizeof(pthread_t));
    pthread_mutex_init(&d->mutex, NULL);

    for (int i = 0; i < 5; i++) {
		p = malloc(sizeof(t_thread_p));
        p->d = d;
        p->th_id = i;
        pthread_create(&d->threads[i], NULL, ft_routine, p);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(d->threads[i], NULL);
    }


    pthread_mutex_destroy(&d->mutex);
    free(d->threads);
    free(d);
    return 0;
}



// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <pthread.h>
// #include <string.h>

// typedef struct 		s_data
// {
//     int 			x;
//     pthread_t 		*threads;
//     pthread_mutex_t mutex;
// } 					t_data;

// typedef struct 		s_thread_p //parameter
// {
//     t_data 			*d;
//     int 			th_id;
// } 					t_thread_p;

// void *ft_routine(void *arg)
// {
//     t_thread_p *p = (t_thread_p *)arg;

//     pthread_mutex_lock(&p->d->mutex);  // แก้ไขจาก d->mutex เป็น p->d->mutex
//     printf("Thread %d start    x = %d\n", p->th_id, p->d->x);
//     p->d->x += 1;
//     printf("Thread %d leave    x = %d\n", p->th_id, p->d->x);
//     pthread_mutex_unlock(&p->d->mutex);  // แก้ไขจาก d->mutex เป็น p->d->mutex

//     return NULL;
// }

// int main()
// {
//     t_data			*d;
//     t_thread_p 		*p;

// 	d = (t_data *)malloc(sizeof(t_data));
//     d->x = 0;
//     d->threads = malloc(5 * sizeof(pthread_t));
//     pthread_mutex_init(&d->mutex, NULL);

//     for (int i = 0; i < 56789; i++) {
// 		p = malloc(sizeof(t_thread_p));
//         p->d = d;
//         p->th_id = i;
//         pthread_create(&d->threads[i], NULL, ft_routine, p);
//     }

//     for (int i = 0; i < 56789; i++) {
//         pthread_join(d->threads[i], NULL);
//     }

//     pthread_mutex_destroy(&d->mutex);
//     free(d->threads);
//     free(d);
//     return 0;
// }
