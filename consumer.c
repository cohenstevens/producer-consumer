#include "procon.h"


void* consumer(void* arg){
    srand(time(NULL));

    printf("Consumer Thread created\n");

    struct table *shmptr; // shared memory ptr
    int sharedMem = shmget(KEY, sizeof(struct table), 0644|IPC_CREAT); // creating shared mem buffer
    if(sharedMem == -1) printf("Shared Mem Key error\n");

    shmptr = shmat(sharedMem, NULL, 0); // attach to shared mem buffer
    if(sharedMem == -1) printf("Shared Mem attach error\n");

    sleep(1);

    for(int it=1; it <= iteration; ++it){

        sleep(1);

        sem_wait(&shmptr->mutex); // 
        printf("Consumer entered CS\n");

        int i, j = 1;
        sem_getvalue(&shmptr->empty, &i);

        while(i < SIZE){
            int x;
            x = shmptr->buffer[j];
            sem_post(&shmptr->empty); // say item has been taken from buffer
            printf("Consumer consumed item %d at %d\n", x, j);

            ++j;
            sem_getvalue(&shmptr->empty, &i);
        }

        printf("buffer is empty. Consumer done consuming items.\n");
        sem_post(&shmptr->mutex); //not in CS so post mutex
    }

    printf("Consumer Thread is done\n\n");

    shmdt(shmptr); //detach sharem mem buffer
    shmctl(sharedMem, IPC_RMID, NULL); // remove the shared memory buffer
}

int main(){

    pthread_t con;
    
    pthread_create(&con, NULL, consumer, NULL);
    pthread_join(con, NULL);

    return 0;
}