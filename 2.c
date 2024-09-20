/*
============================================================================
Name : 2.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to print the system resource limits. Use getrlimit system call.
Date: 19 Sept, 2024.
============================================================================
*/

#include <stdio.h>      
#include <sys/resource.h> 
#include <stdlib.h>     

// Function to display system resource limits
void display_limit(int resource, const char* resource_name) {
    struct rlimit limit_data;  

    // Retrieve resource limits and handle errors
    if (getrlimit(resource, &limit_data) == 0) {
        printf("%s:\n", resource_name);
        printf("  Soft limit: %ld\n", (long) limit_data.rlim_cur);
        printf("  Hard limit: %ld\n", (long) limit_data.rlim_max);
    } else {
        perror("Unable to retrieve limit");
        exit(EXIT_FAILURE); 
    }
}

int main() {
    // Display various system resource limits

    display_limit(RLIMIT_CPU, "CPU Time (seconds)");
    display_limit(RLIMIT_FSIZE, "File Size (bytes)");
    display_limit(RLIMIT_DATA, "Data Segment Size (bytes)");
    display_limit(RLIMIT_STACK, "Stack Size (bytes)");
    display_limit(RLIMIT_CORE, "Core File Size (bytes)");
    display_limit(RLIMIT_RSS, "Resident Set Size (bytes)");
    display_limit(RLIMIT_NOFILE, "Max Number of File Descriptors");
    display_limit(RLIMIT_MEMLOCK, "Locked Memory (bytes)");
    display_limit(RLIMIT_NPROC, "Max Number of Processes");
    display_limit(RLIMIT_AS, "Address Space (bytes)");

    return 0;
}

/*
============================================================================
Command line: cc 2.c && ./a.out
Output: 
CPU Time (seconds):
  Soft limit: -1
  Hard limit: -1
File Size (bytes):
  Soft limit: -1
  Hard limit: -1
Data Segment Size (bytes):
  Soft limit: -1
  Hard limit: -1
Stack Size (bytes):
  Soft limit: 8388608
  Hard limit: -1
Core File Size (bytes):
  Soft limit: 0
  Hard limit: -1
Resident Set Size (bytes):
  Soft limit: -1
  Hard limit: -1
Max Number of File Descriptors:
  Soft limit: 1048576
  Hard limit: 1048576
Locked Memory (bytes):
  Soft limit: 1012609024
  Hard limit: 1012609024
Max Number of Processes:
  Soft limit: 30624
  Hard limit: 30624
Address Space (bytes):
  Soft limit: -1
  Hard limit: -1
============================================================================
*/