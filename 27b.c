/*
============================================================================
Name : 27b.c
Author : Deepanshu Saini
Description : Write a program to receive messages from the message queue.
                a. with 0 as a flag
                b. with IPC_NOWAIT as a flag
Date: 20 Sept 2024
============================================================================
*/

#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
	key_t key = ftok(".", 'a');
	if(key == -1) {
		perror("Failed to create key\n");
		exit(1);
	}

	int id = msgget(key, IPC_CREAT|0777);
	if(id == -1) {
		perror("Failed to create the message queue\n");
		exit(1);
	}

	struct msgbuf {
		long mtype;
		int num;
	};

	struct msgbuf msg;
	msg.mtype = 1;
	
	int status = msgrcv(id, &msg, sizeof(msg), msg.mtype, IPC_NOWAIT);
	if(status  == -1) {
		perror("Failed to send the message\n");
		exit(1);
	} else {
		printf("Message received with number: %d", msg.num);
	}

	return 0;
}

/*
============================================================================
Command line: cc 26.c && ./a.out 
Output: Message Sent!!        

Command line : cc 27b.c && ./a.out 
Message received with number: 108
============================================================================
*/