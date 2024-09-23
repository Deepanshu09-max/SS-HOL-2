/*
============================================================================
Name : 11.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -
                use sigaction system call.
Date: 19 Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Custom signal handler to ignore SIGINT
void ignore_sigint(int sig) {
    printf("SIGINT signal (Ctrl+C) is currently ignored.\n");
}

int main() {
    struct sigaction sa;

    // Step 1: Set up sigaction to ignore SIGINT
    sa.sa_handler = ignore_sigint;  // Handler that ignores SIGINT
    sigemptyset(&sa.sa_mask);  // No signals blocked during handler execution
    sa.sa_flags = 0;  // No special flags

    // Register the handler to ignore SIGINT
    sigaction(SIGINT, &sa, NULL);

    // Wait for signals for 10 seconds (SIGINT is ignored during this time)
    printf("SIGINT is being ignored for the next 10 seconds. Try pressing Ctrl+C now.\n");
    sleep(10);

    // Step 2: Reset SIGINT to its default action
    sa.sa_handler = SIG_DFL;  // Reset the signal handler to default
    sigaction(SIGINT, &sa, NULL);

    // Wait for signals for 10 seconds (SIGINT default action is restored)
    printf("SIGINT action has been reset to default. Press Ctrl+C again to terminate the program.\n");
    sleep(10);

    return 0;
}

/*
============================================================================
Command line: cc 11.c && ./a.out
Output: 
SIGINT is being ignored for the next 10 seconds. Try pressing Ctrl+C now.
^CSIGINT signal (Ctrl+C) is currently ignored.
SIGINT action has been reset to default. Press Ctrl+C again to terminate the program.
^C
============================================================================
*/
