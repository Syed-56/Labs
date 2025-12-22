INCLUDE Irvine32.inc

.data
	var BYTE 11010011b
	msgEven BYTE "Even Parity", 0
	msgOdd BYTE "Odd Parity", 0
	count BYTE 0

.code

main PROC
	MOV BL,var
	XOR BL, 0
	JNP oddParity
	MOV EDX, OFFSET msgEven
	call writeString
	JMP next

	oddParity:
	MOV EDX, OFFSET msgOdd
	call writeString

	next:
	MOV AL, var
	MOV ECX,8
	call crlf
	looping:
		TEST AL,00000001
		JZ skip
		INC count
		skip:
		SHR AL,1
		LOOP looping

	MOVZX EAX, count
	call writeDec
	exit
main ENDP
END main