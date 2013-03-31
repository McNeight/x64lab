  
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

mnu:
	virtual at rbx
		.mii MENUITEMINFOW
	end virtual

	;#---------------------------------------------------ö
	;|                   SETUP                           |
	;ö---------------------------------------------------ü

.setup:
	push rbx
	push rdi
	push rsi

	;--- create main menu
	call apiw.mnu_create
	mov [hMnuMain],rax

	;--- main menu ------------
	xor r8,r8
	mov rcx,rax
	mov rsi,.mp_add

	;--- General top menu
	mov rdx,tMP_WSPACE
	call rsi
	mov [hMP_WSPACE],rax

;---	mov rdx,tMP_FILE
;---	call rsi
;---	mov [hMP_FILE],rax

	mov rdx,tMP_EDIT
	call rsi
	mov [hMP_EDIT],rax

	mov rdx,tMP_CONF
	call rsi
	mov [hMP_CONF],rax

	mov rdx,tMP_PATH
	call rsi
	mov [hMP_PATH],rax

		;--- WORKSPACE --------
		xor r8,r8
		mov rcx,[hMP_WSPACE]
		mov rdx,tMI_WS_LOAD
		call rsi
		mov rdx,tMI_SEP
		call rsi
		mov rdx,tMI_WS_NEW
		call rsi
		mov rdx,tMI_FI_NEWF
		call rsi
		mov rdx,tMI_FI_IMP
		call rsi
		mov rdx,tMI_ED_LNK
		call rsi
		mov rdx,tMI_SEP
		call rsi
		mov rdx,tMI_ED_REMITEM
		call rsi
		mov rdx,tMI_SEP
		call rsi
		mov rdx,tMI_WS_SAVE
		call rsi
		mov rdx,tMI_SEP
		call rsi
		mov rdx,tMI_WS_EXIT
		call rsi

		;--- EDIT --------
		xor r8,r8
		mov rcx,[hMP_EDIT]
		mov rdx,tMI_FI_OPEN
		call rsi
		mov rdx,tMI_FI_NEWB
		call rsi
		mov rdx,tMI_FI_SAVE
		call rsi
		mov rdx,tMI_FI_CLOSE
		call rsi
		mov rdx,tMI_SEP
		call rsi
		mov rdx,tMP_SCI
		call rsi
		mov [hMP_SCI],rax

			;--- SCINTILLA ---
			xor r8,r8
			mov rcx,[hMP_SCI]
			mov rdx,tMI_SCI_RELSCICLS
			call rsi
			mov rdx,tMI_SCI_COMML
			call rsi
			mov rdx,tMI_SCI_UNCOMML
			call rsi
		
		;--- CONFIGURE --------
		xor r8,r8
		mov rdx,tMI_CONF_KEY
		mov rcx,[hMP_CONF]
		call rsi
		mov rdx,tMP_LANG
		call rsi
		mov [hMP_LANG],rax
		mov rdx,tMP_UPD
		call rsi
		mov [hMP_UPD],rax
		mov rdx,tMP_DEVT
		call rsi
		mov [hMP_DEVT],rax

			;--- UPDATE ---------
			xor r8,r8
			mov rcx,[hMP_UPD]
			mov rdx,tMI_UPD_LANG
			call rsi
			
			;--- DEVTOOL --------
			xor r8,r8
			mov rcx,[hMP_DEVT]
			mov rdx,tMI_DEVT_ADD
			call rsi
			mov rdx,tMI_DEVT_REM
			call rsi
			mov rdx,tMI_DEVT_ADDG
			call rsi
			mov rdx,tMI_DEVT_REMG
			call rsi
		
		;--- PATH --------
		xor r8,r8
		mov rcx,[hMP_PATH]
		mov rdx,tMI_PA_BROWSE
		call rsi
		mov rdx,tMI_PA_CONS
		call rsi
	
	;--- Trackpopups ---- MT_WSP
	xor r8,r8
	mov rdx,tMT_WSP
	xor ecx,ecx
	call rsi
	mov [hMT_WSP],rax

		mov rdi,.mp_track
		mov r9,MI_WS_LOAD
		xor r8,r8
		mov rdx,[hMP_WSPACE]
		mov rcx,[hMT_WSP]
		call rdi
		mov r9,MI_SEP
		call rdi
		mov r9,MI_WS_NEW
		call rdi
		mov r9,MI_FI_NEWF
		call rdi
		mov r9,MI_FI_IMP
		call rdi
		mov r9,MI_ED_LNK
		call rdi
		mov r9,MI_SEP
		call rdi
		mov r9,MI_WS_SAVE
		call rdi
		mov r9,MI_SEP
		call rdi
		mov r9,MI_WS_EXIT
		call rdi

	;--- Trackpopups ---- MT_FILE
	xor r8,r8
	mov rdx,tMT_FILE
	xor ecx,ecx
	call rsi
	mov [hMT_FILE],rax

	xor r8,r8
	mov rcx,[hMT_FILE]
	mov rdx,[hMP_WSPACE]

	mov r9,MI_FI_NEWF
	call rdi
	mov r9,MI_FI_IMP
	call rdi
	mov r9,MI_ED_LNK
	call rdi
	mov r9,MI_ED_REMITEM
	call rdi
	mov r9,MI_SEP
	call rdi
	mov rdx,[hMP_EDIT]
	mov r9,MI_FI_SAVE
	call rdi
	mov r9,MI_FI_CLOSE
	call rdi


	;--- Trackpopups ---- MT_SECT
	xor r8,r8
	mov rdx,tMT_SECT
	xor ecx,ecx
	call rsi
	mov [hMT_SECT],rax

	xor r8,r8
	mov rcx,[hMT_SECT]
	mov rdx,[hMP_WSPACE]

	mov r9,MI_FI_NEWF
	call rdi
	mov r9,MI_FI_IMP
	call rdi
	mov r9,MI_ED_LNK
	call rdi
	mov r9,MI_ED_REMITEM
	call rdi


	;---------------------
	mov rdx,[hMnuMain]
	mov rcx,[hMain]
	call apiw.mnu_set
	
	mov rcx,[hMain]
	call apiw.mnu_draw



	pop rsi
	pop rdi
	pop rbx
	ret 0


.mp_track:
	;--- in RCX dest hMenu
	;--- in RDX src hMenu
	;--- in R8 pos
	;--- in R9 src menuid
	push r12
	push r13
	push r14
	push r15

	mov r12,rcx
	mov r13,rdx
	mov r14,r8
	mov r15,r9

	sub rsp,\
		sizea16.MENUITEMINFOW

	mov r9,rsp
	mov [r9+\
		MENUITEMINFOW.fMask],\
		MIIM_TYPE or \
		MIIM_DATA or \
		MIIM_SUBMENU or\
		MIIM_ID or \
		MIIM_STATE or \
		MIIM_CHECKMARKS

	mov rdx,r15
	mov rcx,r13
	call apiw.mni_get_byid
  test eax,eax
	jz .mp_trackE

	mov r9,rsp
	mov rdx,r14
	mov rcx,r12
	call apiw.mni_ins_bypos
  test eax,eax
	jz .mp_trackE

	inc r14


.mp_trackE:
	mov rcx,r12
	mov rdx,r13
	mov r8,r14
	mov r9,r15

	add rsp,\
		sizea16.MENUITEMINFOW
	pop r15
	pop r14
	pop r13
	pop r12
	ret 0
	




.mp_add:
	;--- in RCX hMenuParent/0
	;--- in RDX type/flags/0
	;--- in R8 position

	;--- RET RAX hMenu
	;--- RET RCX hParent
	;--- RET R8 position+1
	push rbx
	push r12
	push r13

	sub rsp,\
		sizea16.MENUITEMINFOW
	mov r12,rcx
	mov r13,r8
	mov rbx,rsp

	;--- ID ---
	mov rax,rdx
	and eax,0FFFFh
	mov [.mii.wID],eax

	;--- ICON ----
	shr rdx,16
	mov eax,edx
	and eax,0FFh	;---> max 255 icons
	;--- field -> MEASUERITEMSTRUCT.itemData
	mov [.mii.dwItemData],rax

	shr rdx,16
	mov eax,edx

	and eax,\
		MFT_STRING\
		or MFT_BITMAP\
		or MFT_MENUBARBREAK\
		or MFT_MENUBREAK\
		or MFT_OWNERDRAW\   
		or MFT_RADIOCHECK\   
		or MFT_SEPARATOR\  
		or MFT_RIGHTORDER\   
		or MFT_RIGHTJUSTIFY
	mov [.mii.fType],eax

	mov eax,edx
	and eax,\
		MFS_DISABLED\
		or MFS_GRAYED\
		or MFS_CHECKED\  
		or MFS_HILITE\ 
		or MFS_DEFAULT  
	mov [.mii.fState],eax

	shr rdx,16
	and edx,\
		MIIM_ID \
		or MIIM_SUBMENU\
		or MIIM_STRING\
		or MIIM_FTYPE\
		or MIIM_STATE\
		or MIIM_CHECKMARKS\
		or MIIM_TYPE\
		or MIIM_DATA\
		or MIIM_BITMAP

	xor eax,eax
	mov [.mii.fMask],edx
	mov [.mii.dwTypeData],rax

	test edx,MIIM_SUBMENU
	jz .mp_addA
	call apiw.mnp_create

.mp_addA:
	mov edx,[.mii.wID]
	mov [.mii.hSubMenu],rax
	test edx,edx
	jz	.mp_addB

	xor r8,r8
	mov rcx,[pLangRes]
	call lang.get_uz

;@break
	add ecx,ecx
	add ecx,ecx
	or ecx,1
	@nearest 16,ecx
	
	call art.a16malloc
	mov [.mii.dwTypeData],rax

	mov edx,[.mii.wID]
	mov r8,rax
	mov rcx,[pLangRes]
	call lang.get_uz

	;--- ITEMDATA
	;---  ID 1 
	;---  LEN 1
	;---  pointer to string 6 bytes
	;--- 0008'01 -------
	;--- xLEN'ID -------
;@break
	shr eax,1
	mov rcx,[.mii.dwItemData]
	mov rdx,[.mii.dwTypeData]
	shl rdx,16
	mov ch,al
	or rcx,rdx
	mov [.mii.dwItemData],rcx

.mp_addB:
	mov r9,rbx
	mov rdx,r13
	mov rcx,r12
	call apiw.mni_ins_bypos

	mov r8,r13
	mov rcx,r12
	mov eax,[.mii.fMask]
	mov r9,[.mii.hSubMenu]
	inc r8
	test eax,\
		MIIM_SUBMENU
	cmovnz rax,r9
	
.mp_addE:	
	add rsp,\
		sizea16.MENUITEMINFOW
	pop r13
	pop r12
	pop rbx
	ret 0



	;#---------------------------------------------------ö
	;|                RESET                              |
	;ö---------------------------------------------------ü

.reset:
	;--- in RCX hMenuPopup
	push rbx
	push rdi

	mov rbx,rcx
	call apiw.get_mnuicount
	test eax,eax
	jz	.resetE
	mov rdi,rax
	jmp	.resetB

.resetA:	
	mov r8,MF_BYPOSITION	
	mov rdx,rdi
	mov rcx,rbx
	call apiw.mnu_del

.resetB:
	dec rdi
	jns .resetA
	
.resetE:	
	pop rdi
	pop rbx
	ret 0

	;#---------------------------------------------------ö
	;|                GET_DATA                           |
	;ö---------------------------------------------------ü

.get_data:
	;--- in RCX hMenu
	;--- in RDX menuid
	;--- ret RAX data
	;--- ret RDX menuid
	push rdx
	sub rsp,\
		sizea16.MENUITEMINFOW
	xor eax,eax
	mov r9,rsp
	mov [r9+\
		MENUITEMINFOW.fMask],\
		MIIM_DATA
	mov [rsp+\
		MENUITEMINFOW.dwItemData],rax
	call apiw.mni_get_byid
  test eax,eax
	jz .get_dataE

	mov rdx,[rsp+\
		MENUITEMINFOW.dwItemData]
	xor eax,eax
	test rdx,rdx
	cmovnz rax,rdx

.get_dataE:
	add rsp,\
		sizea16.MENUITEMINFOW
	pop rdx
	ret 0

	;#---------------------------------------------------ö
	;|                GET_DIR  from MP_PATH              |
	;ö---------------------------------------------------ü

.get_dir:
	;--- ret RAX dir
	;--- ret RDX dir,rdir
	mov edx,MP_PATH
	mov rcx,[hMnuMain]
	call .get_data
	mov rdx,rax
	test eax,eax
	jnz	.get_dirA
	ret 0

.get_dirA:
	test [rax+DIR.type],\
		DIR_HASREF
	cmovnz rax,\
		[rdx+DIR.rdir]
	ret 0

	;#---------------------------------------------------ö
	;|                SET_DIR  on MP_PATH                |
	;ö---------------------------------------------------ü

.set_dir:
	;--- in RCX DIRslot
;@break
	push rbp
	push rbx

	mov rbp,rsp
	and rsp,-16
	mov rbx,rcx

	sub rsp,\
		sizeof.MENUITEMINFOW+\
		FILE_BUFLEN
	mov rbx,rsp
	lea rax,[rsp+\
		sizeof.MENUITEMINFOW]

	mov [.mii.fMask],\
		MIIM_STRING or \
		MIIM_FTYPE or \
		MIIM_DATA

	mov [.mii.fType],\
		MFT_STRING or\
		MFT_RIGHTJUSTIFY

	mov [.mii.dwItemData],rcx
	lea rcx,[rcx+DIR.dir]
	push rax

	push 0
	push uzBlackLxPTri
	push uzSpace
	push uzCPar
	push rcx
	push uzOPar
	push rax
	push 0
	call art.catstrw

	pop [.mii.dwTypeData]
	
	mov r9,rbx
	mov edx,MP_PATH
	mov rcx,[hMnuMain]
	call apiw.mni_set_byid

	mov rcx,[hMain]
	call apiw.mnu_draw

	mov rsp,rbp
	pop rbx
	pop rbp
	ret 0

