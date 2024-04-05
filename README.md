# Producer Consumer Problem
OS Assignment 1


In this C program, the producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.
This marks my initial venture into coding in C. While I've had prior experience with C++, which provided me with a foundational understanding, I encountered difficulties in correctly executing this problem in C. Despite facing several setbacks and conducting extensive research, I eventually comprehended how to utilize semaphores and threads in this scenario. Solving this challenge proved to be an enjoyable learning experience for me.

# Requirements
- GCC Compiler
- Linux Machine

# How To Run
 - Download or clone the repository
 - Compile the code:
     gcc producer.c -pthread -lrt -o producer
   
     gcc consumer.c -pthread -lrt -o consumer
   
     ./producer & ./consumer & 

