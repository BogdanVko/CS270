; IO Recitation
; Author: <name>
; Date:   <date>
; Email:  <email>
; Class:  CS270
; Description: Converts hexadecimal number in ASCII to binary number
;--------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000

                JSR read            ; read number from keyboard
                JSR convert         ; convert to binary number
                HALT

; Decinal value
Result          .BLKW 1             ; space to store result

; String value
String          .BLKW 4

; End reserved section: do not change ANYTHING in reserved section!
;--------------------------------------------------------------------------

; Constants
Four            .FILL 4             ; the number 4
AsciiA          .FILL xFFBF         ; minus ASCII 'A'
Ascii0          .FILL xFFD0         ; minus ASCII '0'
Prompt          .STRINGZ "Hexadecimal: " 
;--------------------------------------------------------------------------
; read - reads four ASCII digits from console and stores them in string

read_ra         .BLKW 1             ; return address
read            ST R7,read_ra       ; save return address

                LD R1,Four          ; R1 = loop counter = 4
                LEA R2, String
                LEA R0, Prompt       ; R2 = string pointer
                PUTS
                                    ; Display prompt using PUTS
                                    ; 
loop0           GETC                ; Input character using GETC
                OUT                 ; Output character using OUT

                STR R0,R2,0         ; Store next character
                ADD R2, R2, #1      ; Increment pointer
                ADD R1,R1,-1        ; Decrement counter
                BRp loop0           ; Loop if positive

                LD R7,read_ra       ; restore return address           
                RET
;--------------------------------------------------------------------------
; convert - converts four ASCII digits to binary number

convert_ra      .BLKW 1             ; return address
convert                             ; save return address

                LD R1,Four          ; R1 = loop counter = 4
                LEA R2, String                    ; R2 = string pointer
                AND R3, R3, #0
                                   ; R3 = result = 0
loop1           LDR R0, R2, #0                   ; R0 = load next character
                LD R4,AsciiA 
                                 ; Minus 'A'
                ADD R4,R0,R4        ; Compare 'A'
                BRzp letter                    ; Branch to letter if >= 'A'

digit           LD R4,Ascii0        ; Minus '0'
                ADD R4,R0,R4        ; Compare '0'
                BR continue         ; Processed digit

letter          ADD R4,R4,10        ; Letter to digit

continue                            ; result *= 16
        ADD R3, R3, R3
        ADD R3, R3, R3
        ADD R3, R3, R3
        ADD R3, R3, R3
                                         ; 
                                    ; 
        ADD R3, R3, R4 
        
        
                                  ; result += digit
        ADD R2, R2, #1                            ; Increment pointer
        ADD R1, R1, #-1                            ; Decrement counter
                BRp loop1
                           ; Loop if positive
                ST R3,Result        ; Store result

                                    ; restore return address           
                RET
;--------------------------------------------------------------------------
               .END

