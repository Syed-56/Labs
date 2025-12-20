INCLUDE Irvine32.inc

.data

.code
main PROC
	;ABB27F10h + 1234F5A9
	;add low bits
	MOV AX, 7F10h
	MOV BX, F5A9h
	ADD AX, BX	;AX=74B9 and CF=1 due to carry
	
	MOV AX,ABB2
	MOV BX, 1234
	ADC AX, BX	;AX=B5E6 but adc adds CF also so add 1 means B5E7
	call writeDec
	exit
main ENDP
END main