INCLUDE Irvine32.inc

.data
	num1 DWORD 10
	num2 DWORD 20
.code

addNums PROC
	ENTER 4,0	;3 steps combined here. 4 means 4 byte reserved for 1 local var
	MOV EAX, [EBP+8]
	MOV EBX, [EBP+12]
	ADD EAX, EBX
	MOV [EBP-4], EAX	;local var place
	LEAVE
	RET 8	;same as ADD ESP, 8 then RET
addNums ENDP

main PROC
	PUSH num1
	PUSH num2
	CALL addNums
	exit
main ENDP

END main