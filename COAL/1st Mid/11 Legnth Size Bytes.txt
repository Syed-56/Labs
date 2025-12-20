INCLUDE Irvine32.inc

.data
	arr BYTE 1,2,3,4
.code
main PROC
	MOV AX, TYPE arr	;AX=1 since BYTE size each element
	MOV AX, LENGTHOF arr	;AX=4 since 4 is length of array
	MOV AX, SIZEOF arr	;AX=4x1=4 since 4 elements of 1 byte
	exit
main ENDP
END main