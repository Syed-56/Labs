INCLUDE Irvine32.inc

.data
	arr WORD 5 DUP(?)
	msgInput BYTE "Enter Arr:- ",0
.code
main PROC
	MOV ECX, LENGTHOF arr
	MOV ESI, 0
	input:
		MOV EDX, OFFSET msgInput
		call WriteString
		call Crlf
		call ReadInt
		MOV [arr + ESI * TYPE arr], AX
		INC ESI
		LOOP input:
	
	MOV ECX, 5
	MOV ESI, 0
	swap:
		MOV AX, arr[ESI * TYPE arr]
		MOV BL, AL
		MOV AL, AH
		MOV AH, BL
		MOV [arr + ESI * TYPE arr], AX
		INC ESI
		LOOP swap
	
	MOV ECX, 5
	MOV ESI, OFFSET arr
	Print:
		MOV AX, [ESI]
		call WriteDec
		call Crlf
		Loop Print
		
	exit
main ENDP
END main	