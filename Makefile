PORT := 9999
SERVER_FILENAME := ./src/server/server.c
CLIENT_FILENAME := ./src/client/client.c
HOSTNAME := localhost

# To start this application, start the server first before the client.

# Start the server
server:
	@echo "Starting server..."
	gcc $(SERVER_FILENAME) -o ./src/server.out && ./src/server.out $(PORT)

# Start the client
client:
	@echo "Starting client..."
	gcc $(CLIENT_FILENAME) -o ./src/client.out && ./src/client.out $(HOSTNAME) $(PORT)

# Clean out all binaries
clean:
	@echo "Clearing compiled files..."
	rm -f ./src/*.out

# Docker compose commands

silent: 
	@echo "Starting server and client..."
	sudo docker compose up -d

remove: 
	@echo "Removing containers..."
	sudo docker compose down	

client-attach:
	@echo "Attaching to client container..."
	sudo docker attach $(shell docker ps -qf "name=tcp-client")

server-attach:
	@echo "Attaching to server container..."
	sudo docker attach $(shell docker ps -qf "name=tcp-server")
