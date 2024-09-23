/*
============================================================================
Name : 13b.c
Author : Deepanshu Saini (MT2024039)
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
                will send the signal (using kill system call). Find out whether the first program is able to catch
                the signal or not.
Date: 19 Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    // Get the PID of the first program from command line
    int target_pid = atoi(argv[1]);

    // Send SIGSTOP signal to the target process
    if (kill(target_pid, SIGSTOP) == 0) {
        printf("SIGSTOP signal sent to process %d\n", target_pid);
    } else {
        perror("Failed to send SIGSTOP");
        return 1;
    }

    return 0;
}

/*
============================================================================
Command line: cc 13b.c && ./a.out <pid_of_program_waiting_for_SIGSTOP>
Output: 
SIGSTOP signal sent to process <pid>

Conclusion:
When this program sends a `SIGSTOP` signal to the first program (waiting to catch SIGSTOP), the first program cannot catch or handle it, demonstrating that `SIGSTOP` is one of the signals that cannot be caught, blocked, or ignored by a process.
============================================================================
*/
