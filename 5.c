
//Implementation of Classical problems( producer consumer)  using Threads and Mutex

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex;

void* producer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);  
        if (count < BUFFER_SIZE) {
            buffer[count] = rand() % 100;  
            printf("Produced: %d, count: %d\n", buffer[count], count + 1); 
            count++; 
        }
        pthread_mutex_unlock(&mutex);  
        sleep(1);  
    }
}

void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);  
        if (count > 0) {
            printf("Consumed: %d, count: %d\n", buffer[count - 1], count - 1); 
            count--;  
        }
        pthread_mutex_unlock(&mutex);  
        sleep(1);  
    }
}


int main() {
    pthread_t prod_thread, cons_thread;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}

