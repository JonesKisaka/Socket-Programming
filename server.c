#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void error(const char *msg) {
    perror(msg); //inbuilt function to print error message
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Port number not provided. Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int sockfd, newsockfd, portno, n;
    char buffer[256];

    struct sockaddr_in serv_addr, client_addr;
    socklen_t client_len;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //ipv4, TCP, 0 for default protocol
    if (sockfd < 0) {
        error("Error opening the socket.");
    }

    // Clear the server address structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]); //convert port number from string to integer

    serv_addr.sin_family = AF_INET; //ipv4
    serv_addr.sin_addr.s_addr = INADDR_ANY; //bind to all available interfaces
    serv_addr.sin_port = htons(portno); //convert port number to network byte order

    // Bind the socket to the specified port
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Error on binding.");
    }

}