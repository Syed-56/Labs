INCLUDE Irvine32.inc

.data
	n DWORD ?
	msgInput BYTE "Enter n: ", 0
	msgSpace BYTE " ", 0
	number BYTE 1
	temp DWORD ?
.code
main PROC
	MOV EDX, OFFSET msgInput
	call WriteString
	call ReadInt
	MOV n, EAX

	MOV ECX, n
	OuterLoop:
		MOV temp, ECX
		MOV ECX, n
		InnerLoop:
			MOV EAX, number
			call WriteDec
			MOV EDX, OFFSET msgSpace
			call WriteString
			INC number
			LOOP InnerLoop
		Call Crlf
		MOV ECX, temp
		Loop OuterLoop
	exit
main ENDP
END main