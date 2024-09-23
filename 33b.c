/*
============================================================================
Name : 33b.c
Author : Deepanshu Saini (MT2024039)
Description : Write a program to communicate between two machines using socket.
Date: 19 Sept, 2024.
============================================================================
*/

/*
    1. socket() -> create an endpoint for the communication
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
    2. connect() -> initiate a connection to a socket
        connectionStatus = connect(socketfd, &socketaddr, sizeof(socketaddr));
    3. Start communicating -> `write` to and `read` from socketfd
*/

#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>      
#include <unistd.h>     

int main()
{
    int socktd = socket(AF_INET, SOCK_STREAM, 0);
    if (socktd == -1) {
        perror("Error when creating socket");
        return 1;
    }
    printf("Socket created\n");

    // assigning server info
    struct sockaddr_in address;
    address.sin_addr.s_addr = htonl(INADDR_ANY); // host to network long
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    // make connection to the server
    int connectionS = connect(socktd, (struct sockaddr *)&address, sizeof(address));
    if (connectionS == -1) {
        perror("Error while establishing connection");
        return 1;
    }
    
    printf("Connection with server established\n");

    char buf[100];
    // read from server
    read(socktd, buf, sizeof(buf));
    printf("Data from server: %s\n", buf);

    printf("Write message for server: ");
    scanf(" %[^\n]", buf); // Space before % to consume newline

    write(socktd, buf, sizeof(buf));
    printf("Data sent to server\n");

    // closing socket
    close(socktd);
    return 0;
}

/*
============================================================================
Command line: cc 33b.c && ./a.out
Output: 
Socket created
Connection with server established
Data from server: Hello
Write message for server: Hii
Data sent to server
============================================================================
*/
