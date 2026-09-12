# Server Dockerfile
# ---- Stage 1: Build the application ---- #
FROM gcc:14 AS build

WORKDIR /server

COPY ./*.c ./ 

RUN gcc -Wall -O2 server.c -o server.out 

# ---- Stage 2: Runtime ---- #
FROM debian:bookworm-slim

WORKDIR /server

COPY --from=build /server/*.out ./

EXPOSE 9999

ENTRYPOINT ["./server.out"]

CMD ["9999"]