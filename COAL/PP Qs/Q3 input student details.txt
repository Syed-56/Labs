INCLUDE Irvine32.inc 

.data 
	marks DWORD 5 DUP(?) 
	ids BYTE 5*10 DUP(?) 	
	msgMarks BYTE "Enter marks: ", 0
	msgIds BYTE "Enter ID: ", 0
	msgStudent BYTE "Student ", 0
	count DWORD 5
	temp DWORD 0
.code 
main PROC
	MOV ECX, count
	MOV EDI,OFFSET marks
	MOV ESI,OFFSET ids

	inputLoop:
	;Print Student X
	MOV EDX, OFFSET msgStudent
	call WriteString
	MOV EAX, Count
	SUB EAX, ECX
	ADD EAX, 1
	Call WriteDec
	Call Crlf

	;Input ID
	MOV temp, ECX
	MOV EDX, OFFSET msgIds
	call writeString
	MOV EDX, ESI
	MOV ECX, 10
	call ReadString
	ADD ESI, ECX
	MOV ECX, temp

	;Input Marks
	MOV EDX, OFFSET msgMarks
	call WriteString
	call readInt
	MOV [EDI], EAX
	ADD EDI, TYPE marks
	call Crlf

	Loop inputLoop


	exit
main ENDP
END main