INCLUDE Irvine32.inc

.data
	var DWORD ?
.code

fact PROC USES EAX, ECX
	CMP ECX, 1
	JLE return
	MUL EAX, ECX
	DEC ECX
	call fact
	return:
	RET
calcSum ENDP

main PROC
	call readInt
	MOV var, EAX
	MOV EAX, 1
	MOV ECX, var	
	call fact
	call writeInt
	exit
main ENDP