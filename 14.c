/*
============================================================================
Name : 14.c
Author : Deepanshu Saini (MT2024039)
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on
                the monitor.
Date: 20 Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];  // File descriptors for the pipe
    int pid;
    char write_msg[] = "Hello from the pipe!";
    char read_msg[100];

    // Step 1: Create the pipe
    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Step 2: Fork a process (optional for demonstration, single process can also use pipe)
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process
        // Step 3: Write to the pipe
        close(fd[0]);  // Close the read end of the pipe
        sleep(1);
        write(fd[1], write_msg, strlen(write_msg) + 1);  // Write message to the pipe
        close(fd[1]);  // Close the write end after writing
    } else {  // Parent process
        // Step 4: Read from the pipe
        close(fd[1]);  // Close the write end of the pipe
        read(fd[0], read_msg, sizeof(read_msg));  // Read message from the pipe
        close(fd[0]);  // Close the read end after reading

        // Step 5: Display the message read from the pipe
        printf("Message from pipe: %s\n", read_msg);
    }

    return 0;
}

/*
============================================================================
Command line: cc 14.c && ./a.out
Output: Message from pipe: Hello from the pipe!
============================================================================
*/
