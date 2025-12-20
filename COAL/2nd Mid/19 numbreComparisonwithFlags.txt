INCLUDE Irvine32.inc
.data
	num1 BYTE ?
	num2 BYTE ?
	msgInput BYTE "Enter Num", 0
   	msgEqual BYTE "Both numbers are equal", 0
    	msgGreater BYTE "First number is greater", 0
    	msgLesser BYTE "Second number is greater", 0

.code

findGreatestUnsigned PROC
	CMP AL, BL
	;if(a>=b) -> CF=0
	JNC greaterOrEqual
	JC lessThan
	
	greaterOrEqual:
		;if(a>b)->ZF=0, if(a==b)->ZF=1
		JZ equalCase
		JNZ greaterCase
		
		equalCase:
			MOV EDX, OFFSET msgEqual
			call writeString
			JMP done
		greaterCase:
			MOV EDX, OFFSET msgGreater
			call writeString
			JMP done
	lessThan:
		MOV EDX, OFFSET msgLesser
		call writeString
		JMP done
	done:		
	RET
findGreatestUnsigned ENDP

findGreatestSigned PROC
	CMP AL, BL
	;if(a==b)->ZF==1
	JZ equalCase
	JNZ moveAhead
	equalCase:
		MOV EDX, OFFSET msgEqual
		call writeString
		JMP done

	moveAhead:
	;if(a<b)->SF=1 & OF=0
	JS checkOFZero
	JNS checkOFSet
	checkOFZero:
		JO greaterCase
		JNO lesserCase
		greaterCaseForSF1:
			MOV EDX, OFFSET msgGreater
			call writeString
			JMP done
		lesserCaseForSF1:
			MOV EDX, OFFSET msgLesser
			call writeString
			JMP done
	
	checkOFSet:
		JNO greaterCase
		JO lesserCase
		greaterCaseForSF0:
			MOV EDX, OFFSET msgGreater
			call writeString
			JMP done
		lesserCaseForSF0:
			MOV EDX, OFFSET msgLesser
			call writeString
			JMP done
	done:
	RET
findGreatestSigned ENDP

main PROC
	MOV EDX, OFFSET msgInput
	call readInt
	MOV num1, AL
	MOV EDX, OFFSET msgInput
	call readInt
	MOV num2, AL
	
	MOV AL, num1
	MOV BL, num2
	call findGreatestUnsigned
	exit
main ENDP