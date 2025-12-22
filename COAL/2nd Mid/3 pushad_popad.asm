INCLUDE Irvine32.inc

.data

.code
main PROC
	mov eax, 1111h
    	mov ebx, 2222h
    	mov ecx, 3333h
    	mov edx, 4444h
	PUSHAD	;stores all register values in stack
	mov eax, 0
    	mov ebx, 0
    	mov ecx, 0
    	mov edx, 0
	POPAD	;all stored values of register in stack are restored back
	;this was for 32-bit regs, for 16-bits we do PUSHA/POPA
exit
main ENDP
END main