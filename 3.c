/*
============================================================================
Name : 3.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 19 Sept, 2024.
============================================================================
*/

#include <stdio.h>      
#include <stdlib.h>     
#include <sys/resource.h> 

int main() {
    struct rlimit limit;

    // Setting soft and hard limits for virtual memory to 256 MB
    limit.rlim_cur = 256 * 1024 * 1024;  
    limit.rlim_max = 256 * 1024 * 1024;  

    // Applying the limit using setrlimit
    if (setrlimit(RLIMIT_AS, &limit) == -1) {
        perror("Failed to set RLIMIT_AS");
        printf("Soft limit: %ld, Hard limit: %ld\n", (long) limit.rlim_cur, (long) limit.rlim_max);
        return EXIT_FAILURE;
    }

    printf("Virtual memory limit set to 256 MB.\n");
    printf("Soft limit: %ld, Hard limit: %ld\n", (long) limit.rlim_cur, (long) limit.rlim_max);

    // Keeping the program alive for inspection
    while (1) {}

    return 0;
}

/*
============================================================================
Command line: cc 3.c && ./a.out
Output: 
Virtual memory limit set to 256 MB.
Soft limit: 268435456, Hard limit: 268435456
============================================================================
*/