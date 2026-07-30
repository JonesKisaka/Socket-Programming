# Socket Programming in C

A hands-on collection of small C programs for learning network programming with the
Berkeley sockets API. The goal is to build up the fundamentals of TCP socket
communication as a stepping stone toward understanding higher-level protocols such as
HTTP and MQTT.

## What's inside

| File | Description |
|------|-------------|
| `server.c` | A TCP **echo/chat server** that listens on a port, accepts a single client, and exchanges messages interactively. |
| `client.c` | A TCP **client** that connects to a server by hostname and port and sends/receives messages in a loop. |
| `Makefile` | Convenience targets to build and run the server and client, and to clean binaries. |

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

## Notes

- The server currently handles a **single client** connection at a time (no concurrency).
- Fixed-size buffers (255/256 bytes) are used for simplicity; these examples are for
  learning and are not hardened for production use.
- Compiled `*.out` binaries are ignored via `.gitignore`.