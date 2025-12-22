; you name functions/variables/constants. Thats what identifier means, having same rules but are also case sensitive

INCLUDE Irvine32.inc

.data
	num1 DWORD 10	;creates variable num1 with value 10
	num2 DWORD 20	;creates variable num2 with value 20
	sum DWORD ?	;creates uninitialized variable for sum
	;keyword DWORD (or DD) means store 4 bytes for variable. 
	;Other Keywords: DB=1byte, DW=2byte, DQ=8bytes

	msg1 DB "Hello, World!", 0   ;msg is variable, 0 is null terminator
	msg2 DB 'A', 'B', 'C', 0    ; like characters

	arr DB 10 DUP(0);	DB 10 means 10 bytes all initialized to 0. DUP means duplicate until size reaches 10 bytes

	
.code
main PROC
	mov eax, num1	;store num1 in eax register
	add eax, num2	;add num2 in eax register's value
	mov sum, eax	;mov value from eax into sum variable (Stored in eax)

	mov eax, sum	;store sum value in eax register
	call WriteInt	;print sum variable as integer
	call CrLf	;print newline

	mov edx, OFFSET msg1	;edx register is used for string storage, offset retreives pointer pointing to beginning of string
    	call WriteString 	;prints string (stored in edx)
	
	exit
main ENDP
END main