  
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

console:
	virtual at rbx
		.cons CONS
	end virtual

	virtual at rdi
		.conf CONFIG
	end virtual

.proc:
@wpro rbp,\
		rbx rsi rdi
;---	cmp edx,WM_NOTIFY
;---	jz	.wm_notify
;---	cmp edx,WM_COMMAND
;---	jz	.wm_command
	cmp edx,\
		WM_INITDIALOG
	jz	.wm_initdialog
	cmp edx,\
		WM_WINDOWPOSCHANGED
	jz	.wm_poschged
;---	cmp edx,WM_DESTROY
;---	jz	.wm_destroy
	jmp	.ret0

;---.wm_destroy:
;---;---	call cmds.discard
;---	jmp	.ret0

.wm_poschged:
	mov rbx,[pCons]
	sub rsp,sizeof.RECT*3

	lea rdi,[rsp+\
		sizeof.RECT*2]
	mov rdx,rdi
	mov rcx,[.hwnd]
	call apiw.get_clirect

	mov esi,[rdi+RECT.right]
	sub esi,[rdi+RECT.left]
	shr esi,4

	mov rdx,rsp
	mov rcx,[.cons.hCbx]
	call apiw.get_winrect

	;--- cbx ---
	mov rax,SWP_NOZORDER
	mov r11d,[rsp+RECT.bottom]
	sub r11d,[rsp+RECT.top]

	mov r10d,[rdi+RECT.right]
	sub r10d,[rdi+RECT.left]

;---	imul r10,rsi,10
;---	sub r10,CX_GAP

	mov r9d,[rdi+RECT.top]
	mov r8d,[rdi+RECT.left]
	mov rdx,HWND_TOP
	mov rcx,[.cons.hCbx]
	call apiw.set_wpos

;---	;--- btn ---
;---	mov rax,SWP_NOZORDER
;---	mov r11d,[rsp+RECT.bottom]
;---	sub r11d,[rsp+RECT.top]
;---	mov r10d,[rdi+RECT.right]
;---	sub r10d,[rdi+RECT.left]
;---	imul r8,rsi,10
;---	sub r10,r8
;---	mov r9d,[rdi+RECT.top]
;---	mov rdx,HWND_TOP
;---	mov rcx,[.cons.hBtn]
;---	call apiw.set_wpos

	;--- sci ----
	mov eax,SWP_NOZORDER or \
		SWP_NOSENDCHANGING or \
		SWP_NOCOPYBITS

	mov r11d,[rdi+RECT.bottom]
	sub r11d,[rdi+RECT.top]
	sub r11d,CY_GAP*2
	mov ecx,[rsp+RECT.bottom]
	sub ecx,[rsp+RECT.top]
	sub r11d,ecx

	mov r10d,[rdi+RECT.right]
	sub r10d,[rdi+RECT.left]

;---	imul r10,rsi,10
;---	sub r10,CX_GAP

	;---	mov r10d,[rdi+RECT.right]
	;---	sub r10d,[rdi+RECT.left]

	mov r9d,[rdi+RECT.top]
	add r9d,[rsp+RECT.bottom]
	sub r9d,[rsp+RECT.top]
	add r9d,CY_GAP

	mov r8d,[rdi+RECT.left]
	mov rdx,HWND_TOP
	mov rcx,[.cons.hSci]
	call apiw.set_wpos

	jmp	.ret1


.wm_initdialog:
	mov rbx,r9
	mov [.cons.hwnd],rcx
	mov rdi,apiw.get_dlgitem
	mov r8,rbx
	call apiw.set_wldata
	mov [.cons.id],CONS_DLG

	mov edx,CONS_CBX
	mov rcx,[.hwnd]
	call rdi
	mov [.cons.hCbx],rax

	mov rcx,rax
	call cbex.get_edit
	mov [.cons.hCbxEdit],rax

	mov rdx,CONS_SCI
	mov rcx,[.hwnd]
	call rdi
	mov [.cons.hSci],rax

;@break
	mov rcx,rax
	call sci.set_defprop

	mov rcx,[.cons.hSci]
	call sci.def_flags

;---	mov r8,SC_CP_UTF8;0
;---	mov rcx,[.cons.hSci]
;---	call sci.set_cp

;---	mov r9,SC_CHARSET_OEM
;---	mov r8d,STYLE_DEFAULT
;---	mov rcx,[.cons.hSci]
;---	call sci.set_charset

	mov rdi,[pConf]
	mov r9d,[.conf.cons.back]
	mov r8,\
		STYLE_DEFAULT
	mov rcx,[.cons.hSci]
	call sci.set_backcolor


.ret1:				;message processed
	xor rax,rax
	inc rax
	jmp	.exit

.ret0:
	xor rax,rax
	jmp	.exit

.exit:
	@wepi

.out:
	;--- in RCX utf16 text
	;--- in RDX flags line
	push rbp
	push rbx
	push rdi
	push rsi
	mov rbp,rsp
	and rsp,-16

	mov rsi,rdx
	mov rbx,[pCons]
	mov rdi,rcx

	call utf16.cpts
	add eax,eax
	add eax,eax
	add eax,6
	@nearest 16,eax
	@frame rax

	mov rcx,rdi
	mov rdx,rsp
	call utf16.to8
	jc .outE
	mov qword[rsp+rax],rsi

	or eax,-1
	mov r9,rax
	mov r8,rax
	mov rcx,[.cons.hSci]
	call sci.set_sel

	mov r9,rsp
	xor r8,r8 
	mov rcx,[.cons.hSci]
	call sci.repl_sel

.outE:
	mov rsp,rbp
	pop rsi
	pop rdi
	pop rbx
	pop rbp
	ret 0

.out8:
	;--- in RCX utf8 text
	;--- in RDX flags line
	push rbx
	push rdx
	push rcx

	or eax,-1
	mov rbx,[pCons]
	mov r9,rax
	mov r8,rax
	mov rcx,[.cons.hSci]
	call sci.set_sel

	pop r9
	xor r8,r8 
	mov rcx,[.cons.hSci]
	call sci.repl_sel

	mov r9,rsp
	xor r8,r8 
	mov rcx,[.cons.hSci]
	cmp r8,[rsp]
	jz .out8E
	call sci.repl_sel

.out8E:
	pop rdx
	pop rbx
	ret 0


