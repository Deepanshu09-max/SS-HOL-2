/*
============================================================================
Name : 30c.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to create a shared memory.
                a. write some data to the shared memory
                b. attach with O_RDONLY and check whether you are able to overwrite.
                c. detach the shared memory
                d. remove the shared memory
Date: 17 Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    key_t key = 12345;
    // Create shared memory
    int shmid = shmget(key, 1024, IPC_CREAT | 0744);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    // Attach shared memory to process address space
    char *data_pointer = shmat(shmid, (void *)0, 0);
    if (data_pointer == (void *)-1) {
        perror("Shared memory not attached");
        return 1;
    }

    printf("Shared memory attached. Press any key to detach it...\n");
    getchar();  // Wait for user input

    printf("Detaching pointer to shared memory...\n");
    if (shmdt(data_pointer) == -1) {
        perror("shmdt failed");
        return 1;
    }

    // Remove shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID failed");
        return 1;
    }

    return 0;
}

/*
============================================================================
Command line: cc 30c.c && ./a.out
Output: 
Shared memory attached. Press any key to detach it...
Detaching pointer to shared memory...
============================================================================
*/
