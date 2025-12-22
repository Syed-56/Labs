INCLUDE Irvine32.inc

.data
	num BYTE 10
.code
main PROC
	MOV EAX, num	;EAX=10
	push EAX	;ESP = 1000h - 4 = 0FFCh
	pop EBX		;EBX=10 and ESP = 0FFCh + 4 = 1000h
	exit
main ENDP
END main