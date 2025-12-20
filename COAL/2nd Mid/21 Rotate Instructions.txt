INCLUDE Irvine32.inc

.data

.code 
main PROC
	MOV AL, 10001000b
	ROL AL, 1	;move bits to left but outplaced bits are wrapped around
	call writeBin

	MOV AL, 10001000b
	ROR AL, 2	;move bits to right and bits are wrapped around
	call writeBin

	MOV AL, 10110001b
	STC	;sets CF=1 and CLC make CF=0
	RCL AL, 1	;move bits to left but rightmost=CF and CF=leftmost

	MOV AL, 10110001b
	STC	;sets CF=1
	RCR AL, 1	;move bits to right but leftmost=CF and CF=rightmost
	exit
main ENDP
END main