; Recitation 10
; Author: <name>
; Date:   <date>
; Email:  <email>
; Class:  CS270
; Description: copies least significant byte to most significant
;--------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000

                JSR copy           ; call function
                HALT

; Parameter and return value
; Try changing Param's .BLKW 1 to .FILL xNNNN where N is a hexadecimal value or #NNNN
; where N is a decimal value, this can save you time by not having to set these 
; values in the simulator every time you run your code. This is the only change 
; you should make to this section.
Param           .BLKW 1              ; space to specify parameter
Result          .BLKW 1              ; space to store result

; Constants, the use of One and Eight is optional
One             .FILL #1             ; the number 1 0001  
Eight           .FILL #8             ; the number 8 1000
Mask            .FILL x00ff          ; mask top bits

; End reserved section: do not change ANYTHING in reserved section!
;--------------------------------------------------------------------------
copy                                 ; Copy bits 7:0 to 15:8
                                     ; ~20 lines of assembly code
            
                LD R0,Param          ; load pattern
                ADD R1, R0, #0
                LD R2, Mask
                AND R1, R1, Mask

                ADD R2, R1, #0
                ADD R3, R1, #0
                LD R4, Eight

                loops
                ADD R3, R3, R3

                ADD R4, R4, #-1 ; 8 7 6 5 4 3 2 1
                BRp loop



                LD R4, Eight

                ; check if the bits in the source mask is in Parameter
                ; R2 is source mask
                ; R3 is dest
                ; R1 is the param
                ; ---
                loop2
                ADD R3, R3, #1 ; issue here with masks
                ADD R2, R2, R2
                ADD R3, R3, R3
                
                ;AND mask param
                AND R5, R2, R1

                AND R4, R4, #-1
                BRp loop2
                ;if 1 
                ;add 1 to dest

                ;shift source to left
                ;sheft dest to left
                ;8 times repteat

                ;endloop
                


                ST R1,Result         ; store result
                RET
;--------------------------------------------------------------------------
               .END

