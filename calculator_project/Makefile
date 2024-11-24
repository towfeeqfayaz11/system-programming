# Compiler and Flags
CC = gcc
CFLAGS = -I include/math -Wall -Wextra -O2
LDFLAGS = -L lib/static -L lib/dynamic
LDLIBS = -lmathmultiply -lmathadd -lmathsubtract -lmathdivide

# Directories
OBJ_DIR = lib/objects
STATIC_LIB_DIR = lib/static
DYNAMIC_LIB_DIR = lib/dynamic
SRC_DIR = src/math

# Sources and Objects
SRC = $(SRC_DIR)/math_addition.c $(SRC_DIR)/math_division.c $(SRC_DIR)/math_multiplication.c \
      $(SRC_DIR)/math_subtraction.c $(SRC_DIR)/math_remainder.c src/main.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Library files
STATIC_LIBS = $(STATIC_LIB_DIR)/libmathmultiply.a $(STATIC_LIB_DIR)/libmathdivide.a
DYNAMIC_LIBS = $(DYNAMIC_LIB_DIR)/libmathadd.so $(DYNAMIC_LIB_DIR)/libmathsubtract.so

# Final executable
TARGET = src/main

# Default target
all: $(TARGET)

# Rule to create the final executable
$(TARGET): $(OBJ) $(STATIC_LIBS) $(DYNAMIC_LIBS)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

# Rule to compile .c files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< $(CFLAGS) -o $@

# Rule to create the static libraries
$(STATIC_LIBS): $(OBJ_DIR)/math_multiplication.o $(OBJ_DIR)/math_division.o
	ar rcs $@ $^

# Rule to create dynamic libraries
$(DYNAMIC_LIBS): $(OBJ_DIR)/math_addition.o $(OBJ_DIR)/math_subtraction.o
	$(CC) -shared $^ -o $@

# Clean up object and library files
clean:
	rm -f $(OBJ) $(STATIC_LIBS) $(DYNAMIC_LIBS) $(TARGET)

# Phony targets
.PHONY: all clean
