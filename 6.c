
//Implementation of Classical problems (reader writer) using Threads and Semaphore. 

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t rw_mutex;    
sem_t readCountSem;  
int readCount = 0;
int sharedData = 0;

void* reader(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&readCountSem);
        readCount++;
        if (readCount == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&readCountSem);

        printf("Reader %d: reading shared data = %d\n", id, sharedData);
        sleep(1);

        sem_wait(&readCountSem);
        readCount--;
        if (readCount == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&readCountSem);

        sleep(1);
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&rw_mutex);
        sharedData++;
        printf("Writer %d: writing shared data = %d\n", id, sharedData);
        sleep(2);
        sem_post(&rw_mutex);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int ids[NUM_READERS + NUM_WRITERS];

    sem_init(&rw_mutex, 0, 1);
    sem_init(&readCountSem, 0, 1);

    for (int i = 0; i < NUM_READERS; i++) {
        ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        ids[NUM_READERS + i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &ids[NUM_READERS + i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&readCountSem);
    return 0;
}

