/*
============================================================================
Name : 8d.c
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

// Signal handler function for SIGALRM (Alarm clock)
void handle_sigalrm(int sig) {
    printf("Caught SIGALRM: Timer expired (using alarm())\n");
    exit(0);  // Exit the program after catching the signal
}

int main() {
    // Register the signal handler for SIGALRM
    signal(SIGALRM, handle_sigalrm);

    // Set an alarm to go off in 2 seconds
    alarm(2);

    // Infinite loop to keep the program running until the alarm triggers
    while (1);

    return 0;
}

/*
============================================================================
Command line: cc 8d.c && ./a.out
Output: 
Caught SIGALRM: Timer expired (using alarm())
============================================================================
*/
