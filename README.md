# Socket Programming in C

A hands-on collection of small C programs for learning network programming with the
Berkeley sockets API. The goal is to build up the fundamentals of TCP socket
communication as a stepping stone toward understanding higher-level protocols such as
HTTP and MQTT.

## What's inside

| Path                    | Description                                                                                                       |
| ----------------------- | ----------------------------------------------------------------------------------------------------------------- |
| `src/server/server.c`   | A TCP **echo/chat server** that listens on a port, accepts a single client, and exchanges messages interactively. |
| `src/client/client.c`   | A TCP **client** that connects to a server by hostname and port and sends/receives messages in a loop.            |
| `src/server/Dockerfile` | Multi-stage build for the **server** image (`kisakathejones/tcp-server`).                                          |
| `src/client/Dockerfile` | Multi-stage build for the **client** image (`kisakathejones/tcp-client`).                                          |
| `compose.yaml`          | Docker Compose definition that builds/runs both containers on a shared `tcpnet` bridge network.                   |
| `Makefile`              | Convenience targets to build and run the server and client natively, and to drive the Docker containers.          |

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

This compiles `src/server/server.c` to `src/server.out` and runs it on the default port.

### 2. Start the client

In a second terminal:

```bash
make client
```

This compiles `src/client/client.c` to `src/client.out` and connects to the server.

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

The server and the client are packaged as **two separate images**, each built from its
own `Dockerfile`:

| Service      | Image                          | Dockerfile              |
| ------------ | ------------------------------ | ----------------------- |
| `tcp-server` | `kisakathejones/tcp-server`    | `src/server/Dockerfile` |
| `tcp-client` | `kisakathejones/tcp-client`    | `src/client/Dockerfile` |

Each image is built in two stages — it compiles its single `.c` source with `gcc`, then
ships only the resulting binary on a slim Debian runtime. The `ENTRYPOINT` is the binary
(`./server.out` / `./client.out`) and the `CMD` supplies the default arguments, so the
server defaults to listening on port `9999` and the client defaults to connecting to
host `server` on port `9999`.

Both containers are **interactive** (they read your replies from standard input), so the
services are configured with `stdin_open` and `tty` enabled.

### Quick start with Docker Compose (recommended)

`compose.yaml` builds both images, attaches them to a shared `tcpnet` bridge network so
the client can reach the server by its service name, and publishes the server's port
`9999` to the host. Because the client connects to `tcp-server` by hostname, no manual
network setup is needed.

Bring the whole stack up in the background:

```bash
make silent      # sudo docker compose up -d
```

Then attach to each container in its own terminal to interact with it:

```bash
make server-attach   # attach to the tcp-server container
make client-attach   # attach to the tcp-client container
```

Once attached, the two containers take turns exchanging messages. Type `exit` to end
the session.

Tear everything down:

```bash
make remove      # sudo docker compose down
```

You can also drive Compose directly if you prefer:

```bash
docker compose up -d      # build and start both services
docker attach tcp-server  # or: docker attach tcp-client
docker compose down       # stop and remove the containers
```

### Building the images locally

To build from source without Compose:

```bash
docker build -t kisakathejones/tcp-server ./src/server
docker build -t kisakathejones/tcp-client ./src/client
```

### Exposing the server to the host

Compose already publishes port `9999`, so a client **outside Docker** (for example, the
native `make client` build or a tool like `nc`) can reach the containerized server:

```bash
make client PORT=9999 HOSTNAME=127.0.0.1
```

## Notes

- The server currently handles a **single client** connection at a time (no concurrency).
- Fixed-size buffers (255/256 bytes) are used for simplicity; these examples are for
  learning and are not hardened for production use.
- Compiled `*.out` binaries are ignored via `.gitignore`.
