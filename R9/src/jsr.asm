	.ORIG x3000
	; Instead of having functions like C or methods like Java,
	; the LC3 has subroutines. There aren't any strict rules for
	; subroutines, but instead, just some general guidelines
	; to help keep programming easier.

	; We use JSR (Jump SubRoutine) and JSRR (the extra R for Register)
	; to go to a subroutine, and RET (return) to get back. RET requires
	; that R7 is the same as it was after JSR/JSRR was executed-
	; we'll get more into that later in the course.
	
	; This program is a simple calculator- it only does addition,
	; subtraction, or ANDing. It assumes that the inputs are set to the desired
	; values, and does addition if Option = 0, subtraction if Option = 1,
	; and bitwise AND if Option = 2. The result is placed into the 
	; 'Output' location.
	; Yes- we have massively overcomplicated these by making them subroutines.

	; This is a common structure for programs- we have important
	; labels at the top and use an unconditional BR to skip to
	; a 'Main' subroutine.
	BRnzp Main
Input1	.BLKW x1	; The first operand
Input2	.BLKW x1	; The second operand
Output	.BLKW x1	; The result
Option	.BLKW x1	; Option == 0 ? Add : Subtract;
	; This portion is strange, but consider it to be an array of
	; pointers to the beginning of our functions. In this case, it's
	; only 3 functions, but it is how many of the later assignments work.
	; It also teaches us something useful- a .FILL value can take a label,
	; and it will fill with the address of that label.
Functions .FILL Addition
	  .FILL Subtraction
	  .FILL BitAnd
Main	LD R0,Input1	; Our functions assume R0 and R1 are set as preconditions,
	LD R1,Input2	; so we load them here.
	LD R2,Option	; Now, we do a base + offset to determine which
	LEA R3,Functions; Function we want to call.
	ADD R2,R2,R3	
	JSRR R2		; JSRR allows us to do a variable subroutine call, whereas
			; JSR always calls the same function.
	ST R0,Option	; R0 is always the solution.
	HALT


	; Precondition: R0 and R1 contain operands to be added
	; Postcondition: R0 = R0 + R1
Addition
	ADD R0,R0,R1
	; The return instruction takes us back to the previous function.
	RET	; RET is a macro for 'JMP R7'

	; Precondition: R0 and R1 contain operands
	; Postcondition: R0 = R0 - R1
SaveR7	.BLKW x1
Subtraction
	NOT R1,R1
	ADD R1,R1,#1
	ST R7,SaveR7	; RET requires that R7 is the same as it was before,
	JSR Addition	; and the JSR instruction changes R7, so we have to
	LD R7,SaveR7	; save and restore R7 in order to RET properly.
	RET		; What happens if we don't save R7?

	; Precondition: R0 and R1 contain operands
	; Postcondition: R0 = R0 & R1
BitAnd
	AND R0,R0,R1
	RET

	; Notice that all of the subroutines RET to Main- none of them execute HALT
	; on their own. This best represents the activation records/stack that happens
	; in Java and C, but is not always required. If we had no action to take in
	; Main after we return, we could instead use JMP in place of JSRR and
	; HALT in place of RET. For all assignments, you must RET to the HALT instruction
	; in the main routine, and cannot HALT within your own subroutine. 
	.END
