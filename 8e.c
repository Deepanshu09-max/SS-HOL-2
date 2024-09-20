/*
============================================================================
Name : 8e.c
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
#include <sys/time.h>
#include <unistd.h>

// Signal handler function for SIGALRM (Alarm clock)
void handle_sigalrm(int sig) {
    printf("Caught SIGALRM: Timer expired (using setitimer())\n");
    exit(0);  // Exit the program after catching the signal
}

int main() {
    struct itimerval timer;

    // Register the signal handler for SIGALRM
    signal(SIGALRM, handle_sigalrm);

    // Set the timer to go off after 2 seconds
    timer.it_value.tv_sec = 2;  // Seconds
    timer.it_value.tv_usec = 0; // Microseconds
    timer.it_interval.tv_sec = 0;  // Interval seconds (0 for one-time timer)
    timer.it_interval.tv_usec = 0; // Interval microseconds

    // Set the timer using setitimer()
    setitimer(ITIMER_REAL, &timer, NULL);

    // Infinite loop to keep the program running until the timer triggers
    while (1);

    return 0;
}

/*
============================================================================
Command line: cc 8e.c && ./a.out
Output: 
Caught SIGALRM: Timer expired (using setitimer())
============================================================================
*/
