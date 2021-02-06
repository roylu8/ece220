;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; Partners: briolat2, kaylanw4

; This PRINT_HIST function is used to print the amount of every letter that
; appears within a string. This was done by first looping through the entire
; alphabet and have an extra slot for every other symbol (total of 27). Next,
; you will go through each letter and convert it's binary amount into a hex,
; which is then printed on the screen.
	
	; R0 - used to print and counter for 4 bits
	; R1 - 27 loops
	; R2 - starting ascii value
	; R3 - current address of histogram (will be modified for bit shifting)
	; R4 - counter for 4 hex
	; R5 - current value of hex
	; R6 - current address of histogram
	; R7 - value holder of current hex
	
	LD R6, HIST_ADDR	; load starting address of histogram to R6
	
	LD R1, NUM_BINS		; 27 loops
	
	LD R2, ASCII_START	; starting ascii value - @
	
PRINT_LOOP				; main print loop
	ADD R1, R1, #0		
	BRz DONE			; branch to DONE if counter reaches 0
	AND R0, R0, #0		; clear R0
	ADD R0, R2, #0		; print current ascii value
	OUT
	LD R0, ASCII_SPACE
	OUT					; print space after current ascii value
	
HEX_LOOP				; start of hex loop
	AND R3, R3, #0		; clear R3
	LDR R3, R6, #0		; load current value of histogram into R3
	AND R4, R4, #0		; clear R4
	ADD R4, R4, #4		; set loop to 4	(for hex counter)
	
	
RESET
	AND R0, R0, #0
	ADD R0, R0, #4		; set loop to 4 (for bit counter)
	AND R7, R7, #0		; clears R7
	
BIT_LOOP
	ADD R0, R0, #0
	BRz PRINT_HEX		; if bit counter reaches zero, goes to PRINT_HEX to print corresponding hex value
	
	ADD R7, R7, R7		; shift R7 left by one for next bit value
	ADD R3, R3, #0		; checks if R3 is zero or positive
	BRzp #1				; if so, skips the next step to avoid adding an additional bit
	
	ADD R7, R7, #1		; copies the current bit value into R7
	
	ADD R0, R0, #-1		; decrement counter by 1
	ADD R3, R3, R3		; shift R4 left by one for next bit value
	
	BRnzp BIT_LOOP
	
PRINT_HEX				; prints the hex value

	AND R0, R0, #0		; clear R0
	ADD R0, R7, #-9		; put the value of hex into R0
	BRp PRINT_HEX_TWO	; branch to PRINT_HEX_TWO if hex is greater than 9
	LD R0, ASCII_ZERO	; load the starting value of 0 in ascii
	ADD R0, R0, R7		; add offset value of R7 to R0
	OUT					; print to console
	ADD R4, R4, #-1		; decrement hex counter
	BRp RESET			; branch to RESET if the chunk of bits were converted
	BRnzp READY_NEXT_HEX ; branch to READY_NEXT_HEX if all bits were converted
	
PRINT_HEX_TWO			; prints the hex value 2
	AND R0, R0, #0		; clear R0
	LD R0, ASCII_A		; load the starting value of A in ascii
	ADD R0, R0, R7
	ADD R0, R0, #-10	; add offset value of R7 to R0
	OUT					; print to console
	ADD R4, R4, #-1		; decrement hex counter
	BRp RESET			; branch to RESET if the chunk of bits were converted
	BRnzp READY_NEXT_HEX ; branch to READY_NEXT_HEX if all bits were converted
	
READY_NEXT_HEX
	ADD R2, R2, #1		; increment ascii counter
	ADD R6, R6, #1		; increment histogram address by 1
	ADD R1, R1, #-1		; decrement one from the 27 characters
	LD R0, ASCII_NL		; load hex of new line
	OUT					; print a new line
	BRnzp PRINT_LOOP	; goes to character in histogram

DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00 ; histogram starting address
STR_START	.FILL x4000	; string starting add ress

ASCII_START	.FILL x40   ; character used for @
ASCII_SPACE .FILL x20	; character used for space
ASCII_NL 	.FILL xA	; character used for new line
ASCII_ZERO 	.FILL x30   ; the ASCII value of '0'
ASCII_A		.FILL x41	; the ASCII value of 'A'

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
