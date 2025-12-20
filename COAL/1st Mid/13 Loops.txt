INCLUDE Irvine32.int

.data
	num BYTE 1
.code
main PROC
	MOV ECX, 5
	MOV EAX, num
	print5times:
		call WriteInt
		INC EAX
		LOOP print5times
	exit
main ENDP
END main