/*
============================================================================
Name : 20a.c
Author : Deepanshu Saini (MT2024039)
Description : Write two programs so that both can communicate by FIFO - Use one way communication.
Date: 20 Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_NAME "20fifo"

int main() {
    int fd;
    char message[] = "Hello from the writer!";

    // Create FIFO using mkfifo if not already created
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo failed");
        exit(EXIT_FAILURE);
    }

    // Open the FIFO for writing
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    // Write a message to the FIFO
    if (write(fd, message, sizeof(message)) == -1) {
        perror("write failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Message sent to FIFO: %s\n", message);

    // Close the FIFO
    close(fd);

    return 0;
}

/*
============================================================================
Command line: cc 20a.c && ./a.out
Output:
Message sent to FIFO: Hello from the writer!
============================================================================
*/
