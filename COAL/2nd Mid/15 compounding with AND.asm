INCLUDE Irvine32.inc

.data
	varA BYTE 1
	varB BYTE 2
	varC BYTE 3
	msgGreat BYTE "varA is greatest", 0
	msgNotGreat BYTE "varA is not greatest", 0
.code
main PROC
	;if(varA > varB && varA > varC)	print("varA is biggest")
	MOV AL, varA
	MOV BL, varB
	CMP AL, BL
	JG checkAND
	JNG notGreatest

	checkAND: 
		MOV AL, varA
		MOV BL, varC
		CMP AL, BL
		JG greatest
		JNG notGreatest

	greatest:
		MOV EDX, OFFSET msgGreat
		call WriteString
		JMP done
	notGreatest:
		MOV EDX, OFFSET msgNotGreat
		call WriteString
		JMP done
done:
exit
main ENDP
END main