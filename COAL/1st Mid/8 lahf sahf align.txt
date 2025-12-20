INCLUDE Irvine32.inc

.data
	var1 db 10h	;OFFSET => 0001h
	ALIGN 4		;OFFSet => 0001h to 0004h
	var2 dd 12345678h	;OFFSET => 0008h (otherwise it would be 0005h)
.code
main PROC
	mov ah, 0          ; clear AH
	lahf               ; load flags into AH
	; now AH contains flag bits

	mov ah, 02h        ; modify AH manually
	sahf               ; update flags from AH

	exit
main ENDP
END main