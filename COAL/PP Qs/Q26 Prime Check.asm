Include Irvine32.inc

.data
	num DWORD 18
	msgNotprime BYTE "Not Prime",0
	msgPrime BYTE "Prime",0

.code
main PROC
	MOV EAX, num
	CMP EAX,1
	JNG notPrime
	XOR EDX,EDX
	MOV ECX, 2
	DIV ECX
	MOV EBX,EAX

	checkPrime:
		XOR EDX,EDX
		MOV EAX,num
		DIV ECX
		CMP EDX,0
		JE notPrime
		INC ECX
		CMP ECX,EBX
		JL checkPrime

	MOV EDX, OFFSET msgPrime
	call writeString
	JMP done

	notPrime:
		MOV EDX, OFFSET msgNotprime
		call writeString
		JMP done

	done:
	exit
main ENDP
END main