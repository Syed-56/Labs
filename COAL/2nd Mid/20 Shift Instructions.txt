INCLUE Irvine32.inc

.data

.code
main PROC
	MOV AL, 11001111b
	SHL AL, 1	;shifts bits to left once, empty (last) places are 0-extended
	call writeBin

	MOV AL, 11001111b
	SHL AL, 2	;same as SHL but here left shift happens twice. empty places are 0-extended
	call writeBin
	;both these multiply a number with 2^n.

	MOV AL, 11001111b
	SHR AL,1	;right shift once and empty (first) place is 0
	call writeBin

	MOV AL, 11001111b
	SAR AL, 2	;right shift twice but empty place is sign-extended (1 here).
	call writeBin
	;SHR divides unsigned num by 2^n and SAR divides signed num by 2^n.
	exit
main ENDP
END main