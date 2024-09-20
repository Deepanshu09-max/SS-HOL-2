/*
Name : 1b.c
Author : Deepanshu saini (MT2024039)
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
                10micro second
                b. ITIMER_VIRTUAL
Date: 19 Sept, 2024.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>   // For signal handling
#include <sys/time.h> // For timers

// Custom handler for SIGVTALRM signal
void custom_alarm_handler(int sig) {
    printf("Virtual timer expired (SIGVTALRM)\n");
}

int main() {
    struct itimerval virtual_timer; // Structure for timer configuration

    // Attach the custom signal handler to SIGVTALRM
    signal(SIGVTALRM, custom_alarm_handler);

    // Initialize the timer's initial expiration and interval values
    virtual_timer.it_value.tv_sec = 10;    // Timer will expire after 10 seconds
    virtual_timer.it_value.tv_usec = 10;   // Plus an additional 10 microseconds
    virtual_timer.it_interval.tv_sec = 10; // Timer will reset every 10 seconds
    virtual_timer.it_interval.tv_usec = 10;// With an additional 10 microseconds each interval

    // Set the virtual timer to trigger SIGVTALRM in user-mode execution
    if (setitimer(ITIMER_VIRTUAL, &virtual_timer, NULL) == -1) {
        perror("Failed to initialize ITIMER_VIRTUAL");
        exit(EXIT_FAILURE);
    }

    // Infinite loop to simulate user-mode activity
    for (;;) {
        // Placeholder for user-mode tasks (e.g., computations)
        // The timer only triggers while the process is in user mode
        volatile int count = 0;
        count++;  // Prevent the compiler from optimizing the loop away
    }

    return 0;
}


/*
Command line: cc 1b.c && ./a.out
Output: 
Timer expired (ITIMER_VIRTUAL)
Timer expired (ITIMER_VIRTUAL)
...
(every 10 sec 10 usec)
*/