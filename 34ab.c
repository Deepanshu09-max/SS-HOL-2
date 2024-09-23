/*
============================================================================
Name : 34ab.c
Author : Deepanshu Saini (MT2024039)
Description : A simple client program to communicate with a server using sockets.
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
    printf("Socket created successfully.\n");

    // Define server address
    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to your server's IP
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    // Establish connection to the server
    if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to server");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    char buffer[100];
    // Read message from server
    read(socket_fd, buffer, sizeof(buffer));
    printf("Message from server: %s\n", buffer);

    printf("Enter message to send to server: ");
    fgets(buffer, sizeof(buffer), stdin); // Use fgets for safe input

    write(socket_fd, buffer, sizeof(buffer)); // Send message to server
    printf("Message sent to server.\n");

    // Close the socket
    close(socket_fd);
    return 0;
}

/*
============================================================================
Command line: cc 34ab.c && ./a.out
Output: 
Socket created successfully.
Connected to server.
Message from server: Hello
Enter message to send to server: 
Hi
Message sent to server.
============================================================================
*/
