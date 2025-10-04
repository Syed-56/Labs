INCLUDE Irvine32.inc
.code
main PROC
	mov edx, OFFSET msg ; point to string
	call WriteString ; print string
	exit
main ENDP
.data
	msg BYTE "Hello, World!", 0
END main