PORT := 9999
SERVER_FILENAME := server.c
CLIENT_FILENAME := client.c
HOSTNAME := localhost

# To start this application, start the server first before the client.

# Start the server
server:
	@echo "Starting server..."
	gcc $(SERVER_FILENAME) -o server.out && ./server.out $(PORT)

# Start the client
client:
	@echo "Starting client..."
	gcc $(CLIENT_FILENAME) -o client.out && ./client.out $(HOSTNAME) $(PORT)

# Clean out all binaries
clean:
	@echo "Clearing compiled files..."
	rm -f *.out
	