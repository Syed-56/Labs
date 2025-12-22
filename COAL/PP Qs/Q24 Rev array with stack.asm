INCLUDE Irvine32.inc

.data
	arr DWORD 1,2,3,4,5
	len DWORD 5
.code

main PROC
	MOV ESI, OFFSET arr
	MOV ECX, len
	pushing:
		MOV EAX, [ESI]
		PUSH EAX
		ADD ESI, TYPE arr
		LOOP pushing

	MOV ESI, OFFSET arr
	MOV ECX, len
	popping:
		POP EAX
		MOV [ESI], EAX
		call writeInt
		ADD ESI, TYPE arr
		LOOP popping
	exit
main ENDP

END main