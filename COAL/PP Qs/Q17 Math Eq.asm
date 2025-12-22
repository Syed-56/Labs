INCLUDE Irvine32.inc
;X=(A+B)-C
;Y=(D+E)-(F+G)
;Z=X+Y-H

.data
	varA BYTE 1
	varB BYTE 2
	varC BYTE 3
	varD BYTE 4
	varE BYTE 5
	varF BYTE 6
	varG BYTE 7
	varH BYTE 8
	varX BYTE ?
	varY BYTE ?
	varZ BYTE ?
.code
main PROC
	MOV AL, varA
	ADD AL, varB
	SUB AL, varC
	call WriteInt
	call Crlf
	MOV varX, AL

	MOV AL, varD
	ADD varD, varE
	MOV varY, varD
	MOV AL, varF
	ADD AL, varG
	SUB varY, AL
	MOV AL, varY
	call WriteInt
	call Crlf

	MOV AL, varX
	ADD AL, vary
	SUB AL, varH
	call WriteInt
	
	exit
main ENDP
END main