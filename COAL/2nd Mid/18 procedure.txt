INCLUDE Irvine32.inc

.data
	msgPrint BYTE "Hello World", 0
.code

print PROC
	MOV EDX, OFFSET msgPrint
	call WriteString
	call Crlf
	RET
print ENDP

;this is a function with arguments as eax,ebx,ecx are used from main
sample PROC
 	add eax, ebx
 	add eax, ecx
 	ret
sample ENDP

main PROC
	CALL print
	
	mov eax, 5
	mov ebx, 3
	mov ecx, 2
	call sample
	call writeDec
	exit
main ENDP
END main