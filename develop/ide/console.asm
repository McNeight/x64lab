  
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
;---	cmp edx,WM_COMMAND
;---	jz	.wm_command
;---	cmp edx,WM_NOTIFY
;---	jz	.wm_notify
	cmp edx,\
		WM_INITDIALOG
	jz	.wm_initdialog
	cmp edx,\
		WM_WINDOWPOSCHANGED
	jz	.wm_poschged
	jmp	.ret0

;---.wm_command:
;---	mov rbx,[pCons]
;---	cmp r9,[.cons.hCbxEdit]
;---	jnz	.ret0
;---	shr r8,16
;---	cmp r8,CBN_SETFOCUS
;---	jnz	.ret0
;---@break

;---	jmp	.ret0


;---.wm_notify:
;---	mov rbx,[pCons]
;---	mov rax,[r9+\
;---		NMHDR.hwndFrom]
;---	cmp rax,[.cons.hCbx]
;---	jnz	.ret0

;---	mov edx,[r9+\
;---		NMHDR.code]
;---	cmp edx,\
;---		NM_KILLFOCUS
;---	jz	.cbex_killfoc
;---	cmp edx,\
;---		NM_SETFOCUS
;---	jz	.cbex_setfoc
;---	jmp	.ret0

.wm_poschged:
	mov rbx,[pCons]
	sub rsp,sizeof.RECT*3
	lea rdi,[rsp+\
		sizeof.RECT*2]
	mov rdx,rdi
	mov rcx,[.hwnd]
	call apiw.get_clirect

	mov rdx,rsp
	mov rcx,[.cons.hCbx]
	call apiw.get_winrect

	mov rax,SWP_NOZORDER
	mov r11d,[rsp+RECT.bottom]
	sub r11d,[rsp+RECT.top]
	mov r10d,[rdi+RECT.right]
	sub r10d,[rdi+RECT.left]
	mov r9d,[rdi+RECT.top]
	mov r8d,[rdi+RECT.left]
	mov rdx,HWND_TOP
	mov rcx,[.cons.hCbx]
	call apiw.set_wpos

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

	mov rdx,CONS_CBX
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

	mov rdi,[pConf]
	mov r9d,[.conf.cons.back]
	mov r8,\
		STYLE_DEFAULT
	mov rcx,[.cons.hSci]
	call sci.set_backcolor

	mov r8,cbxedit.proc
	mov rcx,[.cons.hCbxEdit]
	call apiw.set_wlproc
	mov [.cons.pCbexEOld],rax

;---	call _edit.get_caretsize
	

.ret1:				;message processed
	xor rax,rax
	inc rax
	jmp	.exit

.ret0:
	xor rax,rax
	jmp	.exit

.exit:
	@wepi



	;#---------------------------------------------------ö
	;|      subclassed EDIT window of the ComboBoxEx     |
	;ö---------------------------------------------------ü

cbxedit:
	virtual at rbx
		.cons CONS
	end virtual

	virtual at rdi
		.conf CONFIG
	end virtual
	
.proc:
@wpro rbp,\
		rbx rsi rdi

	mov rdx,[.msg]
	cmp edx,WM_DESTROY
	jz	.wm_destroy
;---	cmp edx,WM_SETFOCUS
;---	jz	.wm_setfoc
;---	cmp edx,WM_KILLFOCUS
;---	jz	.wm_killfoc
	jmp	.cwproc

;---.wm_killfoc:
;---;@break
;---	mov rcx,[.hwnd]
;---  call apiw.hide_caret

;---	mov rcx,[.hwnd]
;---	call apiw.destr_caret
;---	jmp	.ret0

;---.wm_setfoc:
;---;@break
;---	mov rbx,[pCons]
;---	movzx r9,\
;---		[.cons.cyCaret]
;---	movzx r8,\
;---		[.cons.cxCaret]
;---	xor edx,edx
;---	mov rcx,[.hwnd]
;---	call apiw.create_caret

;---	mov rcx,[.hwnd]
;---  call apiw.show_caret
;---	jmp	.ret0



.wm_destroy:
	mov rbx,[pCons]
	mov r8,[.cons.pCbexEOld]
	mov rcx,[.hwnd]
	call apiw.set_wlproc
	jmp	.ret0

.ret1:				;message processed
	xor rax,rax
	inc rax
	jmp	.exit

.ret0:
	xor rax,rax
	jmp	.exit

.cwproc:
	sub rsp,30h
	mov rax,[.lparam]
	mov rbx,[pCons]
	mov [rsp+20h],rax
	mov r9,[.wparam]
	mov r8,[.msg]
	mov rdx,[.hwnd]
	mov rcx,[.cons.pCbexEOld]
	call [CallWindowProcW]
	
.exit:
	@wepi



;---.get_caretsize:
;---	push rbx
;---	push rdi
;---	push r12
;---	push r13

;---	mov rbx,[pCons]
;---	sub rsp,\
;---		sizea16.TEXTMETRIC
;---	mov r12,rsp

;---	mov rcx,[.cons.hCbxEdit]
;---	call apiw.get_dc
;---	mov r13,rax

;---	mov rdx,r12
;---	mov rcx,rax
;---	call apiw.get_txtmetr

;---	mov eax,[r12+\
;---		TEXTMETRIC.tmAveCharWidth]
;---	mov [.cons.cxCaret],al
;---	mov eax,[r12+\
;---		TEXTMETRIC.tmHeight]
;---	mov [.cons.cyCaret],al

;---	mov rdx,r13
;---	mov rcx,[.cons.hCbxEdit]
;---	call apiw.rel_dc

;---	add rsp,\
;---		sizea16.TEXTMETRIC

;---	pop r13
;---	pop r12
;---	pop rdi
;---	pop rbx
;---	ret 0
