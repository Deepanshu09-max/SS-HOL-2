/*
============================================================================
Name : 4.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to measure how much time is taken to execute 100 getppid()
              system calls using time stamp counter.
Date: 19 Sept, 2024.
============================================================================
*/

#include <stdio.h>     // For standard I/O functions
#include <stdint.h>    // For uint64_t type
#include <x86intrin.h> // For __rdtsc() intrinsic to access TSC
#include <unistd.h>    // For getppid() system call

int main() {
    uint64_t start, end; // Variables for storing the start and end TSC values
    int i;

    // Capture the Time Stamp Counter before the loop
    start = __rdtsc();

    // Call getppid() 100 times in a loop
    for (i = 0; i < 100; i++) {
        getppid();
    }

    // Capture the Time Stamp Counter after the loop
    end = __rdtsc();

    // Calculate and display the time taken (in clock cycles)
    printf("Time taken for 100 getppid() calls: %lu clock cycles\n", (end - start));

    return 0;
}

/*
============================================================================
Command line: cc 4.c && ./a.out
Output: 
Time taken for 100 getppid() calls: 157592 clock cycles
============================================================================
*/