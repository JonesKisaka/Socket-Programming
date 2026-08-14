# Socket Programming in C

A hands-on collection of small C programs for learning network programming with the
Berkeley sockets API. The goal is to build up the fundamentals of TCP socket
communication as a stepping stone toward understanding higher-level protocols such as
HTTP and MQTT.

## What's inside

| File       | Description                                                                                                       |
| ---------- | ----------------------------------------------------------------------------------------------------------------- |
| `server.c` | A TCP **echo/chat server** that listens on a port, accepts a single client, and exchanges messages interactively. |
| `client.c` | A TCP **client** that connects to a server by hostname and port and sends/receives messages in a loop.            |
| `Makefile` | Convenience targets to build and run the server and client, and to clean binaries.                                |

## Concepts covered

- Creating a socket with `socket(AF_INET, SOCK_STREAM, 0)` (IPv4 + TCP)
- **Server side:** `bind()`, `listen()`, and `accept()`
- **Client side:** resolving a host with `gethostbyname()` and `connect()`
- Sending and receiving data with `read()`/`write()`
- Network byte order conversion with `htons()`
- Basic error handling via `perror()`

## Requirements

- A Unix-like OS (Linux, macOS)
- `gcc` and `make`

## Building and running

The `Makefile` uses `localhost` and port `9999` by default. **Start the server first,
then the client** — each in its own terminal.

### 1. Start the server

```bash
make server
```

This compiles `server.c` to `server.out` and runs it on the default port.

### 2. Start the client

In a second terminal:

```bash
make client
```

This compiles `client.c` to `client.out` and connects to the server.

Once connected, the client and server take turns exchanging messages:

- The **client** prompts for a message and sends it.
- The **server** prints the received message, then prompts for a reply to send back.

Type `exit` to terminate the session.

### Overriding defaults

The port, hostname, and source files are variables in the `Makefile` and can be
overridden on the command line:

```bash
make server PORT=8080
make client PORT=8080 HOSTNAME=127.0.0.1
```

### Cleaning up

Remove compiled binaries:

```bash
make clean
```

## Running with Docker

The application is published as a container image on Docker Hub:
[`kisakathejones/tcp-chat`](https://hub.docker.com/r/kisakathejones/tcp-chat).
The image is built in two stages — it compiles `server.c` and `client.c` with `gcc`,
then ships only the resulting `server.out` and `client.out` binaries on a slim Debian
runtime. By default the container starts the **server** on port `9999`.

Both the server and the client are **interactive** (they read your replies from
standard input), so every `docker run` below uses the `-it` flags to attach an
interactive terminal.

### Pull the image

```bash
docker pull kisakathejones/tcp-chat:0.2
```

### Quick start: server and client on one Docker network

Because the client connects to the server by hostname, the easiest setup is a
user-defined Docker network so the containers can find each other by name.

**1. Create a network:**

```bash
docker network create chatnet
```

**2. Start the server** (named `chat-server`, the default `CMD` runs `./server.out 9999`):

```bash
docker run -it --rm --name chat-server --network chatnet kisakathejones/tcp-chat:0.2
```

**3. Start the client** in a second terminal, connecting to `chat-server` on port `9999`.
This overrides the default command to run the client binary instead:

```bash
docker run -it --rm --network chatnet kisakathejones/tcp-chat:0.2 ./client.out chat-server 9999
```

Once connected, the two containers take turns exchanging messages. Type `exit` in
either terminal to end the session.

### Exposing the server to the host

To let a client **outside Docker** (for example, the native `make client` build or a
tool like `nc`) reach the containerized server, publish the port:

```bash
docker run -it --rm -p 9999:9999 kisakathejones/tcp-chat:0.2
```

Then connect from the host:

```bash
make client PORT=9999 HOSTNAME=127.0.0.1
```

### Running a different port

The server takes the port as a command-line argument. Override the default command and
map the port accordingly:

```bash
docker run -it --rm -p 8080:8080 kisakathejones/tcp-chat:0.2 ./server.out 8080
```

### Building the image locally

If you want to build from source instead of pulling:

```bash
docker build -t kisakathejones/tcp-chat:0.2 .
```

## Notes

- The server currently handles a **single client** connection at a time (no concurrency).
- Fixed-size buffers (255/256 bytes) are used for simplicity; these examples are for
  learning and are not hardened for production use.
- Compiled `*.out` binaries are ignored via `.gitignore`.
