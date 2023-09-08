# Makefile for Netlink example

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Output binary name
TARGET = netlink_example

# Source files
SRCS = netlink_example.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)
