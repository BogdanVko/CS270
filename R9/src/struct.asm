; Semicolons denote a comment in LC3 assembly. just like //

; The LC3 assembly language/simulator take the form of 16-bit addressable memory.
; All instructions and data are in this memory, with no distinction between the two.
; This first line of code is an assembler directive that tells us what address to
; start our program at, and is required for all programs.
	.ORIG x3000
	ADD R0,R0,R0	; This is just a sample instruction
	HALT		; We use HALT to stop our programs.
			; You can treat it like the end of a main function.

	.FILL x1000	; The .FILL directive tells the assembler to put
			; a predefined value into a memory space.

	.END
	; .END tells the assembler that it's done, and it also required for every
	; program.

; Aseemble this program and open it in the simulator. Notice that the ADD instruction
; is at memory address x3000, just like we told it to.
; What does the simulator say for the .FILL value? Why?
