PORT := 9999
SERVER_FILENAME := server.c
CLIENT_FILENAME := client.c
HOSTNAME := localhost

# Compile the main program.

server:
	@echo "Starting server..."
	gcc $(SERVER_FILENAME) -o server.out && ./server.out $(PORT)

client:
	@echo "Starting client..."
	gcc $(CLIENT_FILENAME) -o client.out && ./client.out $(HOSTNAME) $(PORT)

trial:
	@echo "Running trial..."
	gcc pointers.c -o pointers.out && ./pointers.out

clean:
	@echo "Clearing compiled files..."
	rm -f *.out
	