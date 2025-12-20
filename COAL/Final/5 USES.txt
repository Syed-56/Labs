INCLUDE Irvine32.inc

.data

.code
AddToRegisters PROTO USES eax ,val:DWORD
AddToRegisters PROC USES eax ,val:DWORD
	MOV EAX, val
	ADD EAX, 5
	RET
AddToRegisters ENDP

main PROC
	INVOKE AddToRegisters, 20
	exit
main ENDP

END main