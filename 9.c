/*
============================================================================
Name : 9.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - Use signal system call.
Date: 19 Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function for SIGINT (Ctrl+C)
void handle_sigint(int sig) {
    printf("SIGINT received, but currently ignored. Press Ctrl+C again to terminate the program.\n");
}

int main() {
    // Step 1: Ignore the SIGINT signal by setting the signal handler to the handle_sigint function
    signal(SIGINT, handle_sigint);

    // Wait for a signal (sleep for 10 seconds or until a signal is caught)
    printf("SIGINT is currently ignored. Try pressing Ctrl+C now.\n");
    sleep(10);  // During this time, SIGINT will be caught by handle_sigint

    // Step 2: Reset the SIGINT signal to its default action
    signal(SIGINT, SIG_DFL);

    // Wait for a signal (sleep for another 10 seconds)
    printf("SIGINT action reset to default. Press Ctrl+C again to terminate the program.\n");
    sleep(10);  // During this time, pressing Ctrl+C will terminate the program

    return 0;
}

/*
============================================================================
Command line: cc 9.c && ./a.out
Output: 
SIGINT is currently ignored. Try pressing Ctrl+C now.
^CSIGINT received, but currently ignored. Press Ctrl+C again to terminate the program.
SIGINT action reset to default. Press Ctrl+C again to terminate the program.
^C
============================================================================
*/
