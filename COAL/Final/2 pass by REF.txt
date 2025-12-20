INCLUDE Irvine32.inc

.data
	num1 DWORD 10
	num2 DWORD 20
.code

addNums PROC
	PUSH EBP
	MOV EBP, ESP
	SUB ESP, 4
	LEA EAX, [EBP+8]
	LEA EBX, [EBP+12]
	MOV ECX, [EBX]
	ADD [EAX], ECX
	MOV [EBP-4], [EAX]	;local var place
	MOV ESP, EBP
	POP EBP
	RET 8	;same as ADD ESP, 8 then RET
addNums ENDP

main PROC
	PUSH OFFSET num1
	PUSH OFFSET num2	;pushing address
	CALL addNums
	exit
main ENDP

END main