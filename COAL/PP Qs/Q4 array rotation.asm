INCLUDE Irvine32.inc

.data
	arr SBYTE 5 DUP(?)
	msgArr BYTE "Array:- ", 0
	msgInput2 BYTE " Element: ", 0
	msgSpace BYTE " , ", 0
	msgRotate BYTE "After Rotation: "
.code
main PROC
	MOV EDX, OFFSET msgArr
	call WriteString
	call Crlf
	MOV ECX, 5
	MOV ESI, OFFSET arr

	input:
		MOV EAX, 5
		ADD EAX, 1
		SUB EAX, ECX
		call Crlf
		call WriteDec
		MOV EDX, OFFSET msgInput2
		call WriteString

		MOV EDX, ESI
		call ReadInt	
		MOV [ESI], AL
		INC ESI
		LOOP input

	call Crlf
	MOV EDX, OFFSET msgArr
	call WriteString
	MOV ESI, OFFSET arr
	MOV ECX, 5
	output:
		MOVSX EAX, BYTE PTR [ESI]
		call WriteInt
		MOV EDX, OFFSET msgSpace
		call WriteString
		INC ESI
		LOOP output

	MOV EDX, OFFSET msgRotate
	call Crlf
	call WriteString
	MOV ESI, OFFSET arr
	MOV ECX, 5
	MOV BL, BYTE PTR [ESI+ECX-1]

	rotating:
		MOV AL, BYTE PTR [ESI+ECX-2]
		MOV BYTE PTR [ESI+ECX-1], AL
		LOOP rotating

	MOV BYTE PTR [ESI], BL

	MOV ESI, OFFSET arr
	MOV ECX, 5
	outputRotate:
		MOVSX EAX, BYTE PTR [ESI]
		call WriteInt
		MOV EDX, OFFSET msgSpace
		call WriteString
		INC ESI
		LOOP outputRotate
	exit
main ENDP
END main