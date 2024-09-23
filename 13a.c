/*
============================================================================
Name : 13a.c
Author : Deepanshu Saini (MT2024039)
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
                will send the signal (using kill system call). Find out whether the first program is able to catch
                the signal or not.
Date: 19 Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function for catching signals
void signal_handler() {
    printf("Caught SIGTSTP (Ctrl+Z)\n");
}

int main() {
    // Set up signal handler for SIGTSTP
    signal(SIGSTOP, signal_handler);  // Trying to catch SIGSTOP

    // Inform the user
    printf("Waiting for signals (SIGSTOP cannot be caught)\n");

    // Infinite loop to keep the program running and waiting for signals
    while (1) {
        sleep(30);  // Wait for signals
    }

    return 0;
}

/*
============================================================================
Command line: cc 13a.c && ./a.out
Output: 
Waiting for signals (SIGSTOP cannot be caught)

Conclusion: 
A program cannot catch a SIGSTOP signal. We can conclude this by observing that the custom handler function is never executed and instead, the program is simply stopped.
Two signals that cannot be caught or ignored:
1. SIGSTOP
2. SIGKILL
============================================================================
*/
