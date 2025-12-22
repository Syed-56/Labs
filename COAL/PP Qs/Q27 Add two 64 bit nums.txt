INCLUDE Irvine32.inc

.data
	num1 QWORD 12345678h
	num2 QWORD 87654321h
	result QWORD ?

.code
main PROC
	MOV EAX, DWORD PTR num1
	MOV EBX, DWORD PTR num2
	ADD EAX,EBX
	MOV DWORD PTR result, EAX
	MOV EAX, DWORD PTR num1+4
	MOV EBX, DWORD PTR num2+4
	ADC EAX,EBX
	MOV DWORD PTR result+4, EAX

	MOV EAX, DWORD PTR+4 result
	call writeHex
	MOV EAX, DWORD PTR result
	exit
main ENDP
END main