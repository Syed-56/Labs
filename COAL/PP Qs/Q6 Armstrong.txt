INCLUDE Irvine32.inc

.data
	;153
	num1 DWORD 1
	num2 DWORD 5
	num3 DWORD 3
	num1arm DWORD ?
	num2arm DWORD ?
	num3arm DWORD ?
	total DWORD ?
	digits DWORD 3
	original DWORD 153
	msgEqual BYTE "Armstrong", 0
	msgNotEqual BYTE "Not Armstrong", 0

.code
main PROC
	MOV ECX, digits
	DEC ECX
	MOV EAX, num1
	MOV EBX, num1
	multiply1:
		PUSH ECX
		MOV ECX, num1
		DEC ECX
		notMUL1:
			ADD EAX, EBX
			LOOP notMUL1
		POP ECX
		MOV EBX, EAX
		LOOP multiply1
	MOV num1arm, EAX

	XOR EAX, EAX
	MOV ECX, digits
	DEC ECX
	MOV EAX, num2
	MOV EBX, num2
	multiply2:
		PUSH ECX
		MOV ECX, num2
		DEC ECX
		notMUL2:
			ADD EAX, EBX
			LOOP notMUL2
		POP ECX
		MOV EBX, EAX
		LOOP multiply2
	MOV num2arm, EAX

	XOR EAX, EAX
	MOV ECX, digits
	DEC ECX
	MOV EAX, num3
	MOV EBX, num3
	multiply3:
		PUSH ECX
		MOV ECX, num3
		DEC ECX
		notMUL3:
			ADD EAX, EBX
			LOOP notMUL3
		POP ECX
		MOV EBX, EAX
		LOOP multiply3
	MOV num3arm, EAX

	XOR EAX, EAX
	MOV EAX, num1arm
	ADD EAX, num2arm
	ADD EAX, num3arm
	MOV total, EAX
	call WriteDec
	call Crlf

	CMP EAX, original
	JE equal

	notequal:
		MOV EDX, OFFSET msgNotEqual
		call WriteString
		JMP done
	equal:
		MOV EDX, OFFSET msgEqual
		call WriteString
		JMP done
	done:
		exit
main ENDP
END main