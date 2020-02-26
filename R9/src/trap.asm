	.ORIG x3000
	; TRAP subroutines are predefined system routines to perform tasks
	; the user isn't expected to do, like handling I/O.
	; Each TRAP can be invoked by a direct instruction or a macro.
	; E.g.: "TRAP x21" is equivalent to "OUT"
	; All of the I/O TRAPs use R0 as a parameter/output register.

	; Open the LC3 simulator and investigate the first few memory addresses.
	; Most addresses with a default value of 0 are labelled "NOP," but these
	; are labeled "BAD_TRAP." Some values, for example at memory x0021, however,
	; have addresses. What is at the address stored in location x0021?
	; This is the TRAP vector. It contains pointers to the beginning of
	; every TRAP routine, which can be called by doing
	; "TRAP x??" where ?? is the address of the pointer.

	; Let's actually show off some TRAP routines:

	GETC	; This will put a character from the keyboard into R0.
	OUT	; This will output the character in R0 to the monitor.
	IN	; This will request a character from the keyboard with some fancy
		; dialogue and automatically echo the character to the monitor.

	LEA R0,String	; Address of a String.
	PUTS		; This will print a null-terminated string pointed to by R0.
	ADD R0,R0,#6	; Increment our pointer
	PUTS		; The pointer is different, but still a null-terminated string.

	TRAP x25; It's HALT, but done the old fashion way.

String	.STRINGZ "Hello World!\n"	; This assembler directive gives us a null-terminated string.
	.END
