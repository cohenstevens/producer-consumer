#ifndef OS_1
#define OS_1

#include <semaphore.h>


#define SIZE 2 // setting buffer size
#define iteration 10 // setting num of iterations to go through

#define KEY 0x1234 // shared memory key

struct table {
    sem_t mutex; // semaphore for mutual exclusion
    sem_t empty; // semaphore to check if buffer is empty

    int buffer[SIZE];
};


#endif