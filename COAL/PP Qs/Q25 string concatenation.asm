INCLUDE Irvine32.inc

.data
	str1 BYTE "HEllO ", 0
	str2 BYTE "WORLD", 0

.code

concat PROC USES ESI EDI EAX ECX, msg1: PTR BYTE, msg2: PTR BYTE
	MOV ESI, msg2
	MOV EDI, msg1
	CLD
	MOV AL, 0

	findEnd:
		CMP BYTE PTR [EDI], AL
		JE copyStr
		INC EDI
		JMP findEnd

	copyStr:
		MOV AL, [ESI]
		MOV [EDI], AL
		INC ESI
		INC EDI
		CMP AL, 0
		JNE copyStr
	RET
concat ENDP

main PROC
	INVOKE concat, ADDR str1, ADDR str2
	MOV EDX, OFFSET str1
	call writeString
	exit
main ENDP

END main