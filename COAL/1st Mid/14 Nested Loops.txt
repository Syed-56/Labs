INCLUDE Irvine32.inc

.data
	msg BYTE "*",0
	i DWORD 5
	j DWORD 1
.code
main PROC
	MOV ECX, i
	outerLoop:
		MOV i, ECX
		MOV ECX, j
		innerLoop:
			MOV EDX, OFFSET msg
			call writeString
			Loop innerLoop
		call Crlf
		INC j
		MOV ECX, i
		Loop outerloop
	exit
main ENDP
END main