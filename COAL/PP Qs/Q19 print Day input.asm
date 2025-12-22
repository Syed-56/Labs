INCLUDE Irvine32.inc

.data
        day1 BYTE "Monday", 0
        day2 BYTE "tuesday", 0
        day3 BYTE "wednesday", 0
        day4 BYTE "thursday", 0
        day5 BYTE "friday", 0
        day6 BYTE "saturday", 0
        day7 BYTE "sunday", 0
	num BYTE ?
	msgInput BYTE "Enter Num: ", 0
	msgInvalid BYTE "Invalid Num", 0
.code

printDay PROC
	MOVZX EAX, num
	CMP EAX, 1
	JE monday
	CMP EAX, 2
	JE tuesday
	CMP EAX, 3
	JE wednesday
	CMP EAX, 4
	JE thursday
	CMP EAX, 5
	JE friday
	CMP EAX, 6
	JE saturday
	CMP EAX, 7
	JE sunday
	
	MOV EDX, OFFSET msgInvalid
	call writeString
	JMP done

	monday:
		MOV EDX, OFFSET day1
		call writeString
		JMP done
	tuesday:
		MOV EDX, OFFSET day2
		call writeString
		JMP done
	wednesday:
		MOV EDX, OFFSET day3
		call writeString
		JMP done
	thursday:
		MOV EDX, OFFSET day4
		call writeString
		JMP done
	friday:
		MOV EDX, OFFSET day5
		call writeString
		JMP done
	saturday:
		MOV EDX, OFFSET day6
		call writeString
		JMP done
	sunday:
		MOV EDX, OFFSET day7
		call writeString
		JMP done
	done:
	RET
printDay ENDP

main PROC
	MOV EDX, OFFSET msgInput
	call WriteString
	call Readint
	MOV num, AL
	call printDay
	exit
main ENDP

exit