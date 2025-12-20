INCLUDE Irvine32.inc

.data
  ROWS EQU 3
  COLS EQU 5
  arr DWORD ROWS*COLS DUP(?)

.code
main PROC
  MOV EDI, 0
  
  col_loop:
    CMP EDI, COLS
    JGE done
    MOV ESI, 0
    
  row_loop:
    CMP ESI, ROWS
    JGE next_col
    
    MOV EBX, OFFSET arr
    MOV EAX, EDI
    IMUL EAX, ROWS
    IMUL EAX, TYPE arr	
    ADD EBX, EAX
    call readInt
    MOV arr[EBX+ESI*TYPE arr], EAX
    
    INC ESI
    JMP row_loop
    
  next_col:
    INC EDI
    JMP col_loop
    
  done:
    exit
main ENDP
END main