INCLUDE Irvine32.inc

.data
	var DWORD ?
.code

calcSum PROC USES EAX ECX
	CMP ECX, 0
	JLE return
	ADD EAX, ECX
	DEC ECX
	call calcSum
	return:
	RET
calcSum ENDP

main PROC
	call readInt
	MOV var, EAX
	MOV EAX, 0
	MOV ECX, var	
	call calcSum
	call writeInt
	exit
main ENDP