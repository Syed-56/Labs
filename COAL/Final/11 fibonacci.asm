INCLUDE Irvine32.inc

.data
	num DWORD 8

.code

fibo PROC count:DWORD
	;base-case
	CMP count,1
	JG recursion
	MOV EAX, count
	RET

	recursion:
	PUSH ECX
	;fib(n-1)
	MOV ECX,count
	DEC ECX
	INVOKE fibo,ECX
	PUSH EAX
	;fib(n-2)
	MOV ECX,count
	SUB ECX,2
	INVOKE fibo,ECX
	;add 'em
	POP EBX
	ADD EAX,EBX
	POP ECX
	RET

fibo ENDP

main PROC
	INVOKE fibo,num
	call writeDec
	exit
main ENDP

END main