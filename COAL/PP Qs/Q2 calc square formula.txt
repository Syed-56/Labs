INCLUDE Irvine32.inc 

.data 
   a DWORD 4
   b DWORD 5
   a2 DWORD ?
   b2 DWORD ?
   ab2 DWORD ?
   ans DWORD ?
   msg BYTE "(a+b)^2 = ", 0
.code 
main PROC
	MOV EAX, a
	IMUL EAX, a
	MOV a2, EAX

	MOV EAX, b
	IMUL EAX, b
	MOV b2, EAX

	MOV EAX, a
	IMUL EAX, b
	IMUL EAX, 2
	MOV ab2, EAX

	ADD EAX, a2
	ADD EAX, b2
	MOV ans, EAX

	MOV EDX, OFFSET msg
	call WriteString
	MOV EAX, ans
	call WriteDec
  exit
main ENDP
END main