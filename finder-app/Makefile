# Makefile for cross-compilation support

# Compiler and linker
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

# Target executable
TARGET = writer

# Source files
SRCS = writer.c
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Build rule
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

# Compile rule for source files
%.o: %.c
	$(CC) -c $< -o $@

# Clean rule
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
