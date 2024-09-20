/*
============================================================================
Name : 10c.c
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

// Signal handler function for SIGFPE
void handle_sigfpe(int sig) {
    printf("Caught SIGFPE: Floating Point Exception\n");
    exit(1);  // Exit the program after catching the signal
}

int main() {
    struct sigaction sa;

    // Setting up SIGFPE handler
    sa.sa_handler = handle_sigfpe;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGFPE, &sa, NULL);  // Register the handler for SIGFPE

    // Trigger a SIGFPE for testing purposes by performing division by zero
    int x = 1;
    int y = 0;
    int z = x / y;  // This will trigger SIGFPE

    return 0;
}

/*
============================================================================
Command line: cc 10c.c && ./a.out
Output: 
Caught SIGFPE: Floating Point Exception
============================================================================
*/
