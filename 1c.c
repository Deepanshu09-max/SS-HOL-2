/*
============================================================================
Name : 1c.c
Author : Deepanshu Saini (MT2024039)
Description : Write a separate program (for each time domain) to set an interval timer for 10 sec and
                10 microseconds
                c. ITIMER_PROF
Date: 19 Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

// Signal handler function for SIGPROF
void timer_handler(int signum) {
    printf("ITIMER_PROF: Timer triggered!\n");
}

int main() {
    struct itimerval prof_timer;

    // Setting up the signal handler for SIGPROF
    signal(SIGPROF, timer_handler);

    // Initialize the timer for 10 seconds and 10 microseconds
    prof_timer.it_value.tv_sec = 10;
    prof_timer.it_value.tv_usec = 10;
    prof_timer.it_interval.tv_sec = 10;
    prof_timer.it_interval.tv_usec = 10;

    // Activate the ITIMER_PROF timer
    if (setitimer(ITIMER_PROF, &prof_timer, NULL) == -1) {
        perror("Failed to set ITIMER_PROF");
        exit(EXIT_FAILURE);
    }

    // Infinite loop to simulate ongoing processing
    while (1) {
        // Simulating work in user and kernel mode
    }

    return 0;
}

/*
============================================================================
Command line: cc 1c.c && ./a.out
Output: 
ITIMER_PROF: Timer triggered!
ITIMER_PROF: Timer triggered!
...
(every 10 sec 10 usec)
============================================================================
*/