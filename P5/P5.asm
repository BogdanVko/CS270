; P5 Assignment
; Author: Bogdan
; Date:   29 feb 20
; Email:  <email>
; Class:  CS270
;
; Description: Implements the arithmetic, bitwise, and shift operations

;------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000
                BR Main

Functions       .FILL IntAdd         ; Address of IntAdd routine     (option 0)
                .FILL IntSub         ; Address of IntSub routine     (option 1)
                .FILL IntMul         ; Address of IntMul routine     (option 2)
                .FILL BinaryOr       ; Address of BinaryOr routine   (option 3)
                .FILL LeftShift      ; Address of LeftShift routine  (option 4)
                .FILL RightShift     ; Address of RightShift routine (option 5)

Main            LEA R0,Functions     ; The main routine calls one of the 
                LD  R1,Option        ; subroutines below based on the value of
                ADD R0,R0,R1         ; the Option parameter.
                LDR R0,R0,0          ;
                JSRR R0              ;
EndProg         HALT                 ;

; Parameters and return_write values for all functions
; Try changing the .BLKW 1 to .FILL xNNNN where N is a hexadecimal value or #NNNN
; where N is a decimal value, this can save you time by not having to set these 
; values in the simulator every time you run your code. This is the only change 
; you should make to this section.
Option          .FILL #0             ; Which function to call
Param1          .BLKW 1              ; Space to specify first parameter
Param2          .BLKW 1              ; Space to specify second parameter
Result          .BLKW 1              ; Space to store result

; End reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------

; You may add variables and functions after here as you see fit.


;R4 will be temp result storage

;------------------------------------------------------------------------------
IntAdd                               ; Result is Param1 + Param2
                                     ; Your code goes here (~4 lines)
	LD R0, Param1		;load parameters
	LD R1, Param2		;
	ADD R3, R0, R1		;add numbers
	ST R3, Result		;store R3 into result
                RET
;------------------------------------------------------------------------------
IntSub                               ; Result is Param1 - Param2
                                     ; Your code goes here (~6 lines)
	LD R0, Param1		;load parameters
	LD R1, Param2		;
	NOT R1, R1		;make R1 into NOT-R1
	ADD R1, R1, #1		;add 1 to R1 (two's compliment calculated)
	ADD R3, R0, R1		;add numbers (subtracting)
	ST R3, Result		;store result into R3
                RET
;------------------------------------------------------------------------------
IntMul
    AND R0, R0, #0 		
	LD R1, Param1		
	BRz return		
	LD R2, Param2		
	BRz return		




loop				
	ADD R2, R2, #-1		
	BRn return
	ADD R0, R0, R1
	BR loop		
return
	ST R0, Result

                RET
                
;------------------------------------------------------------------------------
BinaryOr
   LD R0, Param1	
		LD R1, Param2	


		NOT R0, R0
		NOT R1, R1	


		AND R2, R1, R0

		NOT R3, R2	
		ST R3, Result		;store result
		
                RET
;------------------------------------------------------------------------------
LeftShift
             	
		LD R0, Param1	
		LD R1, Param2



	Loop1
		ADD R0, R0, R0


		ADD R1, R1, #-1	
		BRnp Loop1	
		ST R0, Result		;store Result 




                RET
;------------------------------------------------------------------------------
RightShift                           ; Result is Param1 >> Param2
                                     ; (Fill vacant positions with 0's)
   LD R0, Param1		;load parameters -number to shift
	LD R1, Param2		;shift this many times
	AND R2, R2, #0		; 0000 0000 0000 0000
	AND R3, R3, #0		; 0000 0000 0000 0001 
	ADD R3, R3, #1		
	AND R4, R4, #0		 ;0000 0000 0000 0001 
	ADD R4, R4, #1

	
	
maskloop	
	ADD R3, R3, R3		
	ADD R1, R1, #-1 	
	BRp maskloop 		;if 0 go out
	BR inspect

shiftloop
	ADD R4, R4, R4
	ADD R3, R3, R3		;LEFT shift bits by one
	BRz return_write
	BR inspect

inspect
	AND R1, R3, R0		;inspect bit with da mask! Oh yeah
				;getting super complicated. nxt look might be wrong.
	BRz shiftloop
	ADD R2, R4, R2		;where to put? R2
	BR shiftloop				;shiftloop a little more
return_write
	ST R2, Result		;store and return_write
                RET
;------------------------------------------------------------------------------
                .END
