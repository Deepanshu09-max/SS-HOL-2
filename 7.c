/*
============================================================================
Name : 7.c
Author : Deepanshu Saini (MT2024039)
Description : Write a simple program to print the created thread ids.
Date: 19 Sept, 2024.
============================================================================
*/

#include <stdio.h>      // Standard I/O functions
#include <pthread.h>    // POSIX thread library

// Function that will be executed by each thread
void* thread_function(void* arg) {
    long thread_id = pthread_self();  // Get the ID of the current thread
    printf("Thread %d: ID = %lu\n", *(int*)arg, thread_id);  // Print the thread number and its ID
    return NULL;  // Thread returns NULL
}

int main() {
    long threads[3];  // Array to hold the thread IDs for three threads
    int thread_args[3];     // Array to hold the thread arguments (thread numbers)

    // Loop to create three threads
    for (int i = 0; i < 3; i++) {
        thread_args[i] = i + 1;  // Assign a thread number (1, 2, 3)
        int ret = pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);  // Create thread
        if (ret != 0) {
            printf("Error creating thread %d\n", i + 1);  // Print an error message if thread creation fails
            return 1;
        }
    }

    // Loop to wait for all three threads to complete
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);  // Wait for the thread to finish
    }

    printf("All threads completed\n");  // Print a message after all threads are done
    return 0;  // Exit the program
}
/*
============================================================================
Command line: cc 7.c && ./a.out
Output: 
Thread 1: ID = 127049421293248
Thread 2: ID = 127049410807488
Thread 3: ID = 127049400321728
All threads completed
============================================================================
*/