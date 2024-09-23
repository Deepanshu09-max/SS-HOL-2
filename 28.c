/*
============================================================================
Name : 28.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to change the existing message queue permission. (use msqid_ds structure)
Date: 17 Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>

// Define a unique key for the message queue
#define MESSAGE_KEY 12345

int main() {
    int msgid;  // Variable to store the message queue ID
    struct msqid_ds mq_ds;  // Structure to hold the message queue attributes

    // Create or access the message queue with the defined key
    msgid = msgget(MESSAGE_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {  // Check if msgget failed
        perror("msgget failed");  // Print error message
        exit(EXIT_FAILURE);  // Exit the program with an error code
    }

    // Get the current attributes of the message queue
    if (msgctl(msgid, IPC_STAT, &mq_ds) == -1) {
        perror("msgctl IPC_STAT failed");  // Print error message if msgctl fails
        exit(EXIT_FAILURE);  // Exit the program with an error code
    }

    // Print the current permissions
    printf("Current permissions: %o\n", mq_ds.msg_perm.mode);

    // Modify the permissions
    // Example: Set permissions to 0644 (owner can read/write, others can read)
    mq_ds.msg_perm.mode = 0644;

    // Set the new attributes of the message queue
    if (msgctl(msgid, IPC_SET, &mq_ds) == -1) {
        perror("msgctl IPC_SET failed");  // Print error message if msgctl fails
        exit(EXIT_FAILURE);  // Exit the program with an error code
    }

    // Print the updated permissions
    printf("Updated permissions: %o\n", mq_ds.msg_perm.mode);

    return 0;  // Return 0 to indicate successful completion
}

/*
============================================================================
Command line: cc 28.c && ./a.out
Output: 
Current permissions: 666
Updated permissions: 644
============================================================================
*/
