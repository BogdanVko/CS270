; Recitation 8
; Author: <name>
; Date:   <date>
; Email:  <email>
; Class:  CS270
; Description: Computes N! (N-factorial) recursively
;-------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000
                BR Main
                
; Parameter and result
Param           .FILL x0004
Result          .BLKW 1

; Constants
Stack           .FILL x4000
One             .FILL #1
MinusOne        .FILL #-1

; End reserved section: do not change ANYTHING in reserved section!
;-------------------------------------------------------------------------------

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; int Factorial(int N)
; Returns N! (must be a recursive function)
;
Factorial       ADD R6, R6, #-1     ; Step 3: allocate space for return value
                PUSH R7             ; Step 4: push return address
                PUSH R5 ; Step 5: push previous frame pointer
                ADD R5, R6, #-1 ; Step 6: setup new frame pointer
                ADD R6, R6, #-1 ; Step 7: allocate space for local variable
                
                ;;;;;;;;;;;;;;;;;;;;; Step 8: body of the function
                
Checkpoint1     LDR   R0, R5, #4    ; Load parameter N into a register
                
                LD    R1, MinusOne  ; Calculate N - 1
                ADD   R2, R0, R1    ; R2 will contain N - 1
                
                ;__________________ ; Store N - 1 in the local variable
                
                BRnz  BaseCase      ; Detect base case (N <= 1)
                
                ;;;; Start of the recursive call
                
                ;__________________ ; Step 1: push parameter N - 1
                ;__________________ ; Step 2: call Factorial(N - 1)
                ;__________________ ; Step 13: retrieve return value into R2
                ;__________________ ; Step 14: remove parameter from stack
                
                LDR   R0, R5, #4    ; Multiply N * Factorial(N - 1)
                .ZERO R3            ; R3 will contain the product
MultiplyLoop    ADD   R3, R3, R2    ; Notice that by this point, R0 > 1
                ADD   R0, R0, #-1   ;
                BRp   MultiplyLoop  ;
                
                ;__________________ ; Make return value = N * Factorial(N - 1)
                
                BR    Finish
                
                ;;;; End of the recursive call
                
                ;;;; Start of the base case
                
BaseCase        LD    R0, One       ; Make return value = 1
                STR   R0, R5, #3    ;
                
                ;;;; End of the base case
                
                ;;;;;;;;;;;;;;;;;;;;; End of the body of the function
                
Finish          ;__________________ ; Step 9: remove local variable from stack
                ;__________________ ; Step 10: restore previous frame pointer
                ;__________________ ; Step 11: restore return address
Checkpoint2     RET                 ; Step 12: return to calling subroutine

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Entry point
; Calls Factorial(Param) and stores the return value in Result
;
Main            LD    R6, Stack     ; Initialize stack pointer
                LD    R5, Stack     ; Initialize frame pointer
                
                LD    R0, Param     ; Load parameter into a register
                
                ;__________________ ; Step 1: push parameter
                ;__________________ ; Step 2: call Factorial(Param)
                ;__________________ ; Step 13: retrieve return value
                ;__________________ ; Step 14: remove parameter from stack
                
                ;__________________ ; Store return value in Result
                
TheEnd          HALT
                
               .END
                