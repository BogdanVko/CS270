# Makefile template for CS 270

# List of files
C_SRCS          = Debug.c symbol.c testSymbol.c
C_OBJS          = Debug.o symbol.o testSymbol.o
C_HEADERS       = Debug.h symbol.h

OBJS            = ${C_OBJS}
EXE             = testSymbol
DEFINES         = -DDEBUG

# Compiler and loader commands and flags
GCC             = gcc
GCC_FLAGS       = -g -std=c11 -Wall -c
LD_FLAGS        = -g -std=c11 -Wall

# Compile .c files to .o files
.c.o:
	$(GCC) $(GCC_FLAGS) $(DEFINES) $<

# Target is the executable
default: $(OBJS)
	$(GCC) $(LD_FLAGS) $(OBJS) -o $(EXE)

# Recompile C objects if headers change
${C_OBJS}:      ${C_HEADERS}

# Clean up the directory
clean:
	rm -f *.o *~ $(EXE)

