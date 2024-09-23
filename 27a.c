/*
============================================================================
Name : 27a.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to receive messages from the message queue.
                a. with 0 as a flag
                b. with IPC_NOWAIT as a flag
Date: 20 Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct msg_buffer {
    long msg_type;
    char msg_text[100];
} msg_buffer;

int main() {
    msg_buffer message;
    key_t key = 1234; // Project path is current directory and project id=1

    // Create message queue using msgget
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    printf("Enter msgtype:\n");
    scanf("%ld", &message.msg_type);

    // Receive message with flag 0 (blocking)
    int size_s = msgrcv(msgid, &message, sizeof(message), message.msg_type, 0);
    if (size_s <= 0) {
        perror("No message in queue\n");
    } else {
        printf("Message: %s\n", message.msg_text);
    }

    return 0;
}

/*
============================================================================
Command line: cc 27a.c && ./a.out
Output: 
Enter msgtype:
1
Message: Message 1
============================================================================
*/
