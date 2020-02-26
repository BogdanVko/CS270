	.ORIG x3000
	; Not is intuitive, as well.

	; R0 = xFFFF
	AND R0,R0,#0
	NOT R0,R0

	; It can also be used for two's complement negation, however.
	; Set R0 to some arbritary value.
	NOT R1,R0
	ADD R1,R1,#1
	; Flip all the bits and add 1.
	ADD R0,R0,R1
	; Add a number to it's opposite- you get 0.

	; Finally, it can be used to turn AND into OR
	; DeMorgan's Law: R0 | R1 = ~(~R0 & ~R1)
	NOT R0,R0	; Negate the inputs
	NOT R1,R1
	AND R0,R0,R1
	NOT R0,R0	; Negate the output

	HALT
	.END
