
//Implementation of Classical problems (reader writer)  using Threads and Mutex

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

pthread_mutex_t mutex;           
pthread_mutex_t readCountMutex; 
int readCount = 0;             
int sharedData = 0;            

void* reader(void* arg) {
    int id = *((int*)arg);
    while (1) {
        
        pthread_mutex_lock(&readCountMutex);
        readCount++;
        if (readCount == 1) {
            pthread_mutex_lock(&mutex);  
        }
        pthread_mutex_unlock(&readCountMutex);

        
        printf("Reader %d: reading shared data = %d\n", id, sharedData);
        sleep(1);  

        
        pthread_mutex_lock(&readCountMutex);
        readCount--;
        if (readCount == 0) {
            pthread_mutex_unlock(&mutex);  
        }
        pthread_mutex_unlock(&readCountMutex);

        sleep(1);  
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        
        pthread_mutex_lock(&mutex); 

        
        sharedData++;  
        printf("Writer %d: writing shared data = %d\n", id, sharedData);
        sleep(2);  

        pthread_mutex_unlock(&mutex);  
        sleep(2);  
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int ids[NUM_READERS + NUM_WRITERS];

  
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&readCountMutex, NULL);

    
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

   
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&readCountMutex);
    return 0;
}

