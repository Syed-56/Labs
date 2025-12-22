INCLUDE Irvine32.inc
.data
	msg BYTE "natluS sI sihT", 0
	rev BYTE SIZEOF msg DUP(?)
.code
main PROC
	MOV EDX, OFFSET msg
	call WriteString
	XOR EDX, EDX
	
	MOV ECX, LENGTHOF msg
	DEC ECX
	MOV ESI, OFFSET msg
	ADD ESI, ECX
	DEC ESI
	MOV EDI, OFFSET rev

	copy:
		MOV AL, [ESI]
		MOV [EDI], AL
		DEC ESI
		INC EDI
		LOOP copy
	MOV BYTE PTR [EDI], 0
	call Crlf
	MOV EDX, OFFSET rev
	call WriteString
	exit
main ENDP
END main