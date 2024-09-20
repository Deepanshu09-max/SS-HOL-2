/*
============================================================================
Name : 10b.c
Author : Deepanshu Saini (MT2024039)
Description : Write a separate program using sigaction system call to catch the following signals.
                a. SIGSEGV
                b. SIGINT
                c. SIGFPE
Date: 19 Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler function for SIGINT (Ctrl+C)
void handle_sigint(int sig) {
    printf("Caught SIGINT: Interrupt from keyboard (Ctrl+C)\n");
    exit(0);  // Exit the program gracefully
}

int main() {
    struct sigaction sa;

    // Setting up SIGINT handler
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);  // Register the handler for SIGINT

    // Wait indefinitely to allow the program to catch SIGINT
    while (1) {
        // Do nothing, just wait for signals
    }

    return 0;
}

/*
============================================================================
Command line: cc 10b.c && ./a.out
Output: 
^CCaught SIGINT: Interrupt from keyboard (Ctrl+C)
============================================================================
*/
