# Makefile template for CS 270 (specialized for R4) 

# List of files
C_SRCS		= main.c struct.c
C_OBJS		= main.o struct.o
C_HEADERS	= struct.h

OBJS		= ${C_OBJS} 
EXE		= R6

# Compiler and loader commands and flags
CC		= gcc
CC_FLAGS	= -std=c11 -O0 -g -Wall -c
LD_FLAGS	= -std=c11 -O0 -g -Wall

# The first, and hence default, target is the executable
$(EXE): $(OBJS)
	@echo "Linking all object modules."
	$(CC) $(LD_FLAGS) $(OBJS) -o $(EXE)

# Recompile C objects if headers change
${C_OBJS}: ${C_HEADERS}

# Compile .c files to .o files
.c.o:
	@echo "Compiling each C source file separately."
	$(CC) $(CC_FLAGS) $<

# Clean up the directory
clean:
	@echo "Cleaning project directory."
	rm -f *.o *~ $(EXE) $(EXE).tar 

# Package the directory
package: clean
	@echo "Packaging project directory."
	tar -cvf $(EXE).tar $(C_HEADERS) $(C_SRCS)

