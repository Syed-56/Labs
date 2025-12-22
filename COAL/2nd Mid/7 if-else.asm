INCLUDE Irvine32.inc

.data
    msgEQ BYTE "EAX = EBX", 0
    msgNot BYTE "EAX != EBX", 0

.code
main PROC
    MOV EAX, 10
    MOV EBX, 10
    CMP EAX, EBX
    JE equal      ; jump if equal
    JNE notEqual  ; jump if not equal

equal:             ; label definition
    MOV EDX, OFFSET msgEQ
    call WriteString
    call Crlf
    JMP done

notEqual:          ; label definition
    MOV EDX, OFFSET msgNot
    call WriteString
    call Crlf
    JMP done

done:
    exit
main ENDP
END main
