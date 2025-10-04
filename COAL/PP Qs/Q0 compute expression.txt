INCLUDE Irvine32.inc

.data
	varA WORD 0
	varB WORD 5
	varC WORD 8
	varD WORD 5
.code
main PROC
	MOVZX EAX, varA
	MOVZX EBX, varB
	MOVZX ECX, varC
	MOVZX EDX, varD
	ADD EAX, EBX	;(A+B)
	SUB ECX, EDX	;(C-D)
	SUB EAX, ECX	;(A+B)-(C-D)
	call WriteDec

	exit
main ENDP
END main