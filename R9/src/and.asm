	.ORIG x3000
	; AND is also intuitive.
	; Set R1 and R2 before this instruction:
	AND R0,R1,R2

	; You can use an immediate value, too:
	AND R0,R1,xF
	; I only care about the lowest 4 bits.

	; It's signed, for some reason.
	AND R0,R1,x-10
	; x-10 = ~(x10)+x1 = xFFF0
	; I care about everything except the lowest 4 bits.

	; The immediate value is almost always used for one reason:
	AND R0,R0,#0
	; This is the quickest way to set a register to 0.
	; You can never assume that a register has a value in it unless
	; you do something like this to guarantee it, first.

	HALT
	.END
