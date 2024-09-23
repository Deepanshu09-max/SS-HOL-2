/*
============================================================================
Name : 25.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
                a. access permission
                b. uid, gid
                c. time of last message sent and received
                d. time of last change in the message queue
                e. size of the queue
                f. number of messages in the queue
                g. maximum number of bytes allowed
                h. pid of the msgsnd and msgrcv
Date: 20 Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

int main() {
    key_t key = 1234;  // Define a key for the message queue
    int msgid;
    struct msqid_ds msg_info;

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    // Retrieve the message queue information
    if (msgctl(msgid, IPC_STAT, &msg_info) == -1) {
        perror("msgctl failed");
        exit(EXIT_FAILURE);
    }

    // Print the access permissions
    printf("Access Permissions: %o\n", msg_info.msg_perm.mode & 0777);

    // Print UID and GID
    printf("UID: %u\n", msg_info.msg_perm.uid);
    printf("GID: %u\n", msg_info.msg_perm.gid);

    // Print times of last message sent, received, and last change
    printf("Time of Last Message Sent: %s", ctime(&msg_info.msg_stime));
    printf("Time of Last Message Received: %s", ctime(&msg_info.msg_rtime));
    printf("Time of Last Change: %s", ctime(&msg_info.msg_ctime));

    // Print the size of the queue
    printf("Current Size of Queue (in bytes): %ld\n", msg_info.__msg_cbytes);

    // Print the number of messages in the queue
    printf("Number of Messages in Queue: %ld\n", msg_info.msg_qnum);

    // Print the maximum number of bytes allowed
    printf("Maximum Number of Bytes Allowed: %ld\n", msg_info.msg_qbytes);

    // Print the PID of the last msgsnd and msgrcv
    printf("PID of Last msgsnd: %d\n", msg_info.msg_lspid);
    printf("PID of Last msgrcv: %d\n", msg_info.msg_lrpid);

    return 0;
}

/*
============================================================================
Command line: cc 25.c && ./a.out
Output: 
Access Permissions: 666
UID: 1000
GID: 1000
Time of Last Message Sent: Thu Jan  1 05:30:00 1970
Time of Last Message Received: Thu Jan  1 05:30:00 1970
Time of Last Change: Tue Sep 21 18:47:07 2024
Current Size of Queue (in bytes): 0
Number of Messages in Queue: 0
Maximum Number of Bytes Allowed: 16384
PID of Last msgsnd: 0
PID of Last msgrcv: 0
============================================================================
*/
