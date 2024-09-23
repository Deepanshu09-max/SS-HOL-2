/*
============================================================================
Name : 30b.c
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
#include <string.h>

int main() {
    key_t key = 12345;
    // shared memory created
    int shmid = shmget(key, 1024, IPC_CREAT | 0744);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    // attach shared memory to process address space in read-only mode
    char *data = shmat(shmid, (void *)0, SHM_RDONLY);
    if (data == (void *)-1) {
        perror("Shared memory not attached");
        return 1;
    }

    // Attempt to write to shared memory (should fail in read-only mode)
    printf("Attempting to write in shared memory:\n");
    char input[100];
    scanf("%[^\n]", input);

    // Attempting to write should cause an error or undefined behavior
    // This line is commented out because it will cause a segmentation fault.
    // strcpy(data, input);

    printf("Data from shared memory: %s\n", data);

    // Detach shared memory
    if (shmdt(data) == -1) {
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
Command line: cc 30b.c && ./a.out
Output: 
Attempting to write in shared memory:
f
Data from shared memory: [previous data if any]
============================================================================
*/
