  
  ;#-------------------------------------------------ß
  ;|          x64lab  MPL 2.0 License                |
  ;|   Copyright (c) 2009-2012, Marc Rainer Kranz.   |
  ;|            All rights reserved.                 |
  ;ö-------------------------------------------------ä

  ;#-------------------------------------------------ß
  ;| simple read textfile
  ;| compile: fasm readfile_ask.asm
  ;| usage:readfile_ask
  ;ö-------------------------------------------------ä

 format PE CONSOLE 5.0
 entry start
 include 'win32a.inc'

section '.data' data readable writeable
  bytesRead dd 0
  szBuf db 1024 dup (0)
  szErr db "Error while reading",0
	szMsg db "Please enter a valid filename : ",0
	szSize db "Filesize is : %d bytes",13,10,0
  szOk  db "Ok",13,10,0

section '.code' code readable executable
start:
 xor ebx,ebx

 push szMsg		 ;--- print useful message
 call [printf]
 add esp,4		 ;--- adjust stack here for push once

 push szBuf		 ;--- ready to accept a single line containing filename
 call [gets]
 add esp,4
 test eax,eax
 jz	.err

 push 0             ;--- template not required
 push FILE_ATTRIBUTE_NORMAL ;--- normal file
 push OPEN_EXISTING	;--- how to create  
 push 0             ;--- pointer to security attributes not strictly required

 push FILE_SHARE_READ	\
	or FILE_SHARE_WRITE    ;--- can be shared

 push GENERIC_READ ;--- access it for reading 
 push szBuf		     ;--- filename
 call [CreateFile] 
 test eax,eax
 jle .err
 mov ebx,eax

 push 0         ;--- file must be < 4Gb
 push ebx       ;--- handle of file to get size of
 call [GetFileSize]
 test eax,eax   ;--- zero or > 7FFFFFFFh not accepted as size here
 jle .err

 push eax
 push szSize
 call [printf]
 add esp,8      ;--- c-calling covention adjust stack for 2 push dword

.readN:
 push 0					;---address of structure for data 
 push bytesRead ;---address of number of bytes read 
 push 1024			;---number of bytes to read 
 push szBuf			;---address of buffer that receives data  
 push ebx				;---handle of file to read 
 call [ReadFile] ;--- after a successful read the filepointer is automagically after bytesRead

 xor ecx,ecx
 test eax,eax
 jz .err

 cmp ecx,[bytesRead]  ;--- if bytesRead is 0 we are at EOF
 jnz .readP

 push szOk
 jmp .ok

.readP:
 push szBuf			;--- print content
 call [printf]
 add esp,4
 jmp .readN

.err:
 push szErr			;--- print error message

.ok:
 call [printf]
 add esp,4

 test ebx,ebx   ;--- check if filehandle is ok
 jz .exit

 push ebx
 call [CloseHandle] 

.exit:
 ret 0

 section '.idata' import data readable writeable

	library \
		kernel32,'KERNEL32',\
		msvcrt,"MSVCRT",\
		user32,'USER32'

	include 'api\kernel32.inc'
	include 'api\user32.inc'
        
  import msvcrt,\
   printf,"printf",\
   gets,"gets",\
   strlen,"strlen" 
