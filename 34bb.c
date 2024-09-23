/*
============================================================================
Name : 34ab.c
Author : Deepanshu Saini (MT2024039)
Description : A client program to communicate with a server using sockets.
Date: 18 Sept, 2024.
============================================================================
*/

/*
    1. socket() -> create an endpoint for communication
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
    2. connect() -> initiate a connection to the server
        connectStatus = connect(sockfd, &address, sizeof(address));
    3. Start communicating -> `write` to and `read` from sockfd
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error when creating socket");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully.\n");

    // Server information
    struct sockaddr_in address;
    address.sin_addr.s_addr = htonl(INADDR_ANY); // Host to network long
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    // Connect to the server
    int connectStatus = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
    if (connectStatus == -1) {
        perror("Error while establishing connection");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Connection with server established.\n");

    char buf[100];
    // Read message from server
    read(sockfd, buf, sizeof(buf));
    printf("Data from server: %s\n", buf);

    printf("Write message for server: ");
    scanf(" %[^\n]", buf); // Added space before % to ignore newline

    write(sockfd, buf, sizeof(buf));
    printf("Data sent to server.\n");

    // Close the socket
    close(sockfd);
    return 0;
}

/*
============================================================================
Command line: cc 34ab.c && ./a.out
Output: 
Socket created successfully.
Connection with server established.
Data from server: Hello from server
Write message for server: Hi
Data sent to server.
============================================================================
*/
