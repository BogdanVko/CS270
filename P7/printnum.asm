; Author: Fritz Sieker
;
; ------------------------------------------------------------------------
; Begin reserved section - do not change ANYTHING is this section
; except the .FILL values of option, data1, data2

               .ORIG x3000
               BR Main

option         .FILL 0          ; select routine to test
data1          .FILL 0          ; use ONLY for testing
data2          .FILL 0          ; use ONLY for testing

stackBase      .FILL X4000      ; initial sttack pointer

Main           LD R6,stackBase  ; initialize stack pointer
               LD R0,option     ; select routine to test
               BRZ testPrintNum ; option = 0 means test printNum

               ADD R0,R0,#-1
               BRZ testGetDigit ; option = 1 means test getDidit

               ADD R0,R0,#-1
               BRZ testDivRem   ; option = 2 means test divRem

               HALT             ; invalid option if here

testPrintNum                    ; call printNum(x, base)
               LD R0,data2
               PUSH R0          ; push base argument
               LD R0,data1
               PUSH R0          ; push value argument
               JSR printNum
               ADD R6,R6,#2     ; caller clean up 2 parameters
               BR endTest

testGetDigit                    ; call getChar(val)
               LD R0,data1
               PUSH R0          ; push argument (val to convert to ASCII)
               JSR getDigit     ; 
               POP R0           ; get the corresponding character
               ADD R6,R6,#1     ; caller clean up 1 parameter
               OUT              ; print the digit
               NEWLN
               BR endTest

testDivRem                      ; call divRem(num, denom, *quotient, *remainder)
               LEA R0,data2     ; get pointer to remainder (&data2)
               PUSH R0
               LEA R0,data1     ; get pointer to quotient (&data1)
               PUSH R0
               LD R0,data2
               PUSH R0          ; push demoninator
               LD R0,data1
               PUSH R0          ; push numerator
               JSR divRem       ; call routine
               ADD R6,R6,#4     ; caller clean up 4 parameters

endTest        LEA R0,endMsg
               PUTS
theEnd         HALT             ; look at data1/data2 for quotient/remainder

                                ; useful constants
endMsg         .STRINGz "\nTest complete!\n"

negSign        .FILL    x2D     ; ASCII '-'
digits         .STRINGZ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" ; up to base 36

; end reserved section

; ------------------------------------------------------------------------
; Author: your name goes here
; ------------------------------------------------------------------------
;
; C declaration: char getDigit (int val);

getDigit                        ; callee setup
        PUSH  R7
        PUSH R5
        ADD R5, R6, #-1      ;SP                  ; code for getDigit
        LDI R1, R5, #5 ;DEREFERENCE A PTR; R1 IS QUOTENT
        LDI R2, R5, #6 ;R2 IS REMAINDER
        LDR R3, R5, #4 ;R3 IS DEVISOR
        LDR R4, R5, #3 ;R4 IS NUMERNATOR

        NOT R3, R3
        ADD R3, R3, #1

        looper
        ADD R4, R4, R3
        BRp looper
        
                                ; callee cleanup
               RET              ; return
; ------------------------------------------------------------------------
;
; C declaration: void divRem(int num, int denom, int*quotient, int*remainder);
;quotient = numerator / divisor;
;remainder= numerator % divisor;
divRem                          ; callee setup

                                ; code for dicRem

                                ; callee cleanup
               RET              ; return
; ------------------------------------------------------------------------
;
; C declaration: void printNum (int val, int base);

printNum                        ; callee setup

                                ; code for printNum

                                ; callee cleanup
               RET              ; return
; ------------------------------------------------------------------------
               .END
