; statements followed by semicolon are comments (non executable)

TITLE MyFirstProgram (Test.asm)		; just a Title for Program
INCLUDE Irvine32.inc			; includes irvine library
.code			; this section stores instructions
	main PROC		; defines main function
	mov eax, 10h		; moves hex value 10h (16 in dec) into EAX Register	
	mov ebx, 25h		; moves hex value 25h (37 in dec) into EBX Register
	call DumpRegs		; calls DumpRegs Function (This prints the contents of CPU registers (EAX, EBX, ECX, EDX, ESP, EBP, etc.) to the console.)
	exit			; calls exit function to terminate program
main ENDP		; ends main procedure
	END main	; marks the end of program by telling assembler where to begin execution