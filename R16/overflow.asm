                .ORIG x3000         
Main            
                LD R6, Stack        ; initialize stack pointer
                LD R5, Stack        ; initialize frame pointer
                LD R0, ParamValue   ; load parameter that will be passed to ProcessHexData
                PUSH R0             ;                                
                JSR ProcessHexData  ; call ProcessHexData
                ADD R6, R6, #2      ; clean up stack, 1 return value, 1 pram                    
Break1          HALT
ProcessHexData
                ADD R6, R6, #-1     ; allocate space for return value
                PUSH R7             ; push return address
                PUSH R5             ; push previous frame pointer
                ADD R5, R6, #-1     ; setup new frame pointer; 
                ADD R6, R6, #-2     ; allocate space for local buffer of size 2
                ADD R0, R6, #0      ; R0: address of first buffer entry
                TRAP x28            ; call GETH system routine
                TRAP x27            ; move output to next line
                ; Do something interesting with binary data in local buffer
                LD R0, RetValue     ;
                STR R0, R5, #3      ; save return value on stack
                                    ; 
                ADD R6, R6, #2      ; remove local buffer from stack
                POP R5              ; restore previous frame pointer
                POP R7              ; restore return address
                ; could these values (R5, R7) have been modified by GETH?
Break2          RET                 
PrivateFunction                
                ADD R6, R6, #-1     ; allocate space for return value
                PUSH R7             ; push return address
                PUSH R5             ; push previous frame pointer
                ADD R5, R6, #-1     ; setup new frame pointer
                ADD R6, R6, #-5     ; allocate space for local buffer of size 5
                LEA R0, Message     ; R0: address of first char of Message
                PUTS                ; display Message
                TRAP x27            ; move output to next line
                ADD R6, R6, #5      ; remove local buffer from stack
                POP R5              ; restore previous frame pointer
                POP R7              ; restore return address                   
Break3          HALT

; Constants
Stack           .FILL x3040         ; starting address of the stack
ParamValue      .FILL #-1           ; used for locating param on stack
RetValue        .FILL xBBBB         ; used for locating return value on stack
Message         .STRINGZ "@#$@"   	; overflow message, short so stack can be close to data for easy viewing
SecretMessage   .STRINGZ "!!!"      ; message that should be printed by extra credit code                      
               .END                


