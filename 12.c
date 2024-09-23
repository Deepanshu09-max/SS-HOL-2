/*
============================================================================
Name : 12.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
                the parent process from the child process.
Date: 19 Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    int pid = fork();  // Create a new process using fork()

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // This is the child process
        printf("Child process (PID: %d) created. Parent process PID: %d\n", getpid(), getppid());

        // Sleep for 2 seconds to ensure parent is running
        sleep(2);

        // Send SIGKILL to the parent process
        printf("Child process is sending SIGKILL to parent (PID: %d)\n", getppid());
        kill(getppid(), SIGKILL);  // Kill the parent process using SIGKILL

        // Sleep to show the child process becomes orphan
        sleep(5);
        printf("Child process (PID: %d) is now an orphan, adopted by init/systemd (new parent PID: %d)\n", getpid(), getppid());
    } else {
        // This is the parent process
        printf("Parent process (PID: %d) is running.\n", getpid());

        // Sleep to allow the child process to send SIGKILL
        sleep(10);  // The parent will be killed before reaching here
    }

    return 0;
}

/*
============================================================================
Command line: cc 12.c && ./a.out
Output: 
Parent process (PID: 6389) is running.
Child process (PID: 6390) created. Parent process PID: 6389
Child process is sending SIGKILL to parent (PID: 6389)
Killed
Deepanshu:~/Documents/HOL-2$ Child process (PID: 6390) is now an orphan, adopted by init/systemd (new parent PID: 2091)
============================================================================
*/
