  
  ;#-------------------------------------------------ß
  ;|          x64lab  MPL 2.0 License                |
  ;|   Copyright (c) 2009-2012, Marc Rainer Kranz.   |
  ;|            All rights reserved.                 |
  ;ö-------------------------------------------------ä

  ;#-------------------------------------------------ß
  ;| simple read text file on commandline
  ;| compile: fasm readfile.asm
  ;| usage:readfile < myfile.txt
  ;ö-------------------------------------------------ä

	format PE CONSOLE 5.0
	entry start
	include 'win32a.inc'

	section '.data' data readable writeable
		szBuf	db 1024 dup (0)
		szErr db "EOF or error while reading",0

	section '.code' code readable executable

start:
	mov edi,szBuf
	mov esi,szErr

.lineN:
	push edi
	call [gets]
	add esp,4
	
	test eax,eax
	cmovz edi,esi

	push edi
	call [strlen]
	add esp,4
	mov dword[edi+eax],0D0Ah

	push edi
	call [printf]
	add esp,4

	cmp edi,esi
	jnz .lineN
	ret 0

	section '.idata' import data readable writeable
	
	library \
		msvcrt,"MSVCRT",\
		user32,'USER32'

	include 'api\user32.inc'

	import msvcrt,\
		printf,"printf",\
		gets,"gets",\
		strlen,"strlen"
