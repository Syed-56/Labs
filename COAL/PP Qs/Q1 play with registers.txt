INCLUDE Irvine32.inc 

.data 
  signedByte1 SBYTE +20
  signedByte2 SBYTE -10
  unsignedWord WORD 5

  msgEAX BYTE "Value in EAX(signedByte1) = ", 0
  msgEBX BYTE "Value in EBX(signedByte2) = ", 0
  msgECX BYTE "Value in ECX(unsignedWord) = ", 0
  msgXCHG1 BYTE "After XCHG, signedByte1 = ", 0
  msgXCHG2 BYTE "After XCHG, signedByte2 = ", 0
  msgANS BYTE "ANS = ", 0
    
.code 
main PROC
  MOVSX EAX, signedByte1  ; Sign-extend signedByte1 to EAX
  MOV EDX,OFFSET msgEAX
  call WriteString
  call WriteInt
  call Crlf

  MOVSX EBX, signedByte2  ; Sign-extend signedByte2 to EBX
  MOV EDX,OFFSET msgEBX
  MOV EAX, EBX
  call WriteString
  call WriteInt
  call Crlf
  MOV EBX, EAX

  MOVZX ECX, unsignedWord ; Zero-extend unsignedWord to EDX
  MOV EDX,OFFSET msgECX
  MOV EAX, ECX
  call WriteString
  call WriteDec
  call Crlf
  MOV ECX, EAX

  MOV AL, signedByte1
  XCHG signedByte2, AL
  MOV signedByte1, AL

  MOVSX EAX, signedByte1
  MOV EDX,OFFSET msgXCHG1
  call WriteString
  call WriteInt
  call crlf
  MOVSX EBX, signedByte2
  MOV EAX, EBX
  MOV EDX,OFFSET msgXCHG2
  call WriteString
  call WriteInt
  MOV EBX, EAX
  call crlf

  INC signedByte2
  DEC signedByte1
  MOVSX EAX, signedByte1
  MOV EDX,OFFSET msgEAX
  call WriteString
  call WriteInt
  call Crlf
  MOVSX EBX, signedByte2
  MOV EDX,OFFSET msgEBX
  MOV EAX, EBX
  call WriteString
  call WriteInt
  call Crlf
  MOV EBX, EAX

  ADD EAX,EBX
  SUB EAX, EBX
  IMUL EAX, ECX
  NEG EAX
  MOV EDX,OFFSET msgANS
  call WriteString
  call WriteInt
  call Crlf

  exit
main ENDP
END main