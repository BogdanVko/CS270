	.ORIG x3000
	; BR is the only conditional instruction in the LC3,
	; which makes it vital to control logic.

	; The LC3 has a Condition Code (CC) which is always set to one of three states-
	; Negative, Zero, or Positive.
	; This is set by almost any instruction that sets a register to a value.
	; The full list is:
	; ADD, AND, NOT, LD, LDI, LDR, LEA
	; Only those commands set the CC. No other commands do, including those
	; we haven't covered yet (TRAP doesn't set the CC, but may run code which does).
	; Yes, it's weird that LEA sets the CC, but it does.

	; Let's set the CC to zero:
	AND R0,R0,#0
	; To positive:
	ADD R0,R0,#1
	; To negative:
	NOT R0,R0

	; It might not be obvious that the CC is negative, but the rule is simple-
	; CC is negative if MSB is 1, zero if all bits are 0, and positive otherwise.

	; Let's do a BR:
	BRn Skip	;
	ADD R0,R0,#5	; This won't happen.
Skip
	; Br takes a label (PCOffset) to go to if the CC matches it's NZP condition.
	; The CC will only ever be N, Z, or P, but BR can take multiple conditions:
	BRzp Skip2
	AND R0,R0,#0	; This does happen.
Skip2

	; The logic is slightly backwards from an if statement, because it
	; skips if the condition is true.
	; The first BR is equivalent to:
	; if(R0 >= 0) // Because R0 was the last register set
	;     R0 += 5

	; BR is also used to do loops.
	AND R1,R1,#0
	ADD R1,R1,#1	; R1 = 1
	ADD R0,R0,#8 	; R0 = 8 (it was already 0)
Loop	BRnz LoopEnd	; while(R0 > 0) { // only because R0 is always the last register set
	ADD R1,R1,R1	; R1 << 1;
	ADD R0,R0,#-1	; R0--;
	BRnzp Loop	; } // BRnzp is unconditional
LoopEnd			; You can also do BR Loop- it is equivalent

	; That loop just computes 1 << 8.

	; Sometimes, a do while style loop is cleaner in LC3.
	; Lets left shift R1 8 more times:
	ADD R0,R0,#8	; R0 = 8 again, because it was 0 after the last loop.
Loop2	ADD R1,R1,R1	; do {
	ADD R0,R0,#-1	; // statements
	BRp Loop2	; } while(R0 > 0);

	HALT
; Let's say that before a branch, you need to set the CC to the value
; of a specific register without modifying the value in that register.
; How would you do it?
	.END
