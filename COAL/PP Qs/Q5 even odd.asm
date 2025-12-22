INCLUDE Irvine32.inc

.data
	num BYTE 9
	msgEven BYTE "Even Num", 0
	msgOdd BYTE "Odd num", 0
.code
main PROC
	XOR EDX, EDX
	MOVZX EAX, num
	MOV EBX, 2
	DIV EBX	;EAX=10/2=5 and EDX = 10%2=0
	MOV EBX, 0
	CMP EDX,0
	JE evenNum
	JNE oddNum

	evenNum:
		MOV EDX, OFFSET msgEven
		call WriteString
		jmp done
	oddNum:
		MOV EDX, OFFSET msgOdd
		call WriteString
		jmp done
	done:
		exit
main ENDP
END main