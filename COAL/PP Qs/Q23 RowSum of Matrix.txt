INCLUDE Irvine32.inc

;tell nums in array divisible by 3,4,both,none
.data
	matrix DWORD 1,2,3,4,5,6,7,8,9
	ROWS EQU 3
	COLS EQU 3
	n DWORD (ROWS*COLS)
	findRowSum PROTO :DWORD, :DWORD
	msgRow BYTE "Row Sum = ", 0
	sum DWORD ?

.code

findRowSum PROC arr: DWORD, matrixSize: DWORD
	XOR ESI, ESI

	row_loop:
		MOV sum,0
		MOV EDI, 0
		CMP ESI, ROWS
		JGE done

	col_loop:
		CMP EDI, COLS
		JGE next_row
		MOV EBX, arr
		MOV EAX, ESI
		MOV ECX, COLS
		MUL ECX
		MOV ECX, TYPE arr
		MUL ECX
		ADD EBX, EAX
		MOV EAX, [EBX + EDI*TYPE arr]
		ADD sum, EAX
		INC EDI
		LOOP col_loop

	next_row:
		MOV EAX, sum
		MOV EDX, OFFSET msgRow
		call writeString
		call writeDec
		call crlf
		INC ESI
		LOOP row_loop

	done:
	RET
findRowSum ENDP

main PROC
	MOV ECX, n
	MOV ESI, OFFSET matrix
	INVOKE findRowSum, ESI, ECX
	exit
main ENDP
END main