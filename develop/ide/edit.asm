  
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

edit:
	virtual at rbx
		.labf LABFILE
	end virtual

	virtual at rsi
		.pEdit EDIT
	end virtual

	;#---------------------------------------------------ö
	;|             EDIT.open                             |
	;ö---------------------------------------------------ü

.open:
	;--- in RCX labf
	;--- RET EAX = 0 error,labf
	push rbp
	push rbx
	push rdi
	push rsi
	push r12
	push r13
	push r14

	mov rbp,rsp
	and rsp,-16
	xor r12,r12
	xor r13,r13
	xor r14,r14

	sub rsp,\
		FILE_BUFLEN

	xor eax,eax
	test rcx,rcx
	jz	.openE

	mov rdi,rsp
	mov rbx,rcx

	;--- 1) check file existence
	xor eax,eax
	mov r8,[.labf.dir]
	lea rdx,[rbx+\
		sizeof.LABFILE]

	lea rcx,[r8+DIR.dir]
	test [r8+DIR.type],\
		DIR_HASREF
	jz .openA
	mov r8,[r8+DIR.rdir]
	lea rcx,[r8+DIR.dir]

.openA:	
	push rax
	push rdx
	push uzSlash
	push rcx
	push rdi
	push rax
	call art.catstrw	

	mov rcx,rdi
	call art.is_file
	jz .openE

	;--- first check for TEXT extension
	mov rcx,rbx
	add rcx,\
		sizeof.LABFILE
	call ext.load
	mov r14,rax
	test eax,eax
	jnz	.openA1

	mov rcx,rdi
	call ext.fe2hash
	
	mov rcx,rax
	call ext.is_bin
	test eax,eax
	jz .openA1

	mov rcx,rdi
	call .sample_bin
	test eax,eax
	jz .openA1

	or [.labf.type],\
		LF_BIN

	mov rsi,[pEdit]
	mov rcx,[.pEdit.hwnd]
	
	call hex.create
	test eax,eax
	jz	.openE
	mov [.labf.hBin],rax

	mov r9,rdi
	mov r8,HVOF_READONLY
	mov edx,HVM_OPENFILE
	mov rcx,rax
	call apiw.sms
	mov r12,rbx
	jmp	.openB3

.openA1:	
	;--- 2) TODO: check type
	;----TODO: review ---------------
	or [.labf.type],\
		LF_TXT
	;----------------------- 
	mov rsi,[pEdit]
	mov rcx,rdi
	call art.fload

	;--- RET RAX pmem,0,-err
	;--- RET RCX original file size
	;--- RET RDX pextension / flag error

	mov r13,rcx
	mov r12,rax

	test rax,rax
	jnz	.openB

	xor r12,r12
	xor r13,r13
	cmp edx,-3	;--- zero size
	jnz .openE

.openB:
	;--- in RCX labfile
	mov rcx,[.pEdit.hwnd]
	call sci.create
	mov [.labf.hSci],rax

	mov rcx,[.labf.hSci]
	call sci.set_defprop

	;--- TODO: eventual unicode conversion
	;---	mov rcx,rbx
	;---	add rcx,\
	;---		sizeof.LABFILE
	;---	call ext.load
	;---	test eax,eax
	;---	jz	.openB2
	test r14,r14
	jz .openB2

	mov rdx,rbx
	mov rcx,r14
	call ext.apply

.openB2:
	test r12,r12
	jz	.openB1

	mov r9,r12
	mov r8,r13
	mov rcx,[.labf.hSci]
	call sci.add_txt

	mov rcx,r12
	call art.vfree

;---@break
	mov rcx,rbx
	call doc.load_info

.openB1:
	mov rcx,[.labf.hSci]
	call sci.def_flags
	mov r12,rbx

.openB3:
	or [.labf.type],\
		LF_OPENED

.openE:
	xchg rax,r12
	mov rsp,rbp
	pop r14
	pop r13
	pop r12
	pop rsi
	pop rdi
	pop rbx
	pop rbp
	ret 0


	;#---------------------------------------------------ö
	;|             EDIT.sample_bin                       |
	;ö---------------------------------------------------ü
.sample_bin:
	;--- in RCX path+filename	
	;--- RET RAX -1=err, 0=NO-bin 1=bin
	push rbp
	push rbx
	push rsi
	push r12
	push r13
	mov rbp,rsp

	mov rsi,rcx
	and rsp,-16
	mov ecx,1000h ;--- sample size
	sub rsp,rcx
	or r12,-1
	xor r13,r13

	mov rdx,rsp
	call art.zeromem

	mov rcx,rsi
	call art.fopen_r
	test eax,eax
	jz	.sample_binE
	mov rbx,rax

	mov rcx,rax
	call art.fsizex
	test eax,eax
	jz	.sample_binE
	test rcx,rcx
	jz .sample_binF

	sub ecx,1000h
	sbb eax,eax
	and ecx,eax
	add ecx,1000h

	mov r8,rcx
	mov r13,rcx
	mov rdx,rsp
	mov rcx,rbx
	call art.fread
	inc r12
	
	mov rcx,rsp
	mov rdx,r13
	call art.is_bin
	mov r12,rax


.sample_binF:
	mov rcx,rbx
	call art.fclose

.sample_binE:
	mov rax,r12
	mov rsp,rbp
	pop r13
	pop r12
	pop rsi
	pop rbx
	pop rbp
	ret 0

	;#---------------------------------------------------ö
	;|             EDIT.close                            |
	;ö---------------------------------------------------ü

.close:
	;--- in RCX labf
	push rbx
	push rsi

	mov rsi,[pEdit]
	mov rbx,rcx
	mov rdx,\
		[.pEdit.blanks]
	movzx eax,\
		[.labf.type]
	test eax,\
		LF_BLANK
	jz	.closeV

.closeB:
	;--- close a BLANK
	movzx rcx,\
		[.labf.iBlank]
	btr rdx,rcx
	mov [.pEdit.blanks],rdx

.closeV:
	;--- 1) destroy view
	mov rcx,\
		[.labf.hView]
	xor eax,eax
	mov [.labf.hView],rax
	call apiw.destroy

	and [.labf.type],\
		not LF_OPENED

.closeE:
	pop rsi
	pop rbx
	ret 0

	;#---------------------------------------------------ö
	;|             EDIT.new                              |
	;ö---------------------------------------------------ü

.new:
	;--- in RCX 0,labf info
	;--- in RDX type
	;--- RET RAX 0/labf
	xor eax,eax
	test edx,\
		LF_FILE or\
		LF_BLANK
	jnz	.new_btxt
	ret 0

.new_btxt:
	push rbp
	push rbx
	push rdi
	push rsi
	push r12
	mov rbp,rsp

	xor ebx,ebx
	mov rsi,[pEdit]
	xor r12,r12
	xor edi,edi
	test rcx,rcx
	cmovnz rbx,rcx

	xor rax,rax
	mov rcx,[.pEdit.blanks]
	not rcx
	bsf rax,rcx
	mov r12,rax
	jnz	.new_btxtA

	;---TODO: ask to close or save same blanks
	jmp	.new_btxtE

.new_btxtA:
	sub rsp,\
		FILE_BUFLEN

	test ebx,ebx
	mov r9,[projDir]
	jz	.new_btxtB
	mov r9,[.labf.dir]

.new_btxtB:
	mov r8,LF_BLANK\
		or LF_FILE
	xor edx,edx
	lea rcx,[r9+\
		DIR.dir]
	call wspace.new_labf
	test rax,rax
	jz	.new_btxtE
	mov rdi,rax

	or [rax+\
		LABFILE.type],\
		LF_TXT or \
		LF_BLANK or \
		LF_FILE
	
	bts [.pEdit.blanks],r12
	mov [rax+\
		LABFILE.iBlank],r12l

	movzx eax,r12l
	call art.b2a
	lea rdx,[rdi+\
		sizeof.LABFILE]
	mov [rdx],al
	mov [rdx+2],ah

	mov rcx,[.pEdit.hwnd]
	call sci.create
	mov [rdi+\
		LABFILE.hSci],rax

	mov rcx,rax
	call sci.set_defprop

	mov rcx,[rdi+\
		LABFILE.hSci]
	call sci.def_flags

.new_btxtE:
	mov rax,rdi
	mov rsp,rbp
	pop r12
	pop rsi
	pop rdi
	pop rbx
	pop rbp
	ret 0
	
	;#---------------------------------------------------ö
	;|             EDIT.view                             |
	;ö---------------------------------------------------ü

.view:
	;--- in RCX 0, labf to set in view
	;--- RCX = 0 default view
	;--- RET RAX labf
	push rbx
	push rsi

	mov rbx,rcx
	mov rsi,[pEdit]
	
	test rcx,rcx
	cmovz rbx,\
		[.pEdit.deflabf]

	mov rax,[.pEdit.curlabf]
	cmp rax,rbx
	jz	@f

	mov edx,SW_HIDE
	mov rcx,\
		[rax+LABFILE.hView]
	call apiw.show

@@:
	lea r9,[rbx+\
		sizeof.LABFILE]
	mov rax,[.pEdit.pPanel]
	mov rcx,[rax+PNL.hwnd]
	call win.set_text

	mov [.pEdit.curlabf],rbx
	xor r9,r9
	xor r8,r8
	mov rdx,WM_SIZE
	mov rcx,[.pEdit.hwnd]
	call apiw.sms

	mov edx,SW_RESTORE
	mov rcx,[.labf.hView]
	call apiw.show

	mov rax,[.labf.dir]
	xor r8,r8
	lea r9,[rax+DIR.dir]
	mov rcx,[.pEdit.hStb]
	call statb.set_text

	mov r9,RDW_INVALIDATE	\
		or RDW_NOINTERNALPAINT
	xor r8,r8
	mov rax,[.pEdit.pPanel]
	xor edx,edx
	mov rcx,[rax+PNL.hwnd]
	call apiw.redraw_win

;---	xor edx,edx
;---	mov rcx,rbx
;---	call cmds.set

	mov rax,rbx
	pop rsi
	pop rbx
	ret 0

	;#---------------------------------------------------ö
	;|             EDIT.proc                             |
	;ö---------------------------------------------------ü

.proc:
@wpro rbp,\
		rbx rsi rdi

	cmp edx,WM_INITDIALOG
	jz	.wm_initdialog
	cmp edx,WM_SIZE
	jz	.wm_size
	cmp edx,WM_NOTIFY
	jz	.wm_notify
	;---	cmp edx,WM_COMMAND
	;---	jz	.wm_command
	jmp	.ret0

	;---.wm_command:
	;---	shr r8,16
	;---	cmp r8,SCEN_SETFOCUS
	;---	jnz	.ret0
	;---;	@break
	;---	mov rsi,[pEdit]
	;---	mov rbx,[.pEdit.curlabf]
	;---	mov rcx,[.labf.hView]
	;---	call apiw.active
	;---	jmp	.ret0

.wm_notify:
	xor edx,edx
	mov rsi,[pEdit]
	mov rbx,[.pEdit.curlabf]
	cmp	rdx,[.pEdit.deflabf]
	jz	.ret0
	cmp	rbx,rdx
	jz	.ret0
	test rbx,rbx
	jz	.ret0

	mov rax,[r9+\
		NMHDR.hwndFrom]
	cmp rax,[.pEdit.hStb]
	jz	.wm_notifyS
	cmp rax,[.labf.hView]
	jnz	.ret0
	test [.labf.type],\
		LF_TXT
	jz	.ret0

.wm_notifyT:
	;--- view is text ---------
	mov edx,[r9+\
		NMHDR.code]
	cmp edx,\
		SCN_MARGINCLICK
	jz	.wm_notifyM

	cmp edx,\
		SCN_MODIFIED
	jnz	.wm_notifyT2
	test [r9+\
		SCNOTIF.modificationType],\
	SC_MOD_INSERTTEXT
	jnz	.wm_notifyT3

	test [r9+\
		SCNOTIF.modificationType],\
	SC_MOD_DELETETEXT
	jnz	.wm_notifyT3
	jmp	.ret0

.wm_notifyT3:
	mov rsi,r9
	mov r8d,[r9+\
		SCNOTIF.position]
	mov rcx,[.labf.hSci]
	call sci.linefrompos

	mov rcx,rbx
	mov rdx,rax
	mov r8d,[rsi+\
		SCNOTIF.linesAdded]
	test ecx,ecx
	jz	.ret0
	call doc.update_bm
;---	or [.labf.info],LF_BM
	jmp	.ret1

.wm_notifyT2:
	cmp edx,\
		SCN_SAVEPOINTREACHED
	jnz	.wm_notifyT1

	and [.labf.type],\
		not LF_MODIF
	jmp	.ret1

.wm_notifyT1:
	cmp edx,\
		SCN_SAVEPOINTLEFT
	jnz	.ret0
	or [.labf.type],\
		LF_MODIF
	jmp	.ret1

.wm_notifyM:
	mov eax,[r9+SCNOTIF.line]
	mov eax,[r9+\
		SCNOTIF.margin]
	test eax,eax
	jnz	.ret1

	;---push r9
	;---	mov r8,1
	;---	mov rcx,[.labf.hSci]
	;---	call apiw.active
	;---;	call apiw.set_focus
	;---pop r9

	mov r8d,[r9+\
		SCNOTIF.position]
	mov rcx,[.labf.hSci]
	call sci.linefrompos
	mov rdi,rax

	mov rdx,rax
	mov rcx,rbx
	call doc.toggle_bm
	or [.labf.info],LF_BM

	;---	mov r8,1
	;---	mov rcx,[.labf.hSci]
	;---	call sci.set_focus
	jmp	.ret1

	;#---------------------------------------------------ö
	;|             STAT_NOTIFY                           |
	;ö---------------------------------------------------ü

.wm_notifyS:
	mov edx,[r9+\
		NMHDR.code]
	cmp edx,NM_CLICK
	jz	.wm_notifyS1
	jmp	.ret0

.wm_notifyS1:
	sub rsp,\
		FILE_BUFLEN
	mov r9,rsp	
	xor r8,r8
	mov rcx,[.pEdit.hStb]
	call statb.get_text

	mov rcx,rsp
	call art.is_file
	jz	.ret0

	mov rcx,rsp
	call wspace.dir2hash
	jnc	.ret0

	mov rcx,rax
	call mnu.set_dir
	jmp	.ret0
	
	;#---------------------------------------------------ö
	;|             EDIT.wm_size                          |
	;ö---------------------------------------------------ü

.wm_size:
;@break
	mov rsi,[pEdit]
	sub rsp,\
		sizeof.RECT*2
	;--- rsp clirect
	;--- rsp+16 status
	;--- rsp+32 tab
	;--- rsp+48 xcb
	mov rdi,rsp
	.cli_rc equ rdi
	.stb_rc equ rdi+16

	mov rdx,rsp
	mov rcx,[.hwnd]
	call apiw.get_clirect

	lea rdx,[.stb_rc]
	mov rcx,[.pEdit.hStb]
	call apiw.get_winrect

	;--- view handle
	mov eax,SWP_NOZORDER
	mov r11d,[.cli_rc+\
		RECT.bottom]
	mov ecx,[.stb_rc+\
		RECT.bottom]
	sub ecx,[.stb_rc+\
		RECT.top]
	sub r11d,ecx
	mov r10d,[.cli_rc+\
		RECT.right]

	xor r9,r9
	xor r8,r8
	mov rdx,[.pEdit.curlabf]
	mov rcx,[rdx+\
		LABFILE.hView]
	mov rdx,HWND_TOP
	call apiw.set_wpos

	;--- status bar
	mov eax,SWP_NOZORDER \
		or SWP_NOSENDCHANGING \
		or SWP_NOCOPYBITS \
		or SWP_NOMOVE
	mov rdx,HWND_TOP
	mov rcx,[.pEdit.hStb]
	call apiw.set_wpos
	jmp	.ret0

	;#---------------------------------------------------ö
	;|             EDIT.initdialog                       |
	;ö---------------------------------------------------ü

.wm_initdialog:
	mov rsi,[pEdit]
	mov [.pEdit.hwnd],rcx
	mov rbx,rcx
	mov rdi,apiw.get_dlgitem
	
;	mov r8,uzCourierN
;	mov r9,FIXED_PITCH
;	xor edx,edx
;	mov ecx,0A10h
;	call apiw.cfonti
;	mov [.pEdit.hFont],rax

;	mov r9,TRUE
;	mov r8,rax
;	mov rdx,WM_SETFONT
;	mov rcx,rbx
;	call apiw.sms

	xor r8,r8
	call wspace.new_labf
	mov rbx,rax

	mov [.pEdit.curlabf],rax
	mov [.pEdit.deflabf],rax

	mov rdx,EDIT_STC
	mov rcx,[.pEdit.hwnd]
	call rdi
	mov [.labf.hView],rax

	mov rdx,EDIT_STB
	mov rcx,[.pEdit.hwnd]
	call rdi
	mov [.pEdit.hStb],rax

;	mov rcx,[.pEdit.hwnd]
;	call apiw.get_dc
;	mov rdi,rax

;	mov rdx,[.pEdit.hFont]
;	mov rcx,rax
;	call apiw.selobj
;	mov rbx,rax

;	sub rsp,\
;		sizea16.TEXTMETRIC
;	mov rdx,rsp
;	mov rcx,rdi
;	call apiw.get_txtmetr

;	mov eax,[rsp+\
;		TEXTMETRIC.tmHeight]
;	mov [.pEdit.cy_font],ax

;	mov eax,[rsp+\
;		TEXTMETRIC.tmMaxCharWidth]
;	mov [.pEdit.cx_font],ax

;	mov rdx,[.pEdit.hwnd]
;	mov rcx,rdi
;	call apiw.selobj

;	mov rdx,rdi
;	mov rcx,[.pEdit.hwnd]
;	call apiw.rel_dc

;	mov rcx,rdi
;	call sci.get_docp
;	mov [.labf.doc],rax

.ret1:				;message processed
	xor rax,rax
	inc rax
	jmp	.exit

.ret0:
	xor rax,rax
	jmp	.exit

.exit:
	@wepi
