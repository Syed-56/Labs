INCLUDE Irvine32.inc

.data
	msgEQ BYTE "EAX = EBX", 0
	msgLess BYTE "EAX < EBX", 0
	msgGreat BYTE "EAX > EBX", 0
.code
MAIN proc
	MOV EAX, 10
	MOV EBX, 10
	CMP EAX, EBX
	JE equal
	JL less
	JG great

	equal:
		MOV EDX, OFFSET msgEQ
		call WriteString
		call Crlf
		JMP done
	less:
		MOV EDX, OFFSET msgLess
		call WriteString
		call Crlf
		JMP done
	great:
		MOV EDX, OFFSET msgGreat
		call WriteString
		call Crlf
		JMP done
	done:
		exit
main ENDP
END main