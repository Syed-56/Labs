INCLUDE Irvine32.inc

.data
	arr BYTE 1,2,3,4,5
	n DWORD ?
.code
main PROC
	MOV EAX, LENGTHOF arr
	MOV n, EAX
	XOR EDX, EDX
	MOV EBX, 2
	DIV EBX
	MOV ECX, EAX

	MOV ESI, OFFSET arr
	MOV EDI, OFFSET arr
	ADD EDI, n
	DEC EDI
	
	reverse:
		MOV AL, [ESI]
		MOV BL, [EDI]
		XCHG AL, BL
		MOV [ESI], AL
		MOV [EDI], BL
		INC ESI
		DEC EDI
		LOOP reverse

	MOV ECX, n
	print:
		MOV EAX, [ESI]
		call WriteDec
		LOOP print
	exit
main ENDP
END main