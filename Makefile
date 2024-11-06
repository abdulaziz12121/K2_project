CC = gcc
CFLAGS = -Wall

ASSEMBLER = assembler
SIMULATOR = simulator


FILENAME ?= fibonacci.asm



$(ASSEMBLER): assembler.c
	$(CC) $(CFLAGS) -o $(ASSEMBLER) assembler.c

$(SIMULATOR): simulator.c
	$(CC) $(CFLAGS) -o $(SIMULATOR) simulator.c

assemble: $(ASSEMBLER)
	@echo "Running assembler with input file: $(FILENAME)"
	./$(ASSEMBLER) $(FILENAME)

simulate: $(SIMULATOR)
	@echo "Running simulator with binary file: $(FILENAME)"
	./$(SIMULATOR) $(FILENAME)

all: $(ASSEMBLER) $(SIMULATOR)
	@echo "Both assembler and simulator compiled successfully."

clean:
	@echo "Cleaning up compiled files..."
	rm -f $(ASSEMBLER) $(SIMULATOR)

help:
	@echo "Makefile Usage:"
	@echo "  make assemble FILENAME=<filename>  - Run assembler with specified input file"
	@echo "  make simulate FILENAME=<filename>  - Run simulator with specified binary file"
	@echo "  make all                           - Compile both assembler and simulator"
	@echo "  make clean                         - Remove compiled files"
	@echo "  make help                          - Display this help message"

