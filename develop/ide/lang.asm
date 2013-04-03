  
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

lang:
	virtual at rbx
		.mii MENUITEMINFOW
	end virtual

	virtual at rdi
		.conf CONFIG
	end virtual

.reload:
	;--- in RCX lcid
	;--- RET IDYES IDNO
	push rbx
	push rdi
	push rsi

	sub rsp,\
		FILE_BUFLEN

	mov rbx,rcx		;--- lcid
	mov rsi,rsp
	mov rdi,[pConf]

	xor r9,r9
	mov r8,\
		LOCALE_NAME_MAX_LENGTH
	mov rdx,rsi
	mov rcx,rbx
	call apiw.lcid2name

	;---	push rax
	;---	push rcx
	;---	push rdx

	;---;@break
	;---	mov r8,rsi
	;---	mov rdx,rax
	;---	call art.cout2XU

	;---	pop rdx
	;---	pop rcx
	;---	pop rax

	test eax,eax
	jz	.reloadE
	mov [.conf.lcid],bx

	mov rcx,rsi
	lea rdx,[.conf.lang16]
	call utf16.copyz

	mov rcx,rsi
	lea rdx,[.conf.lang8]
	call utf16.to8

	call mnu.get_dir
	mov rsi,rax
	call .unset
	call mnu.discard
	lea rcx,[.conf.lang16]
	call .def
	call mnu.setup
	mov rcx,rsi
	call mnu.set_dir
	
.reloadE:
	add rsp,\
		FILE_BUFLEN
	pop rsi
	pop rdi
	pop rbx
	ret 0


.enum:
	push rbp
	push rdi
	mov rbp,rsp

	mov rcx,[hMP_LANG]
	call mnu.reset

	sub rsp,\
	 FILE_BUFLEN+20h
	
	xor edx,edx
	mov rdi,rsp

;@break
	mov eax,"*"
	stosw
	mov rax,qword[uzBinExt]
	stosq
	xor eax,eax
	stosw
	stosd

	stosq
	stosq

	mov rdx,rdi
	mov rax,\
		qword[uzLangName]
	stosq
	xor eax,eax
	stosq
	mov rcx,rdx

	;---	in RCX upath		;--- example "E:" or "E:\mydir"
	;---	in RDX uattr		;--- FILE_ATTRIBUTE_HIDDEN
	;---	in R8  ulevel		;--- nesting level to stop search 0=all
	;---	in R9  ufilter	;--- "*.asm"
	;---	in R10 ucback   ;--- address of a calback
	;---	in R11 uparam   ;--- user param
	;---------------------------------------------------
	lea r11,[rsp+10h]
	mov r10,.cb_lang
	xor r8,r8
	inc r8
	mov r9,rsp
	mov edx,FILE_ATTRIBUTE_NORMAL
	call [bk64.listfiles]

	mov rsp,rbp
	pop rdi
	pop rbp
	ret 0


.cb_lang:
	;---  the calback receives those args
	;--- in RCX path
	;--- in RDX w32fnd 
	;--- in R8h lenpath
	;--- in R9 uparam
	;--- ret RAX = 1 continue, 0 stop search
	test rdx,rdx
	jz	.cb_langA

	mov eax,[rdx+\
		WIN32_FIND_DATA.dwFileAttributes]
	test eax,\
		FILE_ATTRIBUTE_DIRECTORY
	jnz  .cb_langA

	;---	test eax,\
	;---		FILE_ATTRIBUTE_ARCHIVE
	;---	jz  .cb_langA
	lea rcx,[rdx+\
		WIN32_FIND_DATA.cFileName]
	push r9
	push rcx
	call art.get_ext
	pop rcx
	xor r10,r10
	pop r9
	test eax,eax
	jz .cb_langB
	mov [rax-2],r10
	mov rdx,[r9]
	inc dword[r9]
	call .set_item

.cb_langB:

 .cb_langA:
	xor eax,eax
	inc eax
	ret 0


.set_item:
	;--- in RCX lcid filename [en-US]
	;--- in RDX ord id
	push rbp
	push rbx
	push rsi
	push rdi
	push r12
	push r13

	mov rbp,rsp
	sub rsp,\
		sizeof.MENUITEMINFOW+\
		FILE_BUFLEN

	mov rbx,rsp
	mov rsi,rcx
	lea rdi,[rsp+\
		sizeof.MENUITEMINFOW]
	mov r12,rdx

	;--- check against bad locales
	;--- min VISTA
	mov rcx,rsi
	call apiw.is_locname
	test eax,eax
	jz	.set_itemE

	;--- check again [lang\xxxx.bin]
	xor edx,edx

	push rdx
	push uzBinExt
	push rsi
	push uzSlash
	push uzLangName
	push rdi
	push rdx
	call art.catstrw

	mov rcx,rdi
	call art.is_file
	jz	.set_itemE

	mov r9,4
	mov r8,rdi
	mov edx,\
		LOCALE_ILANGUAGE or \
		LOCALE_RETURN_NUMBER
	mov rcx,rsi
	call apiw.get_locinfox
	mov eax,[rdi]
	mov r13,rax

	mov eax,"["
	stosw
	mov rcx,rsi
	mov rdx,rdi
	call utf16.copyz
	add rdi,rax
	mov eax,"]"
	stosw
	mov al,09h
	stosw

	mov r9,\
		LOCALE_NAME_MAX_LENGTH
	mov r8,rdi
	mov edx,\
		LOCALE_SNATIVELANGUAGENAME
	mov rcx,rsi
	call apiw.get_locinfox
	add rdi,rax
	add rdi,rax
	sub rdi,2
;---	mov eax,')'
;---	stosw
	xor eax,eax
	stosd
	
	mov [.mii.fMask],\
		MIIM_STRING or \
		MIIM_FTYPE or \
		MIIM_DATA or \
		MIIM_ID or \
		MIIM_CHECKMARKS or \
		MIIM_STATE

	mov [.mii.hbmpChecked],rax
	mov [.mii.hbmpUnchecked],rax

	mov rdx,[pConf]
	mov [.mii.fState],eax
	mov ecx,MFS_CHECKED

	;---	push rax
	;---	push rcx
	;---	push rdx

	;---	;@break
	;---	movzx r8d,[rdx+\
	;---		CONFIG.lcid]
	;---	mov rdx,r13
	;---	call art.cout2XX

	;---	pop rdx
	;---	pop rcx
	;---	pop rax

	cmp r13w,[rdx+\
		CONFIG.lcid]
	cmovz eax,ecx
	mov [.mii.fState],eax
	
	mov [.mii.fType],\
		MFT_STRING

	mov rax,r12
	add eax,MI_LANG
	mov [.mii.wID],eax

	mov [.mii.dwItemData],r13

	lea rax,[rsp+\
		sizeof.MENUITEMINFOW]
	mov [.mii.dwTypeData],rax
	
	mov r9,rbx
	mov rdx,r12
	mov rcx,[hMP_LANG]
	call apiw.mni_ins_bypos

	;---	lea r8,[rsp+\
	;---		sizeof.MENUITEMINFOW]
	;---	mov rdx,r13
	;---	call art.cout2XU

.set_itemE:
	mov rsp,rbp
	pop r13
	pop r12
	pop rsi
	pop rdi
	pop rbx
	pop rbp
	ret 0




.info_uz:
	;--- in RCX pMem
	;--- ret RAX ave dlen/ids
	;--- ret ECX pMem->header
	;--- ret RDX lang string
	;--- ret R8 ids
	;--- ret R9 dlen
	;--- ret R10 lcid
	movzx eax,[rcx+\
		RESTABLE.dave]
	lea rdx,[rcx+\
		RESTABLE.lang]
	movzx r9,[rcx+\
		RESTABLE.dlen]
	movzx r10,[rcx+\
		RESTABLE.lcid]
	movzx r8d,[rcx+\
		RESTABLE.ids]
	ret 0

.get_uz:
	;--- in RCX pMem
	;--- in RDX id
	;--- in/out R8 buffer/0
	;---
	;--- to get original string ------
	;--- in RCX pMem
	;--- in RDX id
	;--- in R8=0

	;--- RET RAX len
	;--- RET RCX dest string
	;--- RET RDX id/-1 no translation

	movzx r9,[rcx+\
		RESTABLE.resi]
	mov eax,edx
	and eax,0FFh
	add r9,rcx
	movzx eax,\
		word[r9+rax*2]
	add r9,512
	jmp	.get_uzN


.get_uzN1:
	movzx eax,\
		[r11+RESDEF.next]

.get_uzN:
	inc ax
	jnz	.get_uzN2

.get_uzE:
	movzx eax,[rcx+\
		sizeof.RESTABLE+\
		RESDEF.len]
	or rdx,-1
	lea rcx,[rcx+\
		sizeof.RESTABLE+\
		sizeof.RESDEF]
	jmp	.get_uzN3

.get_uzN2:
	dec ax
	lea r11,[r9+rax]
	cmp dx,[r11+\
		RESDEF.id]
	jnz	.get_uzN1

	movzx eax,[r11+\
		RESDEF.len]

	lea rcx,[r11+\
		sizeof.RESDEF]

	movzx rdx,[r11+\
		RESDEF.id]

.get_uzN3:
	test r8,r8
	jnz	.get_uzC
	xchg rax,rcx
	ret 0

.get_uzC:
	push r8
	push rdx

	xchg eax,eax
	xchg rdx,r8
	call utf8.to16

	pop rdx
	pop rcx
	ret 0



	;ü-----------------------------------------ö
	;|     DEF_LANG                            |
	;#-----------------------------------------ä

.def:
	;--- in RCX langname
	;--- ret RAX bridge
	push rbx
	push rdi

	xor edx,edx
	sub rsp,\
		FILE_BUFLEN
	mov rax,rsp
	xor ebx,ebx

	;--- make lang\CURLANG
	push rdx
	push uzBinExt
	push rcx
	push uzSlash
	push uzLangName
	push rax
	push rdx
	call art.catstrw

	mov rcx,rsp
	call art.mfload
	test eax,eax
	jz .def_langE

	mov rdi,[pTime]
	mov rbx,rax
	mov [pLangRes],rax

	lea r8,[rdi+\
		SYSTIME.uzTmFrm]
	mov edx,UZ_TIMEFRM
	mov rcx,rbx
	call lang.get_uz 	;--- "HH':'mm':'ss"
	
	lea r8,[rdi+\
		SYSTIME.uzDtFrm]
	mov rcx,rbx
	mov edx,UZ_DATEFRM 
	call lang.get_uz 	;--- "dddd','dd'.'MMMM'.'yyyy"

	mov rdi,[pConf]
	lea r8,[.conf.owner]
	mov rcx,rbx
	mov edx,UZ_DEFUSER
	call lang.get_uz 	;--- "Mr.Biberkopf"

.def_langE:
	add rsp,\
		FILE_BUFLEN

	mov rax,rbx
	pop rdi
	pop rbx
	ret 0

.unset:
	xor eax,eax
	mov rcx,[pLangRes]
	mov [pLangRes],rax
	call art.a16free
	ret 0
