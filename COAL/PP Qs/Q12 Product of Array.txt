INCLUDE Irvine32.inc

.data
	arr DWORD 5 DUP(?)
	product DWORD 1
	msgInput BYTE "Enter Array:- ", 0
	msgOutput BYTE "Product: ", 0

.code
main PROC
	MOV EDX,  OFFSET msgInput
	call WriteString
	call Crlf
	MOV ECX, LENGTHOF arr
	MOV ESI, OFFSET arr
	inputArray:
		call ReadInt
		MOV [ESI], EAX
		ADD ESI, TYPE arr
		LOOP inputArray

	MOV ECX, LENGTHOF arr
	MOV ESI, OFFSET arr
	productArray:
		XOR EDX, EDX
		MOV EAX, [ESI]
		MOV EBX, product
		MUL EBX
		MOV product, EAX
		call WriteDec
		call Crlf
		ADD ESI, TYPE arr
		LOOP productArray
	MOV EAX, product
	MOV EDX, OFFSET msgOutput
	call WriteString
	call WriteDec
	exit
main ENDP
END main