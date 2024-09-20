/*
============================================================================
Name : 5.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to print the system limitations of:
                a. maximum length of the arguments to the exec family of functions.
                b. maximum number of simultaneous processes per user id.
                c. number of clock ticks (jiffy) per second.
                d. maximum number of open files.
                e. size of a page.
                f. total number of pages in the physical memory.
                g. number of currently available pages in the physical memory.
Date: 19 Sept, 2024.
============================================================================
*/

#include <stdio.h>      // Standard I/O functions like printf()
#include <unistd.h>     // Provides the sysconf() function for system configuration

int main() {
    // a. Maximum length of the arguments to the exec family of functions
    long arg_max;  // Variable to store the maximum argument length
    arg_max = sysconf(_SC_ARG_MAX);  // Get the value using sysconf() and store it in arg_max
    printf("Maximum length of the arguments to the exec family of functions: %ld\n", arg_max);

    // b. Maximum number of simultaneous processes per user id
    long max_procs;  // Variable to store the maximum number of processes per user ID
    max_procs = sysconf(_SC_CHILD_MAX);  // Get the value using sysconf() and store it in max_procs
    printf("Maximum number of simultaneous processes per user id: %ld\n", max_procs);

    // c. Number of clock ticks (jiffy) per second
    long clk_tck;  // Variable to store the number of clock ticks per second
    clk_tck = sysconf(_SC_CLK_TCK);  // Get the value using sysconf() and store it in clk_tck
    printf("Number of clock ticks (jiffy) per second: %ld\n", clk_tck);

    // d. Maximum number of open files
    long open_max;  // Variable to store the maximum number of open files
    open_max = sysconf(_SC_OPEN_MAX);  // Get the value using sysconf() and store it in open_max
    printf("Maximum number of open files: %ld\n", open_max);

    // e. Size of a memory page
    long page_size;  // Variable to store the size of a memory page
    page_size = sysconf(_SC_PAGESIZE);  // Get the value using sysconf() and store it in page_size
    printf("Size of a memory page: %ld bytes\n", page_size);

    // f. Total number of pages in physical memory
    long total_pages;  // Variable to store the total number of pages in physical memory
    total_pages = sysconf(_SC_PHYS_PAGES);  // Get the value using sysconf() and store it in total_pages
    printf("Total number of pages in physical memory: %ld\n", total_pages);

    // g. Number of currently available pages in physical memory
    long avail_pages;  // Variable to store the number of available pages in physical memory
    avail_pages = sysconf(_SC_AVPHYS_PAGES);  // Get the value using sysconf() and store it in avail_pages
    printf("Number of currently available pages in physical memory: %ld\n", avail_pages);

    return 0;  // Return 0 to indicate the program executed successfully
}

/*
============================================================================
Command line: cc 5.c && ./a.out
Output: 
Maximum length of the arguments to the exec family of functions: 2097152
Maximum number of simultaneous processes per user id: 30624
Number of clock ticks (jiffy) per second: 100
Maximum number of open files: 1048576
Size of a memory page: 4096 bytes
Total number of pages in physical memory: 1977759
Number of currently available pages in physical memory: 145389
============================================================================
*/