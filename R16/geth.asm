; ************************** GETH *************************************

TRAP_GETH_RA            .BLKW 1
TRAP_GETH_R0            .BLKW 1
TRAP_GETH_R1            .BLKW 1
TRAP_GETH_R2            .BLKW 1
TRAP_GETH_R3            .BLKW 1
TRAP_GETH_R4            .BLKW 1
TRAP_GETH_buf_addr      .BLKW 1
TRAP_GETH_String       	.BLKW 4             ; store chars that will make up word
TRAP_GETH_Four         	.FILL 4             ; the number 4
TRAP_GETH_AsciiA       	.FILL xFFBF         ; minus ASCII 'A'
TRAP_GETH_Ascii0       	.FILL xFFD0         ; minus ASCII '0'
TRAP_GETH_StopChar    	.FILL xFF8F         ; minus ASCII 'q' 
TRAP_GETH_Prompt       	.STRINGZ "Hexadecimal: " 
TRAP_GETH_StopFlag     	.BLKW 1             ; if 0 stop reading characters
TRAP_GETH_One          	.FILL #1            ; the number 1

TRAP_GETH                                   ; read in hex and pack into LC3 words
                                            ; terminated by a NULL word
                ST R0, TRAP_GETH_buf_addr   ; address of buffer to pack with hex 
                ST R7, TRAP_GETH_RA 
                ST R1, TRAP_GETH_R1
                ST R2, TRAP_GETH_R2
                ST R3, TRAP_GETH_R3
                ST R4, TRAP_GETH_R4

                LD R0, TRAP_GETH_One        ; R0 = 1
                ST R0, TRAP_GETH_StopFlag   ; initialize TRAP_GETH_StopFlag to 1
                LEA R0,TRAP_GETH_Prompt
                PUTS                        ; display prompt

 TRAP_GETH_loop 
                JSR TRAP_GETH_READ          ; read number from keyboard
				LD R1, TRAP_GETH_StopFlag   ; 
				BRz TRAP_GETH_end
                JSR TRAP_GETH_CONV          ; convert to binary number
                LD R0, TRAP_GETH_buf_addr
                ADD R0, R0, #1              ; increment storage location
                ST R0, TRAP_GETH_buf_addr   ; save location
                BRnzp TRAP_GETH_loop        ; only loop if TRAP_GETH_StopFlag not equal to 0

TRAP_GETH_end
				LD R0, TRAP_GETH_buf_addr	; R1: address of buf
                STR R1, R0, #1               ; append R1 (NULL) to buf
                LD R1, TRAP_GETH_R1
                LD R2, TRAP_GETH_R2
                LD R3, TRAP_GETH_R3
                LD R4, TRAP_GETH_R4
                LD R7, TRAP_GETH_RA 
                RET        

;--------------------------------------------------------------------------
; read - reads four ASCII digits from console and stores them in string

TRAP_GETH_read_ra 	.BLKW 1                 ; return address

TRAP_GETH_READ  ST R7, TRAP_GETH_read_ra    ; save return

                LD R3, TRAP_GETH_StopChar 	; R3 = stop character
                LD R1,TRAP_GETH_Four        ; R1 = loop counter = 4
                LEA R2,TRAP_GETH_String     ; R2 = string pointer

TRAP_GETH_READ_loop           
				GETC                        ; GETC function
                OUT                         ; OUT function
                ADD R4, R3, R0              ; Done with input?
                BRnp TRAP_GETH_READ_continue 
                ST R4, TRAP_GETH_StopFlag   ; Set TRAP_GETH_StopFlag
                BRnzp TRAP_GETH_READ_END    ;

TRAP_GETH_READ_continue        
				STR R0,R2,0                 ; Store character
                ADD R2,R2,1                 ; Increment pointer
                ADD R1,R1,-1                ; Decrement counter
                BRp TRAP_GETH_READ_loop    ; Loop if positive

TRAP_GETH_READ_END
                LD R7,TRAP_GETH_read_ra     ; restore return address           
                RET
;--------------------------------------------------------------------------
; convert - converts four ASCII digits to binary number

TRAP_GETH_conv_ra	.BLKW 1             	; return address

TRAP_GETH_CONV  ST R7, TRAP_GETH_conv_ra    ; save return

                LD R1,TRAP_GETH_Four        ; R1 = loop counter = 4
                LEA R2,TRAP_GETH_String     ; R2 = string pointer
                AND R3,R3,0                 ; R3 = result = 0

TRAP_GETH_CONV_loop
				LDR R0,R2,0                 ; R0 = next character
                LD R4,TRAP_GETH_AsciiA      ; Minus 'A'
                ADD R4,R0,R4                ; Compare 'A'
                BRzp TRAP_GETH_CONV_letter  ; Assume letter

TRAP_GETH_CONV_digit           
				LD R4,TRAP_GETH_Ascii0      ; Minus '0'
                ADD R4,R0,R4                ; Compare '0'
                BR TRAP_GETH_CONV_continue  ; Processed digit

TRAP_GETH_CONV_letter          
				ADD R4,R4, #10              ; Letter to digit

TRAP_GETH_CONV_continue        
				ADD R3,R3,R3                ; result *= 2 (times 2)
                ADD R3,R3,R3                ; result *= 2 (times 4)
                ADD R3,R3,R3                ; result *= 2 (times 8)
                ADD R3,R3,R3                ; result *= 2 (times 16)
                ADD R3,R3,R4                ; result += digit
                ADD R2,R2,1                 ; Increment pointer
                ADD R1,R1,-1                ; Decrement counter
                BRp TRAP_GETH_CONV_loop    	; Loop if positive
                STI R3, TRAP_GETH_buf_addr  ; Store result at address stored in buf_addr
                LD R7, TRAP_GETH_conv_ra ; restore return                
                RET

	
