/*
============================================================================
Name : 8c.c
Author : Deepanshu Saini (MT2024039)
Description : Write a separate program using signal system call to catch the following signals.
                a. SIGSEGV
                b. SIGINT
                c. SIGFPE
                d. SIGALRM (use alarm system call)
                e. SIGALRM (use setitimer system call)
                f. SIGVTALRM (use setitimer system call)
                g. SIGPROF (use setitimer system call)
Date: 19 Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// Signal handler function for SIGFPE (Floating Point Exception)
void handle_sigfpe(int sig) {
    printf("Caught SIGFPE: Floating Point Exception\n");
    exit(1);  // Exit the program after catching the signal
}

int main() {
    // Register the signal handler for SIGFPE
    signal(SIGFPE, handle_sigfpe);

    // Perform integer division by zero
    int x = 1;
    int y = 0;
    int z = x / y;  // This should trigger SIGFPE

    // The code below will not be executed as the program will terminate on the exception
    printf("This line will not be printed.\n");

    return 0;
}

/*
============================================================================
Command line: cc 8c.c && ./a.out
Output: 
Caught SIGFPE: Floating Point Exception
============================================================================
*/
