/*
============================================================================
Name : 8f.c
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

// Signal handler function for SIGVTALRM (Virtual timer)
void handle_sigvtalrm(int sig) {
    printf("Caught SIGVTALRM: Virtual timer expired (using setitimer())\n");
    exit(0);  // Exit the program after catching the signal
}

int main() {
    struct itimerval timer;

    // Register the signal handler for SIGVTALRM
    signal(SIGVTALRM, handle_sigvtalrm);

    // Set the virtual timer to go off after 2 seconds of CPU time used by the process
    timer.it_value.tv_sec = 2;  // Seconds
    timer.it_value.tv_usec = 0; // Microseconds
    timer.it_interval.tv_sec = 0;  // Interval seconds (0 for one-time timer)
    timer.it_interval.tv_usec = 0; // Interval microseconds

    // Set the timer using setitimer()
    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    // Infinite loop to keep the program running until the timer triggers
    while (1);

    return 0;
}

/*
============================================================================
Command line: cc 8f.c && ./a.out
Output: 
Caught SIGVTALRM: Virtual timer expired (using setitimer())
============================================================================
*/
