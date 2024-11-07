CC = gcc
CFLAGS = -Wall

ASSEMBLER = assembler
SIMULATOR = simulator

FILENAME ?= fibonacci.asm

# Compile assembler from K2_assembler.c
$(ASSEMBLER): K2_assembler.c
	$(CC) $(CFLAGS) -o $(ASSEMBLER) K2_assembler.c

# Compile simulator from Simulator.c and K2_Simulator.c
$(SIMULATOR): K2_Simulator.c Simulator.c
	$(CC) $(CFLAGS) -o $(SIMULATOR) K2_Simulator.c Simulator.c

# Run the assembler with the specified input file
assemble: $(ASSEMBLER)
	@echo "Running assembler with input file: $(FILENAME)"
	./$(ASSEMBLER) $(FILENAME)

# Run the simulator with the specified binary file
simulate: $(SIMULATOR)
	@echo "Running simulator with binary file: $(FILENAME)"
	./$(SIMULATOR) $(FILENAME)

# Compile both assembler and simulator
all: $(ASSEMBLER) $(SIMULATOR)
	@echo "Both assembler and simulator compiled successfully."

# Clean up compiled files
clean:
	@echo "Cleaning up compiled files..."
	rm -f $(ASSEMBLER) $(SIMULATOR)

# Display help message
help:
	@echo "Makefile Usage:"
	@echo "  make assemble FILENAME=<filename>  - Run assembler with specified input file"
	@echo "  make simulate FILENAME=<filename>  - Run simulator with specified binary file"
	@echo "  make all                           - Compile both assembler and simulator"
	@echo "  make clean                         - Remove compiled files"
	@echo "  make help                          - Display this help message"

