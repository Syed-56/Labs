INCLUDE Irvine32.inc

;tell nums in array divisible by 3,4,both,none
.data
	nums DWORD 12,9,15,8,16,24,27,32,36,45,7
	sizeOfNums DWORD ?
	msg BYTE " ", 0

	msgBy4 BYTE "Divisible by 4 = ", 0
	msgBy3 BYTE "Divisible by 3 = ", 0
	msgByBoth BYTE "Divisible by Both = ", 0
	msgByNone BYTE "Divisible by None = ", 0


.code

divisibleBy4 PROC USES EAX EBX EDX, arr: PTR DWORD, n:DWORD
	MOV ESI, arr
	MOV ECX, n
	MOV EBX, 4
		traverse:
			XOR EDX, EDX
			MOV EAX, [ESI]
			DIV EBX
			CMP EDX, 0
			JNE notDivisible
			MOV EAX, [ESI]
			call writeDec
			MOV EDX, OFFSET msg
			call writeString
			notDivisible:
			ADD ESI, TYPE arr
			LOOP traverse
	RET
divisibleBy4 ENDP

divisibleBy3 PROC USES EAX EBX EDX, arr: PTR DWORD, n:DWORD
	MOV ESI, arr
	MOV ECX, n
	MOV EBX, 3
		traverse:
			XOR EDX, EDX
			MOV EAX, [ESI]
			DIV EBX
			CMP EDX, 0
			JNE notDivisible
			MOV EAX, [ESI]
			call writeDec
			MOV EDX, OFFSET msg
			call writeString
			notDivisible:
			ADD ESI, TYPE arr
			LOOP traverse
	RET
divisibleBy3 ENDP

divisibleByBoth PROC USES EAX EBX EDX, arr: PTR DWORD, n:DWORD
	MOV ESI, arr
	MOV ECX, n
	
	traverse:
		checkBy4:
			MOV EBX, 4
			XOR EDX, EDX
			MOV EAX, [ESI]
			DIV EBX
			CMP EDX, 0
			JE checkBy3
			JNE done
		checkBy3:
			MOV EBX, 3
			XOR EDX, EDX
			MOV EAX, [ESI]
			DIV EBX
			CMP EDX, 0
			JE print
			JNE done
		print:
			MOV EAX, [ESI]
			call writeDec
			MOV EDX, OFFSET msg
			call writeString
		done:
			ADD ESI, TYPE arr
			LOOP traverse
	RET
divisibleByBoth ENDP

divisibleByNone PROC USES EAX EBX EDX, arr: PTR DWORD, n:DWORD
	MOV ESI, arr
	MOV ECX, n
	
	traverse:
		checkBy4:
			MOV EBX, 4
			XOR EDX, EDX
			MOV EAX, [ESI]
			DIV EBX
			CMP EDX, 0
			JNE checkBy3
			JE done
		checkBy3:
			MOV EBX, 3
			XOR EDX, EDX
			MOV EAX, [ESI]
			DIV EBX
			CMP EDX, 0
			JNE print
			JE done
		print:
			MOV EAX, [ESI]
			call writeDec
			MOV EDX, OFFSET msg
			call writeString
		done:
			ADD ESI, TYPE arr
			LOOP traverse
	RET
divisibleByNone ENDP

main PROC
	MOV ECX, LENGTHOF nums
	MOV sizeOfnums, ECX
	MOV EDX, OFFSET msgBy4
	call writeString
	INVOKE divisibleBy4, ADDR nums, sizeOfNums
	call crlf

	MOV EDX, OFFSET msgBy3
	call writeString
	INVOKE divisibleBy3, ADDR nums, sizeOfNums
	call crlf
	MOV EDX, OFFSET msgByBoth
	call writeString
	INVOKE divisibleByBoth, ADDR nums, sizeOfNums
	call crlf

	MOV EDX, OFFSET msgByNone
	call writeString
	INVOKE divisibleByNone, ADDR nums, sizeOfNums
	call crlf
	exit
main ENDP
END main