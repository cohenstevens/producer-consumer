#ifndef OS_1
#define OS_1

#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <pthread.h>


#define SIZE 2 // setting buffer size
#define iteration 10 // setting num of iterations to go through

#define KEY 0x1234 // shared memory key

struct table {
    sem_t mutex; // semaphore for mutual exclusion
    sem_t empty; // semaphore to check if buffer is empty

    int buffer[SIZE];
};


#endif