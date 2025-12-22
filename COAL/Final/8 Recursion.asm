INCLUDE Irvine32.inc

.data
	var DWORD ?
	zero DWORD 0
.code

printNums PROC USES EAX, var:DWORD
	MOV EAX, var
	CMP EAX, zero
	JE return
	call writeInt
	call crlf
	DEC var
	call printNums
	return:
	RET
printNums ENDP

main PROC
	call readInt
	MOV var, EAX
	INVOKE printNums, var
	exit
main ENDP

END main