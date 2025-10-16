INCLUDE Irvine32.inc

.data
	op1 BYTE 4
	op2 BYTE 4
	msgEqual BYTE "op1==op2", 0
	msgNotEqual BYTE "op1!=op2", 0
.code
main PROC
	;if(op1==op2) print("op1==op2")
	;else	print("op1!=op2")
	MOV AL, op1
	MOV BL, op2
	CMP AL, BL
	JZ equal	;or JE equal
;execute else block
	MOV EDX, OFFSET msgNotEqual
	call WriteString
	call Crlf
	JMP done
;execute if block	
	equal:
		MOV EDX, OFFSET msgEqual
		call WriteString
		call Crlf
		JMP done
done:
exit
main ENDP
END main