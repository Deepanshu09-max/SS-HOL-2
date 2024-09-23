/*
============================================================================
Name : 34aa.c
Author : Deepanshu Saini (MT2024039)
Description : A simple socket server program to communicate between machines.
Date: 18 Sept, 2024.
============================================================================
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    printf("Server socket created.\n");

    // Define server address
    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    // Bind socket to address
    if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding error");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    printf("Successfully bound to server socket.\n");

    // Listen for incoming connections
    if (listen(socket_fd, 3) == -1) {
        perror("Error listening for connections");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    printf("Listening for connections...\n");

    while (1) {
        socklen_t client_size = sizeof(client_addr);
        int connection_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_size);
        if (connection_fd == -1) {
            perror("Connection acceptance error");
            continue; // Try accepting the next connection
        }

        // Create a child process to handle the client
        if (fork() == 0) {
            // In child process
            char buffer[100];
            printf("Enter message for client: ");
            fgets(buffer, sizeof(buffer), stdin); // Read message safely
            write(connection_fd, buffer, sizeof(buffer)); // Send message to client

            read(connection_fd, buffer, sizeof(buffer)); // Read response from client
            printf("Received from client: %s\n", buffer);
            close(connection_fd); // Close connection in child
            exit(0); // Terminate child process
        } else {
            // In parent process
            close(connection_fd); // Close connection fd for the client
        }
    }

    close(socket_fd); // Close server socket
    return 0;
}

/*
============================================================================
Command line: cc 34aa.c && ./a.out
Output: 
Server socket created.
Successfully bound to server socket.
Listening for connections...
Enter message for client: 
Hello
Received from client: Hi
============================================================================
*/
