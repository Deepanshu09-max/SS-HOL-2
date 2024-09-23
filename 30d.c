/*
============================================================================
Name : 30d.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to create a shared memory.
                a. write some data to the shared memory
                b. attach with O_RDONLY and check whether you are able to overwrite.
                c. detach the shared memory
                d. remove the shared memory
Date: 19 Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
int main()
{
    key_t key = 12345;
    // shared memory created
    int shmid = shmget(key, 1024, IPC_CREAT | 0744);
    // attach shared memory to process address space
    char *data_pointer;
    data_pointer = shmat(shmid, (void *)0, 0);
    if (data_pointer == (void *)-1)
    {
        perror("Shared memory not attach");
        return 1;
    }
    printf("Shared memory attached press any key to delete shared memory\n");
    getchar();
    printf("Deleting shared memory\n");
    shmctl(key, IPC_RMID, NULL);
    return 1;
}
/*
============================================================================
Command line: cc 30d.c && ./a.out
Output: 
Shared memory attached press any key to delete shared memory

Deleting shared memory
============================================================================
*/
