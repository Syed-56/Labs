INCLUDE Irvine32.inc
COUNT=500
statement EQU <"COUNT IS ">

.data
	num1 DWORD 10
	num2 DWORD ?
	S1 BYTE statement, 0
.code
main PROC
	mov EAX, num1
	XCHG EAX, num2
	mov EAX, num2
	call WriteInt
	call Crlf
	mov EDX, OFFSET S1
	call WriteString
	mov EAX, COUNT
	call WriteInt
	exit
main ENDP
END main