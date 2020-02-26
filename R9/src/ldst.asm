	.ORIG x3000
	; Let's mess with some memory, now.

	; LD/ST are read/write instructions, respectively.
	; They take a PCOffset as a parameter, but we use labels to make
	; it easier for ourselves.
	; Notice the .FILL values at the end.
	
	; LD puts the value into a register.
	; R0 = Label1
	LD R0, Label1

	; R1 = Label2
	LD R1, Label2

	; Label1 += Label2
	ADD R0,R0,R1
	ST R0,Label1

	HALT
	; The labels don't exist in the simulation, they are only used by the
	; assembler to determine what the PCOffset values should be.
	; Why does the assembler make 2 passes through your program?
	; What is the .sym file it makes?
	; Try and figure out the PCOffset value for a couple of the instructions above.
	; Hint: What is the value of the PC?

Label1 	.FILL x1234
Label2	.FILL xABCD
	.END
