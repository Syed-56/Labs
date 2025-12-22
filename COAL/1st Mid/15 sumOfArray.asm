INCLUDE Irvine32.inc

.data
	arr DWORD 1,2,3,4,5
	sum DWORD 0
.code
main PROC
	MOV ECX, LENGTHOF arr
	MOV ESI, OFFSET arr
	arraySum:
		MOV EAX, [ESI]	
		ADD [sum], EAX
		ADD ESI, TYPE arr	;ESI+=1
		LOOP arraySum
	MOV EAX, [sum]
	call WriteInt
	exit
main ENDP
END main