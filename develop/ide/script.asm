  
  ;#-------------------------------------------------ß
  ;|          x64lab  MPL 2.0 License                |
  ;|   Copyright (c) 2009-2012, Marc Rainer Kranz.   |
  ;|            All rights reserved.                 |
  ;ö-------------------------------------------------ä

  ;#-------------------------------------------------ß
  ;| uft-8 encoded üäöß
  ;| update:
  ;| filename:
  ;ö-------------------------------------------------ä

script:
	;---	command script future implementation
	;---	# ;--- command exec and redirect output here
	;---	> ;--- set x64lab
	;---	< ;--- get x64lab
	;---	? ;--- help x64lab
	;---	- ;--- execute command and close shell /C
	;---	+ ;--- execute command and stay open /K

	virtual at rdi
		.conf CONFIG
	end virtual

	virtual at rbx
		.cmdt CMDT
	end virtual

	;#---------------------------------------------------ö
	;|     .ENV                                          |
	;ö---------------------------------------------------ü
.env:
	;--- in RCX name
	;--- in RDX value
	;--- in R8 flags 
	;--- in R9 param
	push rbp
	push rbx
	push rdi
	push rsi
	push r12
	push r13
	push r14
	push r15

	mov rbp,rsp
	xor r13,r13
	and rsp,-16
	xor r14,r14
	xor r15,r15

	sub rsp,\
		FILE_BUFLEN*3

	mov rbx,r8
	mov r12,r9
	mov rsi,rcx
	mov rdi,rdx

	test ecx,ecx
	jz	.envE
	test ebx,\
		FSCR_816
	jz	.envE
	and ebx,\
		not FSCR_816

	;--- convert name to utf-16
	mov rdx,rsp
	mov rcx,rsi
	call utf8.to16
	jc .envE

	xor ecx,ecx
	mov rsi,rsp
	lea r14,[rsp+rax]
	mov [r14],rcx
	mov [r14+8],rcx
	@nearest 16,r14

	test rdi,rdi
	jz	.envA
	
	;--- convert value to utf-16
	mov rdx,r14
	mov rcx,rdi
	call utf8.to16
	jc .envE
	xor ecx,ecx
	mov rdi,rax		;--- store len value
	mov [r14+rax],rcx
	mov [r14+rax+8],rcx

.envA:
	test ebx,\
		FSCR_SET
	jz .envE
	and ebx,\
		not FSCR_SET

	xor eax,eax
	sub rsp,ENVV_BUFLEN
	mov rdx,rsp
	mov rcx,r14
	mov [rsp],rax
	call apiw.exp_env

	;--- set env utf16
	mov rdx,rsp
	mov rcx,rsi
	call apiw.set_env

	add rsp,ENVV_BUFLEN
	test eax,eax
	jz	.envE

	;--- store env NAME in config.env
	test ebx,\
		FSCR_LAB
	jz .envE
	and ebx,\
		not FSCR_LAB

	;--- calc hash of env NAME
	mov rcx,rsp
	call utf16.zsdbm
	mov r15,rax	;--- store hash
	mov rsi,rdx	;--- store len

	;--- check if hash exist in pConf
	mov rax,[pConf]
	mov rdx,[rax+\
		CONFIG.env]
	xor ecx,ecx
	xor r8,r8
	test edx,edx
	jz	.envL
	
.envN:
	cmp r15d,[rdx+\
		LABENV.hash]
	jz .envL
	
.envN1:
	cmp r8,[rdx+\
		LABENV.next]
	jz .envL3
	mov rcx,rdx
	mov rdx,[rdx+\
		LABENV.next]
	jmp	.envN

.envL3:
	push rcx
	push [rdx+\
		LABENV.next]
	jmp	.envL4

.envL:
	;--- in RCX prev
	;--- in RDX current
	push rcx
	test edx,edx
	jz	.envL1
	mov rax,[rdx+\
		LABENV.next]

	push rax
	mov rcx,rdx
	call art.a16free

.envL4:
	pop rdx

.envL1:
	pop rcx
	test rcx,rcx
	jz .envL2
	mov [rcx+\
		LABENV.next],rdx

.envL2:
	;--- set env name in pConf
	;--- mov r15,rax
	mov rcx,rsi
	@nearest 16,ecx
	add rcx,rdi
	@nearest 16,ecx
	add ecx,\
		sizeof.LABENV
	call art.a16malloc
	test eax,eax
	jz	.envE

	mov r8,[pConf]
	mov r13,rax
	mov [rax+\
		LABENV.hash],r15d
	mov r9,[r8+\
		CONFIG.env]
	mov [rax+\
		LABENV.next],r9
	mov [r8+\
		CONFIG.env],rax
	mov [rax+\
		LABENV.nlen],si
	mov [rax+\
		LABENV.vlen],di

	add rax,\
		sizeof.LABENV

	mov r8,rsi
	@nearest 16,r8
	add r8,rdi
	@nearest 16,r8

	mov rdx,rax
	mov rcx,rsp
	call art.xmmcopy

.envE:
	mov rax,r13
	mov rsp,rbp
	pop r15
	pop r14
	pop r13
	pop r12
	pop rsi
	pop rdi
	pop rbx
	pop rbp
	ret 0


	;#---------------------------------------------------ö
	;|     .SPAWN                                        |
	;ö---------------------------------------------------ü

.spawn:
	;--- in RCX appname
	;--- in RDX cmdline
	;--- in R8 lpCurrentDirectory
	;--- in R9 hWrite
	;--- in R10 flags SHOW
	push rbp
	push rbx
	push rdi
	push rsi
	push r12
	push r13
	push r14

	xor ebx,ebx
	mov r14,r10
	mov rsi,rcx
	mov rbp,rsp
	xor eax,eax
	mov r13,r9
		
	mov r11,STARTF_USESTDHANDLES
	test r9,r9
	cmovz r11,rax
	cmovz r13,rax

	and rsp,-16
	or r11,STARTF_USESHOWWINDOW	

	sub rsp,\
		sizea16.STARTUPINFO+\
		sizea16.PROCESS_INFORMATION

	mov rdi,rsp
	mov ecx,\
		(sizea16.STARTUPINFO+\
		sizea16.PROCESS_INFORMATION) / 8
	xor eax,eax
	rep stosq

	mov rdi,rdx

	mov rax,rsp
	lea rdx,[rsp+\
		sizea16.STARTUPINFO]
	mov r12,rdx

	mov [rax+\
		STARTUPINFO.cb],\
		sizeof.STARTUPINFO

	mov [rax+\
		STARTUPINFO.dwFlags],r11d

	mov [rax+\
		STARTUPINFO.hStdOutput],r13
	mov [rax+\
		STARTUPINFO.hStdInput],r13
	mov [rax+\
		STARTUPINFO.hStdError],r13

	mov [rax+\
		STARTUPINFO.wShowWindow],r14w

	mov r11,\
		CREATE_UNICODE_ENVIRONMENT 
	;or DETACHED_PROCESS;or CREATE_NEW_CONSOLE
	;---cmp [myvar],-1
	;---jz	.ok
	;---or r11,CREATE_SUSPENDED 

	;---.ok:

	;---	push rax
	;---	push rdx
	;---	push r8
	;---	push r11

	;---	mov r8,\
	;---		FSCR_SET or \
	;---		FSCR_816
	;---	xor r9,r9
	;---	mov rdx,myval
	;---	mov rcx,mydummy
	;---	call script.env

	;---	mov rdx,mystring
	;---	mov rcx,mydummy
	;---	call apiw.set_env

	;---	pop r11
	;---	pop r8
	;---	pop rdx
	;---	pop rax

	xor ecx,ecx

	push rdx ;--- PROCESS_INFORMATION
	push rax ;--- STARTUPINFO
	push r8  ;--- lpCurrentDirectory
	push rcx ;--- lpEnvironment
	push r11 ;--- dwCreationFlags
	push 1;rcx ;--- bInheritHandles

	xor r9,r9
	xor r8,r8
	mov rdx,rdi
	mov rcx,rsi
	sub rsp,20h
	call [CreateProcessW]
	mov rbx,rax

	mov rcx,[r12+\
		PROCESS_INFORMATION.hThread]
	call art.hclose

	mov rcx,[r12+\
		PROCESS_INFORMATION.hProcess]
	call art.hclose

	;---	;---cmp [myvar],-1
	;---	;---jz .okE
	;---	mov rdx,mystring
	;---	mov rcx,mydummy
	;---	call apiw.set_env

	;---	mov rcx,[r12+\
	;---		PROCESS_INFORMATION.hThread]
	;---	call apiw.tresume

	;---.okE:
	;---inc [myvar]
	;---inc word[mystring]

	mov rax,rbx
	mov rsp,rbp
	pop r14
	pop r13
	pop r12
	pop rsi
	pop rdi
	pop rbx
	pop rbp
	ret 0



.exec:
	;--- in RCX pCmdT
	push rbp
	push rbx
	push rdi
	push rsi
	push r12
	push r13
	push r14
	push r15

	mov rbp,rsp
	mov rbx,rcx
	and rsp,-16
	sub rsp,\
		1000h+30h

	lea r12,[rsp+1010h]
	lea r14,[rsp+1018h]
	xor r13,r13
	mov rax,[pCons]
	mov r15,[rax+\
		CONS.hSci]

	mov rsi,rsp
	xor eax,eax
	xor edi,edi
	
	mov [r12],rax
	mov [r14],rax

	mov [rsi+\
		SECURITY_ATTRIBUTES.nLength],\
		sizeof.SECURITY_ATTRIBUTES 
	mov [rsi+\
		SECURITY_ATTRIBUTES.bInheritHandle],TRUE
 	mov [rsi+\
		SECURITY_ATTRIBUTES.lpSecurityDescriptor],rax
	
	mov r9,1000h
	mov r8,rsi
	mov rdx,r14	;--- R14 write
	mov rcx,r12	;--- R12 read
	call apiw.cpipe
	test eax,eax
	jz .execF

	mov rdx,[r12]
	mov rcx,STD_OUTPUT_HANDLE	
	call apiw.set_stdh

	mov rdx,[r12]
	mov rcx,STD_INPUT_HANDLE	
	call apiw.set_stdh

	mov rdx,[r12]
	mov rcx,STD_ERROR_HANDLE	
	call apiw.set_stdh

;@break
	mov r10,SW_HIDE
	mov r9,[r14]
	mov r8,[.cmdt.path]
	mov rdx,[.cmdt.cmdl]
	xor ecx,ecx
	call .spawn

.execF:
	mov rdi,rax
	mov rcx,[r14]
	call art.hclose
;@break

	movzx eax,[.cmdt.iType]
	mov r14,.execU
	mov r8,.execA
	sub eax,CMDS_BASEICON
	cmovz r14,r8

	lock and[.cmdt.flags],0
	test edi,edi
	jz .execE

;@break

	;--- in RCX handle
	;--- in RDX pmem
	;--- in R8 num byte to read
.execN:
	mov r8,1000h
	mov rdx,rsi
	mov rcx,[r12]
	call art.fread
	xor edx,edx
	mov r13,rcx
	mov dword[rcx+rsi],edx
	test eax,eax
	jz	.execE
	jmp	r14

.execA:
;---	mov rdx,rsi
;---	mov rcx,rsi
;---	call apiw.oem2char

	or r9,-1
	or r8,-1
	mov rcx,r15
	call sci.set_sel

	mov r9,rsi
	xor r8,r8 
	mov rcx,r15
	call sci.repl_sel
	jmp	.execU1

.execU:
	xor edx,edx
	mov rcx,rsi
	call console.out

.execU1:
	test r13,r13
	jnz	.execN

.execE:
	mov rcx,[r12]
	call art.hclose
	mov rax,rdi

	mov rsp,rbp
	pop r15
	pop r14
	pop r13
	pop r12
	pop rsi
	pop rdi
	pop rbx
	pop rbp
	ret 0
	
	


