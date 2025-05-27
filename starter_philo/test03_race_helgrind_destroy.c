#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 10

int shared_variable = 0;
pthread_mutex_t mutex;

void *increment_shared_variable(void *arg)
{

    // for (int i = 0; i < 1234; i++) //for test ==>  valgrind --tool=helgrind ./a.out  
    for (int i = 0; i < 1234567; i++)
    {
        // pthread_mutex_lock(&mutex);   // Lock the mutex before accessing the shared variable
        shared_variable++;            // Access the shared variable
        // pthread_mutex_unlock(&mutex); // Unlock the mutex after accessing the shared variable
    }
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL); // Initialize the mutex

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, increment_shared_variable, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Final value of shared_variable: %d\n", shared_variable);

    // pthread_mutex_destroy(&mutex); // Destroy the mutex
    return 0;
}
