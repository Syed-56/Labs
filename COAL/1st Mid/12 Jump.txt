INCLUDE Irvine32.inc

.data
	num BYTE 1
	number BYTE 2
.code
	MOV EAX, num
	JMP toPrint
	call WriteInt
	MOV EAX, number
	toPrint:
		call WriteInt
	exit
	;only EAX=num executes so printed is 1

	;have a look at infinite loop
	infinite:
		jmp infinite
main ENDP
END main
	