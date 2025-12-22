INCLUDE Irvine32.inc

.data
	num1 DWORD 10
	num2 DWORD 20
.code

addNums PROC
	PUSH EBP
	MOV EBP, ESP
	SUB ESP, 4
	MOV EAX, [EBP+8]
	MOV EBX, [EBP+12]
	ADD EAX, EBX
	MOV [EBP-4], EAX	;local var place
	MOV ESP, EBP
	POP EBP
	RET 8	;doing like this is called STDCALL convention
	;doing ADD ESP, 8 then RET is called C-style convention
addNums ENDP

main PROC
	PUSH num1
	PUSH num2
	CALL addNums
	exit
main ENDP

END main