  
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

cmds:
	virtual at rbx
		.cons CONS
	end virtual

	;#---------------------------------------------------ö
	;|     SETUP                                         |
	;ö---------------------------------------------------ü

.setup:
	push rbp
	push rbx
	push rdi
	push rsi

	mov rbp,rsp
	and rsp,-16
	sub rsp,\
		FILE_BUFLEN

	;---1) create menu in MT_FILE
	xor r8,r8
	xor r9,r9
	mov rdx,tMP_FI_CMD
	mov rcx,[hMT_FILE]
	call mnu.mp_add
	mov [hMP_FI_CMD],rax

	mov r9d,MI_SEP
	call mnu.mp_add

	;---2) copy menu to MT_SECT
	xor r8,r8
	mov r9,MP_FI_CMD
	mov rdx,[hMT_FILE]
	mov rcx,[hMT_SECT]
	call mnu.mp_track

	mov r9d,MI_SEP
	call mnu.mp_add
	
	xor eax,eax
	xor ebx,ebx
	xor edi,edi

	mov edx,uzConfName
	mov rcx,rsp

	;--- open config/command.utf8 ----
	push rax
	push uzUtf8Ext
	push uzCommand
	push uzSlash
	push rdx
	push rcx
	push rax
	call art.catstrw

	mov rcx,rsp
	call [top64.parse]

	test eax,eax
	jz	.setupE
	test edx,edx
	jz	.setupF

	mov [pTopCmd],rax
	mov rbx,rax
	mov rsi,rax

.setupA:
	;1)--- traverse to find items like 
	;--- .: 
	;--- cmd:
	mov eax,[rsi+\
		TITEM.hash]

	cmp eax,HASH_env
	jz	.setupN
	mov rdx,rsi

	;--- TODO: and
	sub eax,HASH_lt
	jc .setupN
	cmp eax,\
		HASH_un - HASH_lt
	jna .setupB

.setupN:
	mov esi,[rsi+\
		TITEM.next]
	add rsi,rbx
	cmp rsi,rbx
	jnz	.setupA

.setupF:
	test edi,edi
	jnz	.setupE
	call .discard

.setupE:
	mov rsp,rbp
	mov rax,rdi
	pop rsi
	pop rdi
	pop rbx
	pop rbp
	ret 0

	;---	mov eax,16
	;---	jmp	.setupB
	;---.setupEQ:
	;---	mov eax,17
	;---	jmp	.setupB
	;---.setupLT:
	;---	mov eax,18

.setupB:
	mov edx,[rdx+\
		TITEM.attrib]
	test edx,edx
	jz .setupN

	add rdx,rbx
	cmp [rdx+\
		TITEM.type],TNUMBER
	jz .setupB
	xor ecx,ecx
	cmp [rdx+\
		TITEM.type],TQUOTED
	jnz	.setupN
	cmp cx,[rdx+\
		TITEM.len]
	jz	.setupN

	lea r9,[rdx+\
		TITEM.value]
	mov rdx,tMI_CMDI
	mov r8,rdi
	add dx,di
	add eax,CMDS_BASEICON		;--- index base icon
	mov rcx,[hMP_FI_CMD]
	shl eax,16
	or rdx,rax
	;--- in RCX hMenuParent/0
	;--- in RDX type/flags/0
	;--- in R8 position
	;--- in R9 0/eventual utf8 string
	call mnu.mp_add
	test r10,r10
	jz	.setupN

	inc edi
	mov [r10+\
		OMNI.param],rsi
	jmp	.setupN

	;#---------------------------------------------------ö
	;|     CMDS.DISCARD                                  |
	;ö---------------------------------------------------ü

.discard:
	;--- release strings mem/destroy items hauptmenu
	push rbx
	push rdi
	push rsi

	sub rsp,\
		sizea16.MENUITEMINFOW
	mov rsi,[hMP_FI_CMD]
;@break
	mov rcx,rsi
	call apiw.get_mnicount
	test eax,eax
	jz	.discardC

	mov rdi,rax
	mov rbx,art.a16free
	jmp	.discardB

.discardA:
	mov r9,rsp
	mov [r9+\
		MENUITEMINFOW.fMask],\
		MIIM_DATA
	mov rdx,rdi
	mov rcx,rsi
	call apiw.mni_get_bypos

	mov rcx,[rsp+\
		MENUITEMINFOW.dwItemData]
	call rbx

	mov r8,MF_BYPOSITION	
	mov edx,edi
	mov rcx,rsi
	call apiw.mnu_del

.discardB:
	dec rdi
	jns .discardA

.discardC:
	;--- simply destroy. OMNI already discarded
	xor eax,eax
	mov rcx,rsi
	mov [hMP_FI_CMD],rax
	call apiw.mnu_destroy

	;---1) remove anyway items 0,1 (separator) on MT_FILE
	mov r8,MF_BYPOSITION
	xor edx,edx
	mov rcx,[hMT_FILE]
	call apiw.mnu_del

	mov r8,MF_BYPOSITION
	xor edx,edx
	mov rcx,[hMT_FILE]
	call apiw.mnu_del

	mov r8,MF_BYPOSITION
	xor edx,edx
	mov rcx,[hMT_SECT]
	call apiw.mnu_del

	mov r8,MF_BYPOSITION
	xor edx,edx
	mov rcx,[hMT_SECT]
	call apiw.mnu_del

	;--- discard CMDS memory
	xor eax,eax
	mov rcx,[pTopCmd]
	mov [pTopCmd],rax
	call [top64.free]
	
.discardE:
	add rsp,\
		sizea16.MENUITEMINFOW
	pop rsi
	pop rdi
	pop rbx
	ret 0

	;#---------------------------------------------------ö
	;|     CMDS.EXPAND                                   |
	;ö---------------------------------------------------ü

.expand:
	;--- in RCX utf16 line to be expanded
	;--- in/out RDX buffer FILE_BUFLEN*2
	;--- in R8 path
	;--- in R9 filename.ext
	;-----------------------------------------------
	;---x	<d> DRIVE in "DRIVE:\MYPATH\FILENAME.EXT"
	;---x	<f> "FILENAME.EXT"
	;---x	<n> FILENAME
	;---x	<e> EXT
	;---x	<p> DRIVE:\MYPATH
	;---x << >> escape < >
	;---x	# ;--- optional command exec and redirect output here
	;---x	- ;--- execute command and close shell
	;---x	+ ;--- execute command and stay open
	;-----------------------------------------------
	;--- example: C:\mydir\myfile.dll
	;---"polib.exe /OUT:<n>.lib /MAKEDEF:<n>.def <n>.<e>"
	;---"polib.exe /OUT:myfile.lib /MAKEDEF:myfile.def myfile.dll"
	;-----------------------------------------------
	push rbx
	push rdi
	push rsi
	push r12
	push r13
	push r14

	xor eax,eax
	mov rsi,rcx
	mov rdi,rdx
	mov r12,r8
	mov r13,r9

	mov ecx,MAX_CMDCPTS +1
	push rdi
	cmp word[rsi],"#"
	jnz	.expandA
	dec ecx
	jz	.expandA2
	add rsi,2
	jmp	.expandA

.expand_drive:
	xor eax,eax
	sub ecx,2
	jle .expandA2
	mov edx,dword[r12]
	mov [rdi],edx
	add rdi,4
	jmp .expandC1

.expand_ext:
	mov r14,rcx
	mov rcx,r13
	call art.get_ext
	
	test eax,eax
	jz .err_expand
	shr ecx,1
	sub r14,rcx
	jle .err_expand

	push rsi
	mov rsi,rax
	rep movsw
	mov rcx,r14
	xor eax,eax
	pop rsi
	jmp .expandC1

.expand_name:
	mov r8,"."
	mov r9,r13

.expand_nameD:
	push rsi
	xor eax,eax
	mov rsi,r9
	jmp	.expand_nameB

.expand_nameC:
	stosw

.expand_nameB:	
	lodsw
	test eax,eax
	jz	.expand_nameA
	cmp ax,r8w
	jz	.expand_nameA
	dec ecx
	jnz	.expand_nameC
	add rsp,8
	jmp	.err_expand

.expand_nameA:
	xor eax,eax
	pop rsi
	jmp .expandC1

.expand_filename:
	xor r8,r8
	mov r9,r13
	jmp	.expand_nameD

.expand_path:
	dec ecx
	jz	.err_expand
	xor r8,r8
	mov r9,r12
	mov eax,"\"
	cmp word[r12],"%"
	jz .expand_nameD

	add r9,4  ;--- point after C:
	cmp ax,word[r9]
	jz .expand_nameD	

	cmp word[r9],"/"
	jz .expand_nameD
	stosw
	jmp	.expandC1
	
.expandC:
	cmp eax,"d"
	jz	.expand_drive
	cmp eax,"e"
	jz	.expand_ext
	cmp eax,"f"
	jz	.expand_filename
	cmp eax,"n"
	jz	.expand_name
	cmp eax,"p"
	jz	.expand_path

.expandC1:
	lodsw
	cmp eax,">"
	jnz	.err_expand

.expandA:	
	dec ecx
	jnz	.expandA1
	xor eax,eax
	jmp .expandA2

.expandA1:
	lodsw
	cmp eax,"<"
	jz	.expandT
	cmp eax,">"
	jnz	.expandA2
	;--- found  ">"
	lodsw
	cmp eax,">"
	jz	.expandA2

.err_expand:
	mov rdi,[rsp]
	jmp	.expandE
	
.expandT:
	;--- found first "<"
	lodsw
	cmp eax,"<"
	jnz	.expandC
	
.expandA2:
	stosw
	test eax,eax
	jnz	.expandA
	
.expandE:
	pop rdx
	mov rax,rdi
	sub rax,rdx
	add rax,rax

	pop r14
	pop r13
	pop r12
	pop rsi
	pop rdi
	pop rbx
	ret 0

