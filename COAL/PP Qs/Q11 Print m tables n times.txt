INCLUDE Irvine32.inc

.data
	tables DWORD ?
	multiples DWORD ?
	msg BYTE "How many tables to Print: ", 0
	msg2 BYTE "Hoy many multiples to Print: ", 0
	msg3 BYTE " ", 0
.code
main PROC
	MOV EDX, OFFSET msg
	call WriteString
	call readInt
	MOV tables, EAX

	MOV EDX, OFFSET msg2
	call WriteString
	call readInt
	MOV multiples, EAX
	
	MOV ECX, tables
	printTables:
		MOV EBX, ECX
		MOV ECX, multiples
		XOR EDX, EDX
		printMultiples:
			MOV EAX, tables
			SUB EAX, EBX
			INC EAX
			MOV EDX, multiples
			SUB EDX, ECX
			INC EDX
			MUL EDX
			call WriteDec
			MOV EDX, OFFSET msg3
			call WriteString
			LOOP printMultiples
		call Crlf
		MOV ECX, EBX
		LOOP printTables
	exit
main ENDP
END main