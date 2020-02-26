	.ORIG x3000
	; LDI and STI can be two of the more confusing instructions in the LC3.
	; However, they are identical to pointers in C.

	; We have to pointers to integers at the end.
	; Let's do *Point2 = *Point1
	LDI R0,Point1
	STI R0,Point2

	HALT

Point1	.FILL x3005 ; Address of the int is x3005
Point2	.FILL x3006 ; Address of the int is x3006
Val1	.FILL x1234 ; 
Val2 	.FILL x0000
	.END
