# ---- Stage 1: Build the application ---- #
FROM gcc:14 AS build

WORKDIR /src

COPY src/*.c ./

RUN gcc -Wall -O2 server.c -o server && \
    gcc -Wall -O2 client.c -o client


# ---- Stage 2: Runtime ---- #
FROM debian:bookworm-slim

WORKDIR /src

COPY --from=build /src/*.out ./

EXPOSE 9999

CMD ["./server.out", "9999"]