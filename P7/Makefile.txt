# Makefile template for CS 270

# List of files
SRCS			= printnum.asm 
OBJS			= printnum.obj

# Assembler and associated flags
AS				= ~cs270/lc3tools/lc3as
AS_FLAGS		= 

# Target is the executable
default: clean $(OBJS)

$(OBJS) : $(SRCS)
	@echo "Assembling $(SRCS) ..."
	$(AS) $(AS_FLAGS) $(SRCS)

# Check for illegal stuff
#illegal: $(SRCS)
#	@./checkIllegal

# Clean up the directory
clean:
	rm -rf *.obj *.sym *~

# tar needed files for submission
#package:
#	@echo "Creating tar file for submission"
#	tar -cvf overflow.tar lc3os.asm privateFun wholeFun 
