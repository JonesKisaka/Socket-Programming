# Socket Programming in C

In a bid to understand more on HTTP and MQTT connection, i first have to learn Socket programming which is used in the mentioned protocols.
As such this is a basic guide on how to use socket programming in C.
Socket programming is a way of creating network servers and clients using the Berkeley sockets API.
Here is a simple guide on how to use socket programming in C.
### Step 1: Create a socket
To create a socket, you need to use the `socket()` function. This function takes three arguments
- `domain`: This is the address family. It can be `AF_INET` for IPv4
- `type`: This is the socket type. It can be `SOCK_STREAM` for TCP
- `protocol`: This is the protocol. It can be `IPPROTO_TCP` for TCP
