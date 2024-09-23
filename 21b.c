/*
============================================================================
Name : 21b.c
Author : Deepanshu Saini (MT2024039)
Description : Write two programs so that both can communicate by FIFO - Use two way communication.
Date: 20 Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO1 "21fifo1"  // FIFO for receiving data
#define FIFO2 "21fifo2"  // FIFO for sending data
#define BUFFER_SIZE 100

int main() {
    int fd1, fd2;
    char buffer[BUFFER_SIZE];
    char message[] = "Hello from Program 2!";
    
    // Open FIFO1 for reading
    fd1 = open(FIFO1, O_RDONLY);
    if (fd1 == -1) {
        perror("open fifo1 for reading failed");
        exit(EXIT_FAILURE);
    }

    // Open FIFO2 for writing
    fd2 = open(FIFO2, O_WRONLY);
    if (fd2 == -1) {
        perror("open fifo2 for writing failed");
        close(fd1);
        exit(EXIT_FAILURE);
    }

    // Read a message from FIFO1
    if (read(fd1, buffer, sizeof(buffer)) == -1) {
        perror("read from fifo1 failed");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }
    printf("Message received from FIFO1: %s\n", buffer);

    // Write a message to FIFO2
    if (write(fd2, message, sizeof(message)) == -1) {
        perror("write to fifo2 failed");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }
    printf("Message sent to FIFO2: %s\n", message);

    // Close FIFOs
    close(fd1);
    close(fd2);

    return 0;
}

/*
============================================================================
Command line: cc 21b.c && ./a.out
Output: 
Message received from FIFO1: Hello Program 1!
Message sent to FIFO2: Hello Program 2!
============================================================================
*/
