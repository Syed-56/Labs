INCLUDE Irvine32.inc

.data
	msgLoop BYTE "Loop is Running", 0
.code
main PROC
	MOV EAX, 10
	MOV EBX, 1
	;while(eax > ebx) {
	;print(loop is running)
	;eax-- }
	
	whileLoop:
		MOV EDX, OFFSET msgLoop
		call writeString
		call Crlf
		DEC EAX
		CMP EAX, EBX
		JG whileLoop
		;JNG done (optional)
done:
exit
main ENDP
END main