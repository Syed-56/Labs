INCLUDE Irvine32.inc

.data
	num DWORD 12345678h
.code
main PROC
	;MOV AX, num "this will give error as AX=16-bit and num=32-bit"
	MOV AX, WORD PTR num	;now AX=5678h (little endian)
	MOV AX, WORD PTR [num+1]	;here AX=3456h
	exit
main ENDP
END main