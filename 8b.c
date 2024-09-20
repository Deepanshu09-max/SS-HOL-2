/*
============================================================================
Name : 8b.c
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
#include <unistd.h>

// Signal handler function for SIGINT (Ctrl+C)
void handle_sigint(int sig) {
    printf("Caught SIGINT: Interrupt from keyboard (Ctrl+C)\n");
    exit(0);  // Exit the program gracefully after catching the signal
}

int main() {
    // Register the signal handler for SIGINT
    signal(SIGINT, handle_sigint);

    // Infinite loop to keep the program running until interrupted
    while (1) {
        // Sleep for a short duration to reduce CPU usage
        sleep(1);
    }

    return 0;
}

/*
============================================================================
Command line: cc 8b.c && ./a.out
Output: 
Caught SIGINT: Interrupt from keyboard (Ctrl+C)
============================================================================
*/
