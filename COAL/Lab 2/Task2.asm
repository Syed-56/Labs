;Syed Sultan Ahmed - 24K-0585
INCLUDE Irvine32.inc
.data
	num1 DWORD 20
	num2 DWORD 80
	result DWORD ?
	msg BYTE "Ans: ", 0
.code
	main PROC
	mov eax, num1
	add eax, num2
	mov result, eax
	mov edx, OFFSET msg
	call WriteString
	mov eax, result
	call WriteInt
	exit
main ENDP
END main