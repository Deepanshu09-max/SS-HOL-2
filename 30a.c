/*
============================================================================
Name : 30a.c
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

int main() {
    key_t key = 12345;
    // shared memory created
    int shmid = shmget(key, 1024, IPC_CREAT | 0744);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }
    
    // attach shared memory to process address space
    char *data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat failed");
        return 1;
    }
    
    printf("write in shared memory\n");
    scanf("%[^\n]", data);

    printf("data from shared memory: %s\n", data);

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
Command line: cc 30a.c && ./a.out
Output: 
write in shared memory
Hello
data from shared memory: Hello
============================================================================
*/
