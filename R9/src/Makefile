
SRC=$(wildcard *.asm)
OBJ=$(SRC:.asm=.obj)

all: $(OBJ)

%.obj : %.asm
	@~cs270/lc3tools/lc3as $^ > /dev/null

clean:
	rm *.obj *.sym
