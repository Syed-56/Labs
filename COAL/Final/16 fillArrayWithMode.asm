INCLUDE Irvine32.inc

.data
  pixel DWORD 10 DUP(?)
  invalidMsg BYTE "Invalid", 0
  
.code

;mode=0 means WORD and 1 means DWORD
initialize PROC dest:DWORD, count:DWORD, color:DWORD, mode:DWORD
  MOV EDI, dest
  MOV ECX, count
  CLD
  
  CMP mode, 0
  JE modeWORD
  CMP mode, 1
  JE modeDWORD
  JMP invalid
  
  modeWORD:
    MOV AX, WORD PTR color
    REP STOSW
    JMP done
  
  modeDWORD:
    MOV EAX, color
    REP STOSD
    JMP done
  
  invalid:
    mov edx, offset invalidMsg
    call writeString
    jmp done

  done:
  RET
initialize ENDP

main PROC
   INVOKE initialize, OFFSET pixel, 5, 0ff1h, 0
   exit
main ENDP
END main