	.ORIG x3000
	; LEA loads the address of a label into a register.
	LEA R0,Label

	; Why would we need this? To use with LDR/STR (the R is for register).
	; These instructions take a register that holds a base address and
	; and offset from that address, just like an array.
	; In other words, R0 is like an array now, and we use LDR and STR
	; to access/modify it.

	; R0[0] = 1
	AND R1,R1,#0
	ADD R1,R1,#1	; R1 = 1
	STR R1,R0,#0	; R0[0] = R1

	; R0[3] = 2
	ADD R1,R1,#1
	STR R1,R0,#3

	; R0[R1] = 5
	ADD R2,R1,#3	; R2 = R1 + 3, R1 was 2 before, so R2 is 5
	ADD R0,R0,R1	; R0 + R1 is our Base + Offset. We have to do it ourselves.
	STR R2,R0,#0

	; LDR is pretty much identical.
	; R1 = R0[2]
	LEA R0,Label	; We changed R0 before, so we reset it here.
	LDR R1,R0,#2

	; The offset is a 6 bit signed value.

	HALT

Label	.BLKW x10 ; Basically an array of size 10.
	.END
