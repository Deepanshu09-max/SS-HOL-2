/*
============================================================================
Name : 34aa.c
Author : Deepanshu Saini (MT2024039)
Description : A server program to communicate with clients using sockets.
Date: 18 Sept, 2024.
============================================================================
*/

/*
    1. socket() -> create an endpoint for communication
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
    2. bind() -> bind a name to the socket
        bindStatus = bind(sockfd, &server, sizeof(server));
    3. listen() -> listen for connections on the socket
        listenStatus = listen(sockfd, 2); // backlog -> 2
    4. accept() -> accept a connection on the socket
        connectionfd = accept(sockfd, (struct sockaddr *)&client, &client_size);
    5. Start communicating -> `write` to and `read` from connectionfd
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void *communicate(void *arg) {
    int connectionfd = *((int *)arg);
    free(arg); // Free allocated memory for the connectionfd

    char buf[100];
    // Send greeting message to client
    write(connectionfd, "Hello from server\n", 19);

    // Read message from client
    read(connectionfd, buf, sizeof(buf));
    printf("Data from client: %s\n", buf);

    close(connectionfd);
    return NULL;
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error when creating socket");
        exit(EXIT_FAILURE);
    }
    printf("Server socket created successfully.\n");

    // Server information
    struct sockaddr_in server, client;
    server.sin_addr.s_addr = htonl(INADDR_ANY); // Host to network long
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    // Bind the socket
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("Error while binding name to socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Binding to server socket was successful!\n");

    // Listen for connections
    if (listen(sockfd, 2) == -1) {
        perror("Error while trying to listen for connections");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Listening for connections...\n");

    while (1) {
        int client_size = sizeof(client);
        int *connectionfd = malloc(sizeof(int));
        *connectionfd = accept(sockfd, (struct sockaddr *)&client, (socklen_t *)&client_size);
        if (*connectionfd == -1) {
            perror("Error while accepting connection");
            free(connectionfd);
            continue;
        }

        pthread_t threadID;
        if (pthread_create(&threadID, NULL, communicate, connectionfd) != 0) {
            perror("Error while creating thread");
            close(*connectionfd);
            free(connectionfd);
        }
        pthread_detach(threadID); // Detach the thread to free resources upon completion
    }

    // Closing the server socket (unreachable in this loop)
    close(sockfd);
    return 0;
}

/*
============================================================================
Command line: cc 34aa.c -o server && ./server
Output: 
Server socket created successfully.
Binding to server socket was successful!
Listening for connections...
Data from client: <client message>
============================================================================
*/
