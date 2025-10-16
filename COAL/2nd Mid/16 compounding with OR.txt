INCLUDE Irvine32.inc

.data
	varA BYTE 5
	varB BYTE 4
	varC BYTE 8
	msgMightBeGreat BYTE "varA greater than atleast one", 0
	msgNotGreat BYTE "varA not greater than anyone", 0
.code
main PROC
	MOV AL, varA
	MOV BL, varB
	CMP AL, BL
	JG checkOR

	MOV BL, varC
	CMP AL, BL
	JG checkOR
	
	MOV EDX, OFFSET msgNotGreat
	call WriteString
	JMP done
	
	checkOR:
		MOV EDX, OFFSET msgMightBeGreat
		call WriteString
		JMP done
done:
exit
main ENDP
END main