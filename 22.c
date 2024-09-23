/*
============================================================================
Name : 22.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
                system call with FIFO.
Date: 20 Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <errno.h>

#define FIFO_NAME "22fifo"
#define BUFFER_SIZE 100

int main() {
    int fd;
    char buffer[BUFFER_SIZE];
    fd_set readfds;
    struct timeval timeout;
    int retval;

    // Create the FIFO if it does not already exist
    if (mkfifo(FIFO_NAME, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo failed");
        exit(EXIT_FAILURE);
    }

    // Open the FIFO for reading
    fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    // Set up the file descriptor set
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    // Set up the timeout value
    timeout.tv_sec = 10;  // 10 seconds
    timeout.tv_usec = 0;  // 0 microseconds

    // Wait for data to become available
    retval = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (retval == -1) {
        perror("select failed");
        close(fd);
        exit(EXIT_FAILURE);
    } else if (retval == 0) {
        // Timeout occurred
        printf("No data received within 10 seconds.\n");
    } else {
        // Data is available
        if (FD_ISSET(fd, &readfds)) {
            ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
            if (bytes_read == -1) {
                perror("read failed");
                close(fd);
                exit(EXIT_FAILURE);
            }
            buffer[bytes_read] = '\0';  // Null-terminate the string
            printf("Data received: %s\n", buffer);
        }
    }

    // Close the FIFO
    close(fd);

    return 0;
}

/*
============================================================================
Command line: cc 22.c && ./a.out
Output: 
Data received: ong
============================================================================
*/
