/*
============================================================================
Name : 16.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to send and receive data from parent to child vice versa. Use two way
                communication.
Date: 20 Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int parent_to_child[2];  // Pipe 1: Parent writes, Child reads
    int child_to_parent[2];  // Pipe 2: Child writes, Parent reads
    pid_t pid;
    char parent_msg[] = "Message from parent to child";
    char child_msg[] = "Message from child to parent";
    char read_msg[100];

    // Step 1: Create the pipes
    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Step 2: Fork the process to create a child
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process
        // Step 3: Close unused ends of the pipes in the child process
        close(parent_to_child[1]);  // Close write end of Parent -> Child pipe
        close(child_to_parent[0]);  // Close read end of Child -> Parent pipe

        // Step 4: Read from parent
        read(parent_to_child[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);

        // Step 5: Send a message back to the parent
        write(child_to_parent[1], child_msg, strlen(child_msg) + 1);

        // Step 6: Close the pipe ends after usage
        close(parent_to_child[0]);  // Close read end after reading
        close(child_to_parent[1]);  // Close write end after writing
    } else {  // Parent process
        // Step 7: Close unused ends of the pipes in the parent process
        close(parent_to_child[0]);  // Close read end of Parent -> Child pipe
        close(child_to_parent[1]);  // Close write end of Child -> Parent pipe

        // Step 8: Send a message to the child
        write(parent_to_child[1], parent_msg, strlen(parent_msg) + 1);

        // Step 9: Read the message from the child
        read(child_to_parent[0], read_msg, sizeof(read_msg));
        printf("Parent received: %s\n", read_msg);

        // Step 10: Close the pipe ends after usage
        close(parent_to_child[1]);  // Close write end after writing
        close(child_to_parent[0]);  // Close read end after reading
    }

    return 0;
}

/*
============================================================================
Command line: cc 16.c && ./a.out
Output:
Child received: Message from parent to child
Parent received: Message from child to parent
============================================================================
*/
