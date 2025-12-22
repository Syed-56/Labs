INCLUDE Irvine32.inc

.data
	num1 BYTE 128
	num2 BYTE 128
.code
main PROC
	MOV AL, num1
	ADD AL, num2
	call DumpRegs	;CF=1
		
	MOV AL, num1
	call DumpRegs ;CF=unchanged
	exit
main ENDP
END main