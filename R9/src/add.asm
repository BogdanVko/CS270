	.ORIG x3000
	; ADD is pretty intuitive:
	; Set R1 and R2 to some values before running this instruction.
	ADD R0,R1,R2 ; R0 = R1 + R2

	; You can add an 'immediate' value to it as well:
	ADD R0,R0,#1 ; R0++

	; The immediate value is signed, too
	ADD R0,R0,#-1 ; R0--

	; Or, you can use hex:
	ADD R0,R0,x-1 ; R0--
	; Note that you can't do ADD R0,R0,xFFFF, or any similar alternative.
	; Even though -1 is FFFF, it simply doesn't work.

	; ADD can do some pretty cool things, however:
	ADD R0,R0,R0
	; R0 + R0 = 2*R0 = R0 << 1

	HALT
	.END
