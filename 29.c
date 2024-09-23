/*
============================================================================
Name : 29.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to remove the message queue.
Date: 17 Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

// Define a unique key for the message queue
#define MESSAGE_KEY 1234

int main() {
    int msgid;  // Variable to store the message queue ID

    // Create or access the message queue with the defined key
    msgid = msgget(MESSAGE_KEY, 0666);
    if (msgid == -1) {  // Check if msgget failed
        perror("msgget failed");  // Print error message
        exit(EXIT_FAILURE);  // Exit the program with an error code
    }

    // Remove the message queue using the IPC_RMID command
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID failed");  // Print error message if msgctl fails
        exit(EXIT_FAILURE);  // Exit the program with an error code
    }

    // Print confirmation that the message queue has been removed
    printf("Message queue removed successfully.\n");

    return 0;  // Return 0 to indicate successful completion
}

/*
============================================================================
Command line: cc 29.c && ./a.out
Output: 
Message queue removed successfully.
============================================================================
*/
