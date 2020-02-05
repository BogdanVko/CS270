# Makefile template for CS 270

# List of files
SRCS          = Debug.c iFloat.c testFloat.c
OBJS          = Debug.o iFloat.o testFloat.o
HEADERS       = Debug.h iFloat.h             convert.h

EXE           = testFloat
DEFINES       = -DDEBUG -DHALF
LIB           = convert.a

# Compiler and loader commands and flags
GCC             = gcc
GCC_FLAGS       = -g -std=c11 -Wall -c
LD_FLAGS        = -g -std=c11 -Wall

# Compile .c files to .o files
.c.o:
	$(GCC) $(GCC_FLAGS) $(DEFINES) $<

# Target is the executable
default: $(OBJS) $(LIB)
	$(GCC) -o $(EXE) $(LD_FLAGS) $(OBJS) $(LIB)

# Recompile C objects if headers change
${OBJS}:      ${HEADERS}

# Clean up the directory
clean:
	rm -f $(OBJS) *~ $(EXE)

