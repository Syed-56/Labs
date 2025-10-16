INCLUDE Irvine32.inc

.data
	msgGreat BYTE "AX > BX", 0
.code
main PROC
	MOV BX, 5
	MOV AX, 10
	JG greater
	;JG is same as JNLE and for unsigned: same as JA and JNBE
		
	greater:
		MOV EDX, OFFSET msgGreat	
		call Crlf
		JMP done

	;similarly we have JGE for >= which is same as JNL (not less) and for unsigned its JAE and JNB
	;similarly we have JL for < which is same as JNGE (not greater or equal) and for unsigned its JB and JNAE
	;similarly we have JLE <= which is same as JNG (not greater) and for unsigned its JBE or JNA
done:
exit
main ENDP
END main