INCLUDE Irvine32.inc

.data
	array DWORD 20,10,40,30,60,50
	msg BYTE " ",0
.code

swap PROC USES ECX ESI , arr: PTR DWORD, n: DWORD
	MOV ECX, n
	MOV ESI, arr
	XOR EDX, EDX
	MOV EAX, n
	MOV EBX, 2
	DIV EBX
	CMP EDX, 0
	JE swapPairs
	DEC ECX
	

	swapPairs:
		MOV EAX, [ESI]
		MOV EBX, [ESI+4]
		MOV [ESI], EBX
		MOV [ESI+4], EAX
		ADD ESI, 4
		ADD ESI, 4
		DEC ECX
		LOOP swapPairs

	RET
swap ENDP

main PROC
	INVOKE swap, OFFSET array, LENGTHOF array
	MOV ESI, OFFSET array
	MOV ECX, LENGTHOF array
	print:
		MOV EAX, [ESI]
		call writeInt
		MOV EDX, OFFSET msg
		call writeString
		ADD ESI, TYPE array
		LOOP print
	exit
main ENDP
END main