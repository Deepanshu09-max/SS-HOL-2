/*
============================================================================
Name : 21a.c
Author : Deepanshu Saini (MT2024039)
Description : Write two programs so that both can communicate by FIFO - Use two way communications.
Date: 20 Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO1 "21fifo1"  // FIFO for sending data
#define FIFO2 "21fifo2"  // FIFO for receiving data
#define BUFFER_SIZE 100

int main() {
    int fd1, fd2;
    char buffer[BUFFER_SIZE];
    char message[] = "Hello from Program 1!";
    
    // Open FIFO1 for writing
    fd1 = open(FIFO1, O_WRONLY);
    if (fd1 == -1) {
        perror("open fifo1 for writing failed");
        exit(EXIT_FAILURE);
    }

    // Open FIFO2 for reading
    fd2 = open(FIFO2, O_RDONLY);
    if (fd2 == -1) {
        perror("open fifo2 for reading failed");
        close(fd1);
        exit(EXIT_FAILURE);
    }

    // Write a message to FIFO1
    if (write(fd1, message, sizeof(message)) == -1) {
        perror("write to fifo1 failed");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }
    printf("Message sent to FIFO1: %s\n", message);

    // Read a message from FIFO2
    if (read(fd2, buffer, sizeof(buffer)) == -1) {
        perror("read from fifo2 failed");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }
    printf("Message received from FIFO2: %s\n", buffer);

    // Close FIFOs
    close(fd1);
    close(fd2);

    return 0;
}

/*
============================================================================
Command line: cc 21a.c && ./a.out
Output:
Message sent to FIFO1: Hello from Program 1!
Message received from FIFO2: Hello from Program 2!
============================================================================
*/
