; This code provides a simple calculator capable of reading
; postfix expressions and performing simple operations of
; subtraction, addition, multiplication, division, and exponents.
;
; PARTNERS: briolat2, kaylanw4, roylu2
;
.ORIG x3000
	
;your code goes here
	GET_INPUT    IN    			; get input value
	JSR EVALUATE     			; evaluate the input for numbers, operators, etc

LOAD_RESULT
    AND R5,R5,#0    			; clear R5
    ADD R5,R5,R0    			; load final answer into R5

	JSR PRINT_HEX    			; print the result

	STOP HALT        			; halt program

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

; convert to hex and print

    AND R3,R3,#0        	; clear R3
    ADD R3,R3,R5        	; load final answer into R3
    LD R1,FOUR            	; digit counter = 4

DIGIT_COUNT
    ADD R1,R1,#0
    BRz STOP            	; if digit counter = 0, stop
    LD R2,FOUR            	; bit counter = 4
    AND R7,R7,#0        	; reset R7
    
BIT_COUNT
    ADD R2,R2,#0
    BRz PRINT             	; if bit counter is 0, go to print the digit
    ADD R7,R7,R7        	; shift R7 left
    ADD R3,R3,#0        
    BRzp #1                	; if R3 z or p, don't add 1 to R7
    
    ADD R7,R7,#1        	; R7 + 1
    ADD R3,R3,R3         	; shift R3 left
    ADD R2,R2,#-1        	; decrement bit counter
    BRnzp BIT_COUNT        	; loop 4 times
    
PRINT
    AND R0,R0,#0        	; clear R0
    ADD R0,R7,#-9        	; compare digit with 9
    BRnz PRINT_NUMERICAL 	; if digit 0-9, go to PRINT_NUMERICAL
    LD R0,A             	; Load ASCII A
    ADD R0,R0,R7        	; R0<-R7+A-10
    ADD R0,R0,#-10       	; R0<-R7+A-10
    BRnzp DIG_LOOP_DONE 	; use OUT trap
    
PRINT_NUMERICAL 
    LD R0,ZERO            	; Load zero into R0
    ADD R0,R0,R7        	; R0<-R7+0
    DIG_LOOP_DONE OUT    	; use OUT trap
    ADD R1,R1,#-1
    BRnzp DIGIT_COUNT    	; loop to DIGIT_COUNT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here

	AND R2, R2, #0	; clear R2, R3, R4
	AND R3, R3, #0				
	AND R4, R4, #0
	
;your code goes here
CHECK_NUMBER
	LD R6, ASCII_9	; load negative ascii 9
	ADD R2, R0, R6	; compare input to -9
	BRp CHECK_EQUAL	; if outside of range, move on
	LD R6, ASCII_0	; load negative ascii 0			
	ADD R2, R0, R6	; compare input to -0
	BRn CHECK_EQUAL	; if outside of range, move on 
	ADD R0, R0, R6	; acquire decimal value 
	JSR PUSH		; push to stack
	BRnzp GET_INPUT ; next input
	
CHECK_EQUAL
	LD R6, ASCII_EQUAL	; load negative ascii =
	ADD R2, R0, R6		; compare input to =
	BRnp CHECK_SPACE	; if the result is not 0, move on
	JSR POP				; pop a value from the stack	
	LD R3, STACK_TOP	; load stack top and start
	LD R4, STACK_START	; into R3, R4
	NOT R4, R4			;
	ADD R4, R4, #1
	ADD R3, R3, R4		; Compare to check if stack is empty
	BRnp INVALID		; if not 0, invalid equation
	BRnzp LOAD_RESULT	; return 
	
CHECK_SPACE
	LD R6, ASCII_SPACE	; load negative ascii space		
	ADD R2, R0, R6		; compare to input
	BRz GET_INPUT		; if 0, get next input
	
CHECK_PLUS
	LD R6, ASCII_PLUS	; load negative ascii +
	ADD R2, R0, R6		; compare input to +
	BRnp CHECK_MINUS	; if not 0, move on
	JSR POP				; pop first value from stack
	ADD R5, R5, #0		
	BRp INVALID			; check underflow
	ADD R4, R4, R0		; load popped value into R4
	JSR POP				; pop second value
	ADD R5, R5, #0
	BRp INVALID			; check underflow again
	ADD R3, R3, R0		; load popped value into R3
	JSR PLUS			; jump to plus subroutine
	JSR PUSH			; push result back to stack
	BRnzp GET_INPUT		; get new input
	
CHECK_MINUS
	LD R6, ASCII_MINUS	; load negative ascii -
	ADD R2, R0, R6		; compare input to -
	BRnp CHECK_MUL		; if not 0, move on
	JSR POP				; pop first value from stack
	ADD R5, R5, #0		
	BRp INVALID			; check underflow
	ADD R4, R4, R0		; load popped value into R4
	JSR POP				; pop second value
	ADD R5, R5, #0
	BRp INVALID			; check underflow again
	ADD R3, R3, R0		; load popped value into R3
	JSR MIN				; jump to minus subroutine
	JSR PUSH			; push result back to stack
	BRnzp GET_INPUT		; get new input
	
CHECK_MUL
	LD R6, ASCII_MUL	; load negative ascii *
	ADD R2, R0, R6		; compare input to *
	BRnp CHECK_DIV		; if not 0, move on
	JSR POP				; pop first value from stack
	ADD R5, R5, #0		
	BRp INVALID			; check underflow
	ADD R4, R4, R0		; load popped value into R4
	JSR POP				; pop second value
	ADD R5, R5, #0
	BRp INVALID			; check underflow again
	ADD R3, R3, R0		; load popped value into R3
	JSR MUL				; jump to multiply subroutine
	JSR PUSH			; push result back to stack
	BRnzp GET_INPUT		; get new input
	
CHECK_DIV
	LD R6, ASCII_DIV	; load negative ascii /
	ADD R2, R0, R6		; compare input to /
	BRnp CHECK_EXP		; if not 0, move on
	JSR POP				; pop first value from stack
	ADD R5, R5, #0		
	BRp INVALID			; check underflow
	ADD R4, R4, R0		; load popped value into R4
	JSR POP				; pop second value
	ADD R5, R5, #0
	BRp INVALID			; check underflow again
	ADD R3, R3, R0		; load popped value into R3
	JSR DIV				; jump to divide subroutine
	JSR PUSH			; push result back to stack
	BRnzp GET_INPUT		; get new input
	
CHECK_EXP
	LD R6, ASCII_EXP	; load negative ascii ^
	ADD R2, R0, R6		; compare input to ^
	BRnp INVALID		; if not 0, must be invalid
	JSR POP				; pop first value from stack
	ADD R5, R5, #0		
	BRp INVALID			; check underflow
	ADD R4, R4, R0		; load popped value into R4
	JSR POP				; pop second value
	ADD R5, R5, #0
	BRp INVALID			; check underflow again
	ADD R3, R3, R0		; load popped value into R3
	JSR EXP				; jump to exponent subroutine
PLACEHOLDER	
	JSR PUSH			; push result back to stack
	BRnzp GET_INPUT		; get new input

INVALID 
	LEA R0, INPUT_INVALID	; load address of output into R0
	PUTS
	BRnzp STOP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	ADD R0, R3, R4
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
	ST R4, MIN_SAVER
	NOT R4, R4
	ADD R4, R4, #1
	ADD R0, R3, R4
	LD R4, MIN_SAVER
	RET
	MIN_SAVER .BLKW #1
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	ST R3, MUL_SAVER
	ST R4, MUL_SAVER2	;stores original R4 value
	AND R0, R0, #0
	ADD R4, R4, #0		;checks if R4 was already 0
	BRz #4
	ADD R0, R0, R3		;multiplication loop
	ADD R4, R4, #-1
	BRp #-3
	LD R3, MUL_SAVER
	LD R4, MUL_SAVER2	;restores original R4 value
	RET
	MUL_SAVER .BLKW #1
	MUL_SAVER2 .BLKW #1
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
    ST R3, DIV_SAVER
	ST R4, DIV_SAVER2
    AND R0, R0, #0
    NOT R4, R4
    ADD R4, R4, #1       ;complement value of R4
    ADD R3, R3, R4
    BRn #2
    ADD R0, R0, #1
    BRnzp #-4
    LD R3, DIV_SAVER
	LD R4, DIV_SAVER2
    RET
    DIV_SAVER  .BLKW #1
	DIV_SAVER2 .BLKW #1
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
    ST R3, EXP_SAVER
    ST R4, EXP_SAVER2
    ST R1, EXP_SAVER3
	ST R7, EXP_SAVER4
    AND R0, R0, #0        	;set both R0 and R1 to 0.
    AND R1, R1, #0
    
    ADD R1, R1, R4        	;set R1 as R4, acts as counter
    ADD R0, R0, R3        	;set value of R0 as R3
    ADD R1, R1, #-1        	;subtract counter, R1, by 1
    BRz #5                	;goes to done if R1 reaches zero
	
	AND R4, R4, #0
	ADD R4, R4, R3       	;move value of R3 into R4
    JSR MUL					;R0 = R3 * R4
	AND R3, R3, #0			;sets R3 as current total value
	ADD R3, R3, R0
    ADD R1, R1, #-1        	;decrement counter by 1
    BRp #-5
    
    LD R3, EXP_SAVER
    LD R4, EXP_SAVER2
    LD R1, EXP_SAVER3
	LD R7, EXP_SAVER4
    RET
    EXP_SAVER      .BLKW #1
    EXP_SAVER2     .BLKW #1
    EXP_SAVER3     .BLKW #1
	EXP_SAVER4 	   .BLKW #1
	
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;

FOUR        .FILL #4    ; ASCII value for 4
ZERO        .FILL #48   ; ASCII value for 0
A 			.FILL x0041 ; ASCII value for A

ASCII_0		.FILL #-48	; negative ASCII value for 0
ASCII_9		.FILL #-57	; negative ASCII value for 9
ASCII_EQUAL	.FILL #-61	; negative ASCII value for =	
ASCII_SPACE	.FILL #-32	; negative ASCII value for space
ASCII_PLUS	.FILL #-43	; negative ASCII value for +
ASCII_MINUS	.FILL #-45	; negative ASCII value for -
ASCII_MUL	.FILL #-42	; negative ASCII value for *
ASCII_DIV	.FILL #-47	; negative ASCII value for /
ASCII_EXP	.FILL #-94	; negative ASCII value for ^

INPUT_INVALID	.STRINGZ "Invalid Expression"

.END
