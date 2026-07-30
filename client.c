#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) {
    perror(msg); //inbuilt function to print error message
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
        exit(1);
    }

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[255];
    portno = atoi(argv[2]); //convert port number from string to integer

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //ipv4, TCP, 0 for default protocol
    if (sockfd < 0) {
        error("Error opening the socket.");
    }

    server = gethostbyname(argv[1]); //get server host information, that is the IP address of the server
    if (server == NULL) {
        fprintf(stderr, "Error: No such host. Provide a valid IP.\n");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); //clear the server address structure
    serv_addr.sin_family = AF_INET; //ipv4
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length); //copy server address
    serv_addr.sin_port = htons(portno); //convert port number to network byte order

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Error connecting to the server.");
    }

    while(1) {
        printf("Enter message: ");
        bzero(buffer, 255); //clear the buffer
        fgets(buffer, 255, stdin); //read input from user

        n = write(sockfd, buffer, strlen(buffer)); //send data to the server
        if (n < 0) {
            error("Error writing to socket.");
        }

        int i = strncmp("exit", buffer, 4); //check if the client user wants to exit
        if (i == 0) {
            printf("Client is exiting. Issa wrap...\n");
            break; //exit the loop and close the client
        }

        bzero(buffer, 255); //clear the buffer

        n = read(sockfd, buffer, 255); //read response from the server
        if (n < 0) {
            error("Error reading from socket.");
        }
        printf("Server: %s\n", buffer); //print the server response

        i = strncmp("exit", buffer, 4);
        if (i == 0) {
            printf("Server has exited. Issa wrap...\n");
            break; //exit the loop and close the client
        }
    }

    close(sockfd); //close the socket
    return 0;
}