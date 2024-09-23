/*
============================================================================
Name : 33a.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to communicate between two machines using socket.
Date: 19 Sept, 2024.
============================================================================
*/

/*
    1. socket() -> create an endpoint for the communication
        socketfd = socket(AF_INET, SOCK_STREAM, 0);
    2. bind() -> bind a name to a socket
        bindStatus = bind(socketfd, &socketaddr, sizeof(socketfd));
    3. listen() -> listen for connections on a socket
        listenStatus = listen(socketfd, 2); // backlog -> 2
    4. accept() -> accept a connection on a socket
        connectionfd = accept(socketfd, &socketaddr, sizeof(socketaddr), 0);
    5. Start communicating -> `write` to and `read` from connectionfd
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int socktd = socket(AF_INET, SOCK_STREAM, 0);
    if (socktd == -1)
    {
        perror("Error when creating socket");
        return 1;
    }
    printf("Server socket created\n");

    // server info
    struct sockaddr_in server, client;
    server.sin_addr.s_addr = htonl(INADDR_ANY); // host to network long
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    int bindS = bind(socktd, (struct sockaddr *)&server, sizeof(server));
    if (bindS == -1)
    {
        perror("Error while binding name to socket!");
        _exit(0);
    }
    printf("Binding to server socket was successful!\n");

    // listen for connection
    int listenS = listen(socktd, 2);
    if (listenS == -1)
    {
        perror("Error while trying to listen to connections");
        _exit(0);
    }
    printf("Listening for connections...\n");

    int client_size = sizeof(client);
    int connectionfd = accept(socktd, (struct sockaddr *)&client, &client_size);
    if (connectionfd == -1)
    {
        perror("Error while accepting connection");
        _exit(0);
    }
    else
    {
        char buf[100];
        printf("Write message from server to client: ");
        scanf(" %[^\n]", buf); // Space before % to consume newline
        // write from server to connection fd
        write(connectionfd, buf, sizeof(buf));

        read(connectionfd, buf, 100);
        printf("Data from client: %s\n", buf);
    }

    // closing socket
    close(socktd);
    return 0;
}

/*
============================================================================
Command line: cc 33a.c && ./a.out
Output: 
Server socket created
Binding to server socket was successful!
Listening for connections...
Write message from server to client: Hello
Data from client: Hii
============================================================================
*/
