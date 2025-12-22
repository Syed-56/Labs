INCLUDE Irvine32.inc

.data
	num1 QWORD 12345678h
.code
write64BitHex PROTO USES EAX, highBits:DWORD, lowBits:DWORD
write64BitHex PROC USES EAX, highBits:DWORD, lowBits:DWORD
	MOV EAX, highBits
	call writeHex
	MOV EAX, lowBits
	call writeHex
	RET
write64BitHex ENDP

main PROC
	MOV EAX, DWORD PTR num1+4
	MOV EBX, DWORD PTR num1
	INVOKE write64BitHex, EAX, EBX
	exit
main ENDP

END main