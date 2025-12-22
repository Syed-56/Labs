INCLUDE Irvine32.inc

.data
	arr BYTE 1,2,3,4,5
	inputMsg BYTE "Enter num: ", 0
	outputMsg BYTE "Index: ", 0
	foundMsg BYTE "Element Found" , 0
	notFoundMsg BYTE "Element not found", 0
	key BYTE ?
.code

linearSearch PROC
	MOV ECX, LENGTHOF arr
	MOV AL, key
	searching:
		CMP AL, [ESI]
		JE found
		ADD ESI, TYPE arr
		LOOP searching
	MOV EDX, OFFSET notFoundMsg
	call WriteString
	MOV EAX, -1
	JMP done
	
	found:
		MOV EDX, OFFSET foundMsg
		call WriteString
		MOV EAX, LENGTHOF arr
		SUB EAX, ECX
	done:
	call Crlf
	RET
linearSearch ENDP

main PROC
	MOV EDX, OFFSET inputMsg
	call writeString
	MOV ESI, OFFSET arr
	call readInt
	MOV key, AL
	call linearSearch
	MOV EDX, OFFSET outputMsg
	call writeString
	call writeInt
	exit
main ENDP

END main