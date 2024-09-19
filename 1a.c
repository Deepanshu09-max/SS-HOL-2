/*
Name : 1a.c
Author : Deepanshu Saini (MT2024039)
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
                10micro second
                a. ITIMER_REAL
Date: 19 Sept, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>   // For signal handling
#include <sys/time.h> // For timers
#include <unistd.h>   // For pause()

// Signal handler for SIGALRM
void handle_alarm(int signum) {
    printf("Timer expired (ITIMER_REAL)\n");
}

int main() {
    struct itimerval timer; // Structure to hold timer settings

    // Set up the signal handler for SIGALRM (called when the timer expires)
    signal(SIGALRM, handle_alarm);

    // Set the initial timer value (10 seconds and 10 microseconds)
    timer.it_value.tv_sec = 10;    // Timer expires after 10 seconds
    timer.it_value.tv_usec = 10;   // 10 microseconds after the 10 seconds
    timer.it_interval.tv_sec = 10; // Timer will reset every 10 seconds
    timer.it_interval.tv_usec = 10;// 10 microseconds after each 10-second interval

    // Set the ITIMER_REAL timer (counts real time and sends SIGALRM when it expires)
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("Error setting ITIMER_REAL");
        exit(EXIT_FAILURE);
    }

    // Infinite loop that waits for the signal (SIGALRM) when the timer expires
    while (1) {
        pause();  // Pause the program until a signal is received
    }

    return 0;
}

/*
Command line: cc 1a.c && ./a.out
Output: 
Timer expired (ITIMER_REAL)
Timer expired (ITIMER_REAL)
...
(every 10 sec 10 usec)
*/