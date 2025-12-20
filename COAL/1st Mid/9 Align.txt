INCLUDE Irvine32.inc

.data
	var1 BYTE ?
	var2 BYTE ?
	;address is now 0x.....401 and we will be making a DWORD datatype which is 4 byte so we want to start at multiple of 4
	ALIGN 4
	var3 DWORD ?