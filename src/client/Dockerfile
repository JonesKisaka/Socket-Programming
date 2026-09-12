# Client Dockerfile
# ---- Stage 1: Build the application ---- #
FROM gcc:14 AS build

WORKDIR /client

COPY ./*.c ./ 

RUN gcc -Wall -O2 client.c -o client.out 

# ---- Stage 2: Runtime ---- #
FROM debian:bookworm-slim

WORKDIR /client

COPY --from=build /client/*.out ./

EXPOSE 9999

ENTRYPOINT ["./client.out"]

CMD ["server", "9999"]