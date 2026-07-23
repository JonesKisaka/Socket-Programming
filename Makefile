PORT := 9999
FILENAME := server.c

# Compile the main program.

compile:
	@echo "Compiling main program..."
	gcc $(FILENAME) -o server.out && ./server.out $(PORT)

clean:
	@echo "Clearing compiled files..."
	rm -f *.out
	