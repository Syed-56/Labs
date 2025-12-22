INCLUDE Irvine32.inc

.data
	msgZero BYTE "Zero Found", 0
	msgNonZero BYTE "Zero Not Found", 0
.code
main PROC
	MOV AX, 0
	CMP AX, 0
	JZ zeroFound
	JNZ zeroNotFound
	;here this will jump to zerofound label as ZF=0
	
	zeroFound:
		MOV EDX, OFFSET msgZero
		call WriteString
		call Crlf
		JMP next1
	zeroNotFound
		MOV EDX, OFFSET msgNonZero
		call WriteString
		call Crlf
		JMP next1
	
next1:
exit
main ENDP
END main