;doing like this using parameters dont need stackframe and enter leave thing
INCLUDE Irvine32.inc

.data
	num1 DWORD 10
	num2 DWORD 20
.code
addNums PROTO num1:DWORD, num2:PTR DWORD, num3:DWORD
addNums PROC num1: DWORD, num2:PTR DWORD, num3:DWORD
	MOV EAX, num1
	ADD EAX,[num2]
	ADD EAX, num3
	RET
addNums ENDP

main PROC
	MOV EBX, 30
	INVOKE addNums, num1, ADDR num2, EBX
	exit
main ENDP

END main