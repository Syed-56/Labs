INCLUDE Irvine32.inc

.data
	fib1 DWORD 0
	fib2 DWORD 1
	temp DWORD ?
	msg BYTE ", ", 0
.code
	MOV ECX, 7
	MOV EDX, OFFSET msg
	MOV EAX, fib1
	call WriteDec
	call WriteString
	fibo:
		MOV EAX, fib2
		MOV temp, EAX
		MOV EBX, fib1
		ADD fib2, EBX
		MOV EAX, temp
		MOV fib1, EAX
		
		MOV EDX, OFFSET msg
		MOV EAX, fib2
		call WriteDec
		call WriteString
		
		LOOP fibo
	exit
main ENDP
END main