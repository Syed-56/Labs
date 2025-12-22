INCLUDE Irvine32.inc

.data

.code
main PROC
	;divide -48/5, -48=divider, 5-dividend
	MOV AL, -48d
	MOV BL, 5
	;in signed division we have to sign extend dividend as result is stored in AX for AL, EAX for AX...
	CBW
	;if we hav 16bit numb in AX then we do CWD anf if we had 32bit numb in EAX then we do CDQ
	IDIV BL
	;now AL=-9, AX=-3 since quotient in low bits and remainder in high bits 
	exit
main ENDP
END main