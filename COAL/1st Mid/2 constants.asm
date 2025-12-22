INCLUDE Irvine32.inc

.code
	main PROC
	mov eax, 25d	; 25d means 25 in decimal, moved in eax register
	mov ebx, 101b	; 101 in binary
	mov ecx, 10h	; 10h in hexadecimal
	
	exit
main ENDP
	END main
