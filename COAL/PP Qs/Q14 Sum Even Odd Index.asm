INCLUDE Irvine32.inc

.data
	arr1 WORD 50,20,90,101,450
	arr2 WORD 10, 24, 67,90,100
	arr3 DWORD 4 DUP(?)
.code 
main PROC
	MOV ECX, LENGTHOF arr1
	DEC ECX
	MOV ESI, 0
	MOV EDI, 1
	MOV EBX, 0

	sumEvenOdd:
		MOV AX, arr1[ESI * TYPE arr1]
		MOV DX, arr2[EDI * TYPE arr2]
		ADD AX,DX
		MOVZX EAX, AX
		MOV arr3[EBX * TYPE arr3], EAX
		INC ESI
		INC EDI
		INC EBX
		LOOP sumEvenOdd
	
	MOV ECX, LENGTHOF arr3
	MOV ESI, OFFSET arr3
	print:
		MOV EAX, [ESI]
		call WriteDec
		call Crlf
		ADD ESI, TYPE arr3
		LOOP print
	exit
	
main ENDP 
END main