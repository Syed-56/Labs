INCLUDE Irvine32.inc

.data
ROWS EQU 3
COLS EQU 5
arr DWORD ROWS*COLS DUP(?)

.code
main PROC
    MOV ESI, 0          ; row counter

row_loop:
    CMP ESI, ROWS
    JGE done
    MOV EDI, 0          ; column counter

col_loop:
    CMP EDI, COLS
    JGE next_row

    ; compute address: (row*COLS + col) * TYPE(arr)
    MOV EAX, ESI
    IMUL EAX, COLS      ; row * COLS
    ADD EAX, EDI        ; + col
    IMUL EAX, TYPE arr  ; multiply by 4 (DWORD)

    MOV EBX, OFFSET arr
    ADD EBX, EAX        ; EBX = address of arr[row][col]

    call ReadInt        ; read value into EAX
    MOV [EBX], EAX      ; store into array

    INC EDI
    JMP col_loop

next_row:
    INC ESI
    JMP row_loop

done:
    exit
main ENDP
END main
