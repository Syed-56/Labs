INCLUDE Irvine32.inc

.data

.code
;syntax: dest,source,no,of bits
main PROC
	MOV AX, 0001001000110100b
	MOV BX, 0101011001111001b
	SHLD AX,BX,4	;AX is left shifted 4x and in place of last 4 bits, top 4 bits of BX are placed there and BX is unchanged
	;CF=1, its the last bit shifted out from AX after left rotation (or the count'th bit of original AX from MSB)

	MOV AX, 0001001000110100b
	MOV BX, 0101011001111001b
	SHRD AX,BX,4	;AX is right shifted 4x and in place of top 4 bits, last 4 bits of BX are placed there
	;CF=0, its the last bit shifte out from BX after right rotation (or the count'th bit of original AX from LSB)
	exit
main ENDP
END main