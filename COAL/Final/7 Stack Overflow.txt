INCLUDE Irvine32.inc

.data

.code

func1 PROC
	LOCAL arr1[50]: DWORD
	call func2
	RET
func1 ENDP
func2 PROC
	LOCAL arr2[80]: WORD
	call func2
	RET
func2 ENDP
func3 PROC
	LOCAL arr1[300]: DWORD
	call func2
	RET
func3 ENDP

main PROC
	call func1
	exit
main ENDP

ENd main