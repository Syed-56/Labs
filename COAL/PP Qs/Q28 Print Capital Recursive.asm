INCLUDE Irvine32.inc

.data
	string BYTE "FAST Nuces Khi",0

.code

printCap PROC USES ESI ECX EDX, msg: PTR BYTE
	MOV ESI, msg
	MOV AL, [ESI]
	CMP AL, 0
	JE done

	MOV AL, [ESI]
	CMP AL, 'A'
	JL skip
	CMP AL, 'Z'
	JG skip
	call writeChar
	skip:
	INC ESI
	INVOKE printCap, ESI
	done:
	RET	
printCap ENDP

main PROC
	INVOKE printCap, ADDR string
	exit
main ENDP
END main