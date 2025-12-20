INCLUDE Irvine32.inc

.data
	i DWORD 5
	j DWORD 1
.code
main PROC
	MOV ECX, i
	outerLoop:
		push ECX
		MOV ECX, j
		MOV EAX, 1
		innerLoop:
			call WriteInt
			INC EAX
			Loop innerLoop
		call Crlf
		INC j
		pop ECX
		Loop outerLoop
	exit
main ENDP
END main