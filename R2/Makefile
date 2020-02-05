# Makefile template for CS 270

# List of files
C_SRCS		= field.c testField.c
C_OBJS		= field.o testField.o
C_HEADERS	= field.h

OBJS		= ${C_OBJS} 
EXE	        = testField

# Compiler and loader commands and flags
CC		    = gcc
CC_FLAGS	= -std=c11 -g -Wall -c
LD_FLAGS	= -std=c11 -g -Wall

# Target is the executable
testField: $(OBJS)	
	@echo "Linking all object modules ..."
	$(CC) $(LD_FLAGS) $(OBJS) -o $(EXE)
	@echo ""

# Recompile C objects if headers change
${C_OBJS}:      ${C_HEADERS}

# Compile .c files to .o files
.c.o:
	@echo "Compiling each C source file separately ..."
	$(CC) $(CC_FLAGS) $<
	@echo ""

# Clean up the directory
clean:
	@echo "Cleaning up project directory ..."
	rm -f *.o *~ $(EXE)
	@echo ""
