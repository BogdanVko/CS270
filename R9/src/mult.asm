	.ORIG x3000
IntMul			; Your code goes here
			; Solution has ~9 instructions
			; Don't use registers 5, 6, or 7
	HALT
; Try changing the .BLKW 1 to .FILL xNNNN where N is a hexadecimal value or #NNNN
; where N is a decimal value, this can save you time by not having to set these 
; values in the simulator every time you run your code. This is the only change 
; you should make to this section.
Param1	.BLKW 1		; Space to specify first parameter
Param2	.BLKW 1		; Space to specify second parameter
Result	.BLKW 1		; Space to store result
	.END

