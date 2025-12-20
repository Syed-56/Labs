INCLUDE Irvine32.inc

.data
  input BYTE "HE#L#LO # #WO#RL#L#D", 0
  output BYTE ($-LENGTHOF input) DUP(?)
  key BYTE "#"

.code
main PROC
  MOV ESI, OFFSET input
  MOV EDI, OFFSET output
  MOV ECX, LENGTHOF input
  CLD
  
  L1:
    LODSB
    CMP AL, key
    JE skip
    STOSB

    skip:
    LOOP L1
  
  done:
   MOV BYTE PTR [EDI], 0
   exit
main ENDP
END main