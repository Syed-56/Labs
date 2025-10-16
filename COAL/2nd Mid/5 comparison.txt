INCLUDE Irvine32.inc

.data
	
.code
MAIN proc
	;EQUAL case
	MOV EAX, 10
	MOV EBX, 10
	CMP EAX, EBX	;EAX-EBX=0
	;Less than case
	MOV EAX, 10
	MOV EBX, 20
	CMP EAX, EBX	;EAX-EBX=-10 

	;greater than case
	MOV EAX, 10
	MOV EBX, 5
	CMP EAX, EBX	;EAX-EBX=5 
	exit
main ENDP
END main