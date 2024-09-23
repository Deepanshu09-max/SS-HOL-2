/*
============================================================================
Name : 26.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 20 Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MESSAGE_KEY 1234  // Define a unique key for the message queue

// Define a structure for the message queue
struct msg_buffer {
    long msg_type;  // Message type (must be greater than 0)
    char msg_text[100];  // Buffer to hold the message text
};

int main() {
    int msgid;  // Variable to store the message queue ID
    struct msg_buffer msg;  // Structure to hold the message to be sent
    int i;

    // Create a message queue with the defined key
    // 0666 specifies read and write permissions
    // IPC_CREAT creates the queue if it does not already exist
    msgid = msgget(MESSAGE_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {  // Check if msgget failed
        perror("msgget failed");  // Print error message
        exit(EXIT_FAILURE);  // Exit the program with an error code
    }

    // Loop to send 5 messages to the queue
    for (i = 1; i <= 5; i++) {
        msg.msg_type = 1;  // Set message type (must be greater than 0)
        
        // Format the message text
        snprintf(msg.msg_text, sizeof(msg.msg_text), "Message %d", i);
        
        // Send the message to the queue
        // sizeof(msg.msg_text) specifies the length of the message text
        // 0 is used for the default flags (no special flags)
        if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
            perror("msgsnd failed");  // Print error message if sending fails
            exit(EXIT_FAILURE);  // Exit the program with an error code
        }
        
        // Print confirmation that the message has been sent
        printf("Sent: %s\n", msg.msg_text);
    }

    return 0;  // Return 0 to indicate successful completion
}

/*
============================================================================
Command line: cc 26.c && ./a.out
Output: 
Sent: Message 1
Sent: Message 2
Sent: Message 3
Sent: Message 4
Sent: Message 5
============================================================================
*/
