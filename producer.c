#include "procon.h"
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <pthread.h>

void* producer(void* arg){
    srand(time(NULL)); // random seed

    printf("Producer Thread created\n");

    struct table *shmptr; // shared memory ptr

    int sharedMem = shmget(KEY, sizeof(struct table), 0644|IPC_CREAT); // creating shared mem buffer
    if(sharedMem == -1) printf("Shared Mem Key error\n");

    shmptr = shmat(sharedMem, NULL, 0); // attach to shared mem buffer
    if(sharedMem == -1) printf("Shared Mem attach error\n");

    sem_init(&shmptr->mutex, 1, 1); // init to 1
    sem_init(&shmptr->empty, 1, SIZE);

    for(int it=0; it < iteration; ++it){
        sleep(1);
        
        sem_wait(&shmptr->mutex); //ensuring mutual exclusion
        printf("Producer entered CS\n"); // entering critical section

        int i, j = 1; // i is empty's value and j = buffer index
        sem_getvalue(&shmptr->empty, &i);

        while(i > 0){
            int x = rand() % 100 + 1; // random int from 1-100
            shmptr->buffer[j] = x;

            sem_wait(&shmptr->empty); // declare that the item was put into the buffer
            printf("Producer produced item %d at %d\n", x, j); // outputting num and buffer num
            ++j;
            sem_getvalue(&shmptr->empty, &i); // reevaluate while loop
        }

        printf("Buffer is full. Producer done producing items.\n");

        sem_post(&shmptr->mutex); // not in CS anymore
    }

    printf("Producer Thread is done\n");

    sem_destroy(&shmptr->mutex); //destroying semaphores
    sem_destroy(&shmptr->empty);
    shmdt(shmptr); //detach sharem mem buffer
}

int main(){

    pthread_t pro;

    pthread_create(&pro, NULL, producer, NULL);
    pthread_join(pro, NULL);

    return 0;
}