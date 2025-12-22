INCLUDE Irvine32.inc

.data
    msgEqual      BYTE "AX is equal to BX", 0
    msgNotEqual   BYTE "AX is NOT equal to BX", 0

.code
main PROC
	MOV AX, 5
	MOV BX, 5
	CMP AX, BX
	
	JE equalLabel
	JNE notequalLabel
	
	equalLabel:
		MOV EDX, OFFSET msgEqual
		call WriteString
		call Crlf
		JMP done
	notequalLabel:
		MOV EDX, OFFSET msgNotEqual
		call WriteString
		call Crlf
		JMP done
done:
exit
main ENDP
END main