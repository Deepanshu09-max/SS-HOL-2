/*
============================================================================
Name : 15.c
Author : Deepanshu Saini (MT2024039)
Description : Write a simple program to send some data from parent to the child process.
Date: 20 Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];  // File descriptors for the pipe
    int pid;
    char write_msg[] = "Message from parent to child";
    char read_msg[100];

    // Step 1: Create the pipe
    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Step 2: Fork the process to create a child
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process
        // Step 3: Read from the pipe
        close(fd[1]);  // Close the write end of the pipe (child only needs to read)
        read(fd[0], read_msg, sizeof(read_msg));  // Read message from the pipe
        close(fd[0]);  // Close the read end after reading

        // Step 4: Display the message received from the parent
        printf("Child received: %s\n", read_msg);
    } else {  // Parent process
        // Step 5: Write to the pipe
        close(fd[0]);  // Close the read end of the pipe (parent only needs to write)
        write(fd[1], write_msg, strlen(write_msg) + 1);  // Write message to the pipe
        close(fd[1]);  // Close the write end after writing
    }

    return 0;
}

/*
============================================================================
Command line: cc 15.c && ./a.out
Output: Child received: Message from parent to child
============================================================================
*/
