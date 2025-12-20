INCLUDE Irvine32.inc

.data
  msg BYTE "Happy Birthday", 0
  msgLength DWORD ?
  buffer BYTE DUP(?)
  
.code

utilityRoutine PROC msg: PTR BYTE, buffer: PTR BYTE, msgLength: PTR DWORD
  MOV EDI, msg
  calcStrLength:
    CLD
    MOV AL, 0
    MOV ECX, 100
    REP SCASB
    MOV EAX, 100
    SUB EAX, ECX
    MOV msgLength, EAX
    
  copyString:
    CLD
    MOV ESI, msg
    MOV EDI, buffer
    MOV ECX, [msgLength]
    REP MOVSB
  
  done:
  MOV BYTE PTR [EDI], 0
  RET
utilityRoutine ENDP

main PROC
  INVOKE utilityRoutine, msg, buffer, OFFSET msgLength
   exit
main ENDP
END main