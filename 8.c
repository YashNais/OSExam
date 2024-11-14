
//Implementation of Classical problems (dining philosopher) using Threads and Semaphore

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];   
sem_t room; 

void* philosopher(void* arg) {
    int philosopher_id = *(int*)arg;

    while (1) {
      
        printf("Philosopher %d is thinking.\n", philosopher_id);
        sleep(rand() % 3);  

       
        sem_wait(&room);  //must always be atleast 1 thinker


        printf("Philosopher %d is hungry and tries to pick up forks.\n", philosopher_id);
        
        sem_wait(&forks[philosopher_id]);  
        sem_wait(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]); 

        printf("Philosopher %d is eating.\n", philosopher_id);
        sleep(rand() % 2);  

        sem_post(&forks[philosopher_id]); 
        sem_post(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]); 

        printf("Philosopher %d finished eating and puts down forks.\n", philosopher_id);

        sem_post(&room);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    sem_init(&room, 0, NUM_PHILOSOPHERS - 1); 

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
        ids[i] = i;
    }


    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }


    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }


    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }
    sem_destroy(&room);

    return 0;
}

