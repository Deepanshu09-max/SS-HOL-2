/*
============================================================================
Name : 20b.c
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
#define BUFFER_SIZE 100

int main() {
    int fd;
    char buffer[BUFFER_SIZE];

    // Open the FIFO for reading
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    // Read the message from the FIFO
    if (read(fd, buffer, sizeof(buffer)) == -1) {
        perror("read failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Message received from FIFO: %s\n", buffer);

    // Close the FIFO
    close(fd);

    return 0;
}

/*
============================================================================
Command line: cc 20b.c && ./a.out
Output: Message received from FIFO: Hello from the writer!
============================================================================
*/
