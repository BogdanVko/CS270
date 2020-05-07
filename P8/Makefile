# List of files
C_HEADERS = assembler.h Debug.h lc3.h        symbol.h tokens.h util.h
C_SRCS    = assembler.h Debug.c lc3.c main.c
C_OBJS    = assembler.o Debug.o lc3.o main.o

EXE       = mylc3as
ASM_LIB   = lc3as.a
DEFINES   = -DSTACK_OPS -DEBUG

# Compiler and loader commands and flags
GCC		= gcc
GCC_FLAGS	= -g -std=c11 -Wall $(DEFINES) -c
LD_FLAGS	= -g -std=c11 -Wall -no-pie

# Compile .c files to .o files
.c.o:
	$(GCC) $(GCC_FLAGS) $<

all: $(EXE) testTokens seeLC3 

# Target is the executable
$(EXE): $(ASM_LIB) $(C_OBJS)
	$(GCC) $(LD_FLAGS) $(C_OBJS) $(ASM_LIB) -o $(EXE)

testTokens: testTokens.c $(ASM_LIB)
	$(GCC) $(LD_FLAGS) testTokens.c $(ASM_LIB) -o testTokens 

seeLC3: seeLC3.c $(ASM_LIB)
	$(GCC) $(LD_FLAGS) seeLC3.c $(ASM_LIB) -o seeLC3

# Recompile C objects if headers change
${C_OBJS}: ${C_HEADERS}

# Clean up the directory
clean:
	rm -f *.o *~ $(EXE) testTokens seeLC3
