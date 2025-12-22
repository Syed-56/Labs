INCLUDE Irvine32.inc

.data
	arr DWORD 1,2,3,4,5

.code

main PROC
	MOV ESI, OFFSET arr
	MOV EDI, OFFSET arr
	MOV ECX, lengthof arr

	traverse:
		LODSD
		IMUL EAX,EAX
		STOSD
		call writeDec
		LOOP traverse
	exit
main ENDP
END main