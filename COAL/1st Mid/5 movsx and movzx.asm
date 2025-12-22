INCLUDE Irvine32.inc

.data
	num1 DB 127
	num2 DB -1

.code
main PROC
	movzx eax, num1
	call WriteInt
	movzx eax, num2
	call WriteInt

	movsx eax,num1
	call WriteInt
	movsx eax, num2
	call WriteInt
main ENDP
END main