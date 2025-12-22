INCLUDE Irvine32.inc

.data
    msgLooping   BYTE "LOOPZ: still looping...", 0
    msgDone      BYTE "LOOPZ: finished.", 0

.code
main PROC
    mov ecx, 5          ; loop counter = 5

    myLoop:
    	cmp eax, eax        ; sets ZF = 1 (because eax - eax = 0)
    	loopz myLoop         ; will jump while (ecx != 0) AND (ZF == 1)

    mov edx, OFFSET msgDone
    call WriteString
    call Crlf

;LOOPNZ is also similar but it check (ECX!=0) AND (ZF==0)
;also LOOPE is same as LOOPZ an LOOPNE is same as LOOPNZ
    exit
main ENDP
END main
