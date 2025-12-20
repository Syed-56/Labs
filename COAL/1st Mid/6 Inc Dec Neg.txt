INCLUDE Irvine32.inc

.data
	num DB 8
.code
main PROC
	MOVZX EAX, num
	INC AX
	call WriteInt
	DEC num
	MOVZX EAX, num
	call Crlf
	call WriteInt
	NEG EAX
	call Crlf
	call WriteInt
	exit
main ENDP
END main