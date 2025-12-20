INCLUDE Irvine32.inc

.data
    num1 DWORD 48
    num2 DWORD 18
    result DWORD ?

.code

GCD PROC a:DWORD, b:DWORD
    CMP b, 0
    JE  gcd_done

    ; Compute a % b
    MOV EAX, a
    XOR EDX, EDX
    DIV b        

    INVOKE GCD, b, EDX
    RET
gcd_done:
    MOV EAX, a
    RET
GCD ENDP

main PROC
    INVOKE GCD, num1, num2
    MOV result, EAX  
    call writeDec
    exit
main ENDP

END main
