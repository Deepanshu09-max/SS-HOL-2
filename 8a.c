/*
============================================================================
Name : 8a.c
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

// Signal handler function for SIGSEGV (Segmentation Fault)
void handle_sigsegv(int sig) {
    printf("Caught SIGSEGV: Segmentation Fault\n");
    exit(1);  // Exit the program after catching the signal
}

// Placeholder for other signal handlers
void handle_sigint(int sig) {
    printf("Caught SIGINT: Interrupt signal\n");
}

void handle_sigfpe(int sig) {
    printf("Caught SIGFPE: Floating point exception\n");
}

void handle_sigalrm(int sig) {
    printf("Caught SIGALRM: Alarm signal\n");
}

int main() {
    // Register the signal handlers
    signal(SIGSEGV, handle_sigsegv);
    signal(SIGINT, handle_sigint);
    signal(SIGFPE, handle_sigfpe);
    signal(SIGALRM, handle_sigalrm);

    // Intentionally cause a segmentation fault by dereferencing a NULL pointer
    int *ptr = NULL;
    *ptr = 42;  // This will trigger SIGSEGV

    return 0;
}

/*
============================================================================
Command line: cc 8a.c && ./a.out
Output: 
Caught SIGSEGV: Segmentation Fault
============================================================================
*/