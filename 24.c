/*
============================================================================
Name : 24.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to create a message queue and print the key and message queue id.
Date: 20 Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MESSAGE_KEY 1234  // Define a key for the message queue

// Define a structure for message queue
struct msg_buffer {
    long msg_type;  // Message type
    char msg_text[100];  // Message text
};

int main() {
    key_t key;
    int msgid;
    
    // Generate a key for the message queue
    key = MESSAGE_KEY;  // You can also use ftok() to generate a key
    if (key == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    // Print the key and message queue ID
    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}

/*
============================================================================
Command line: cc 24.c && ./a.out
Output: 
Message Queue Key: 1234
Message Queue ID: 0
============================================================================
*/
