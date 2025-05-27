
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


int x = 0;

void	*ft_routine(void* th_id_main) 
{
    int th_id_ft = *((int*)th_id_main); 			// แปลง arg เป็น int เพื่อใช้เป็น thread_id

	
    printf("Thread %d start	x = %d\n", th_id_ft, x);
    x +=1;
	sleep(3); 									// ทำงานใน critical section เป็นเวลา 2 วินาที
	x += 1;
    printf("Thread %d leave	x = %d\n", th_id_ft, x);

    return NULL;
}

int main()
{
    pthread_t	threads[50]; 					// ประกาศตัวแปรเก็บเธรด
    int			th_id[50]; 						// ประกาศตัวแปรเก็บ thread_id

    for (int i = 0; i < 42; ++i) // fill 5	    // สร้างเธรด และเรียกใช้ thread_function ในแต่ละเธรด
	{
        th_id[i] = i;
        pthread_create(&threads[i], NULL, ft_routine, &th_id[i]);
    }

	// sleep(4); // รอให้เธรดทำงานเสร็จ by sleep		
 
    // for (int i = 0; i < 2; ++i) 				// รอให้เธรดทำงานเสร็จ by join
	// {
    //     pthread_join(threads[i], NULL);
    // }

	printf("====end=======");
    return (0);
}
