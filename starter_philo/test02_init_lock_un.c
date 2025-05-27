
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex; 							// ประกาศตัวแปร mutex
int x = 0;

void	*ft_routine(void* th_id_main) 
{
    int th_id_ft = *((int*)th_id_main); 			

    pthread_mutex_lock(&mutex); 				// ล็อก mutex

    printf("Thread %d start	x = %d\n", th_id_ft, x);
    x +=1;
	sleep(3); 									
	x += 1;
    printf("Thread %d leave	x = %d\n", th_id_ft, x);
    pthread_mutex_unlock(&mutex); 				// ปลดล็อก mutex

    return NULL;
}

int main()
{
    pthread_t	threads[5]; 					
    int			th_id[5]; 						

	printf("address = %p\n", &mutex);
	printf("size = %zu\n\n", sizeof(mutex));


	// pthread_mutex_init(&mutex, NULL); 			// สร้าง mutex
	
	
	printf("address = %p\n", &mutex);
	printf("size = %zu\n\n", sizeof(mutex));


    // สร้างเธรด และเรียกใช้ thread_function ในแต่ละเธรด
    for (int i = 0; i < 5; ++i) 
	{
        th_id[i] = i;
        pthread_create(&threads[i], NULL, ft_routine, &th_id[i]);
    }



	sleep(4);

    // รอให้เธรดทำงานเสร็จ
    for (int i = 0; i < 5; ++i) 
	{
        pthread_join(threads[i], NULL);
    }




	printf("====end=======");
    return (0);
}
