INCLUDE Irvine32.inc

.data

myProc PROTO par1:DWORD, par2:DWORD, par3:DWORD
myProc PROC par1:DWORD, par2:DWORD, par3:DWORD
	LEA EAX, EBP+8
	call writeHex
	call crlf
	MOV EAX, [EAX]
	call writeHex
	call crlf
	LEA EAX, EBP+12
	call writeHex
	call crlf
	MOV EAX, [EAX]
	call writeHex
	call crlf
	LEA EAX, EBP+16
	call writeHex
	call crlf
	MOV EAX, [EAX]
	call writeHex
	call crlf
myProc ENDP
	
.code

main PROC
	INVOKE myProc, 1234h, 4567h, 0987h
main ENDP

END main