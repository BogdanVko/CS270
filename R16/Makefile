# Makefile template for CS 270

# List of files
SRCS			= lc3os.asm 
OBJS			= lc3os.obj

# Assembler and associated flags
AS				= ~cs270/lc3tools/lc3as
AS_FLAGS		= 

# Target is the executable
default: clean $(OBJS)

$(OBJS) : $(SRCS)
	@echo "Assembling $(SRCS) ..."
	$(AS) $(AS_FLAGS) $(SRCS)

# Clean up the directory
clean:
	rm -rf lc3os.obj lc3os.sym *~

# tar needed files for submission
package:
	@echo "Creating tar file for submission"
	tar -cvf of.tar lc3os.asm privateFun wholeFun 
