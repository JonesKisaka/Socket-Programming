#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
        printf("Connected to the server\n");
    }else {
        printf("Failed to connect to the server\n");
    }
}