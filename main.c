#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define SERVER_IP "142.251.163.100" /* IP address of the server */ // This is google's ip
int main() {
  
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);

    /* Declare the IPV4 address structure */
    struct sockaddr_in address;
    /* Properties of the socket address*/
    address.sin_port = htons(80);
    address.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &address.sin_addr.s_addr);

    /* Connect to the server */
    int result = connect(socketFD, (struct sockaddr *)&address, sizeof(address));

    if (result == 0){
        printf("Connected to google server\n");
    }else {
        printf("Failed to connect to the server\n");
    }

    char *message = "GET / HTTP/1.1\r\nHost:google.com\r\n\r\n";
    send(socketFD, message, strlen(message), 0);

    char buffer[1024];
    int ret = recv(socketFD, buffer, sizeof(buffer), 0);

     if (ret > 0) {
        buffer[ret] = '\0';  // Null-terminate the received data so that it is printed as a string
        printf("Received Response: %s\n", buffer);
    } else {
        printf("Failed to receive response\n");
    }

    close(socketFD);

}
