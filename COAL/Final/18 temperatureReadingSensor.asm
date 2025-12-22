INCLUDE Irvine32.inc

.data
  ;rows=sensors, cols=hourly reading
    tempReadings DWORD 10, 11, 19
                 DWORD 29, 23, 25
                 DWORD 39, 30, 38
    ROWS EQU 3
    COLS EQU 3
    max DWORD ?
    space BYTE " ", 0
    maxMsg BYTE "Max = ", 0
    avgSensorTemp DWORD ROWS DUP(?)
    
.code

printReadings PROC
  XOR ESI, ESI
  
  row_loop:
    CMP ESI, ROWS
    JGE done
    XOR EDI, EDI
    
  col_loop:
    CMP EDI, COLS
    JGE next_row
    
    MOV EBX, OFFSET tempReadings
    MOV EAX, ESI
    IMUL EAX, COLS
    IMUL EAX, TYPE tempReadings
    ADD EBX, EAX
    MOV EAX, [EBX + EDI * TYPE tempReadings]
    call writeInt
    MOV EDX, OFFSET space
    call writeString
    
    INC EDI
    JMP col_loop
    
  next_row
    call crlf
    INC ESI
    JMP row_loop
  done:
  RET
printReadings ENDP
  
findMax PROC
  MOV max, 320000
  XOR ESI, ESI
  
  row_loop:
    CMP ESI, ROWS
    JGE done
    XOR EDI, EDI
    
  col_loop:
    CMP EDI, COLS
    JGE next_row
    
    MOV EBX, OFFSET tempReadings
    MOV EAX, ESI
    IMUL EAX, COLS
    IMUL EAX, TYPE tempReadings
    ADD EBX, EAX
    MOV EAX, [EBX + EDI * TYPE tempReadings]
    CMP EAX, max
    JNG skip
    MOV max, EAX
    
    skip:
    INC EDI
    JMP col_loop
    
  next_row
    INC ESI
    JMP row_loop
    
  done:
  MOV EDX, OFFSET maxMsg
  call writeString
  MOV EAX, max
  call writeInt
  RET
findMax ENDP

computeAvgSensorTemp PROC
  LOCAL sum:DWORD
  XOR ESI, ESI
  
  row_loop:
    CMP ESI, ROWS
    JGE done
    XOR EDI, EDI
    MOV sum, 0
    
  col_loop:
    CMP EDI, COLS
    JGE next_row
    
    MOV EBX, OFFSET tempReadings
    MOV EAX, ESI
    IMUL EAX, COLS
    IMUL EAX, TYPE tempReadings
    ADD EBX, EAX
    MOV EAX, [EBX + EDI * TYPE tempReadings]
    ADD sum, EAX
    
    INC EDI
    JMP col_loop
    
  next_row
    MOV EBX, COLS
    XOR EDX, EDX
    MOV EAX, sum
    DIV EBX
    MOV avgSensorTemp[ESI * TYPE avgSensorTemp], EAX
    INC ESI
    JMP row_loop
  done:
  RET
computeAvgSensorTemp ENDP

normalize PROC
  XOR ESI, ESI
  
  row_loop:
    CMP ESI, ROWS
    JGE done
    XOR EDI, EDI
    
  col_loop:
    CMP EDI, COLS
    JGE next_row
    
    MOV EBX, OFFSET tempReadings
    MOV EAX, ESI
    IMUL EAX, COLS
    IMUL EAX, TYPE tempReadings
    ADD EBX, EAX
    SUB [EBX + EDI * TYPE tempReadings], max
    
    INC EDI
    JMP col_loop
    
  next_row
    
    INC ESI
    JMP row_loop
  done:
  RET
normalize ENDP

main PROC
  call printReadings
  exit
main ENDP
END main