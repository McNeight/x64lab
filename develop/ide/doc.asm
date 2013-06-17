  
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

doc:
	virtual at rbx
		.doc DOCDLG
	end virtual

	virtual at rbx
		.labf LABFILE
	end virtual

	virtual at rdi
		.conf CONFIG
	end virtual

	virtual at rsi
		.lvc	LVCOLUMNW
	end virtual


	;#---------------------------------------------------ö
	;|                  LOAD_INFO                        |
	;ö---------------------------------------------------ü
.load_info:
	;--- in RCX labfile
	push rbp
	push rbx
	push rdi
	push rsi
	push r12

	mov rbp,rsp
	and rsp,-16
	sub rsp,128
	mov rbx,rcx
	xor r12,r12

	mov rdx,rsp
	mov rcx,rbx
	call .frm_tmpname

;@break
	and [rbx+\
		LABFILE.info],not LF_BM

	mov rcx,rsp
	call [top64.parse]
	test rax,rax
	jz	.load_infoE

	or [rbx+\
		LABFILE.info],LF_BM

	mov r12,rax
	mov rsi,rax

.load_infoA:
	mov eax,[rsi+\
		TITEM.value]
	cmp eax,"bm"
	jnz	.load_infoN

	
.load_bm:
	;--- first dword is the visible line
	mov edi,[rsi+\
		TITEM.attrib]
	add rdi,r12
	cmp rdi,r12
	jz	.load_infoN

	cmp [rdi+\
		TITEM.type],TNUMBER
	jnz	.load_infoN

	mov r8d,[rdi+\
		TITEM.lo_dword]

	sub r8,1	;--- ?? patch for strange behaviour: first is 0 !!
	jc .load_bmA

	mov rcx,[rbx+\
		LABFILE.hSci]
	call sci.goto_line

.load_bmA:
	;--- bookmark --------
	mov edi,[rdi+\
		TITEM.attrib]
	add rdi,r12
	cmp rdi,r12
	jz	.load_infoN

	cmp [rdi+\
		TITEM.type],TNUMBER
	jnz	.load_bmA

	mov r8d,[rdi+\
		TITEM.lo_dword]

	mov r9,SC_MARK_CIRCLE
	mov rcx,[rbx+\
		LABFILE.hSci]
	call sci.mark_add
	
	;---	mov edx,[rdi+\
	;---		TITEM.lo_dword]
	;---	mov rcx,rbx
	;---	call .ins_bm

	jmp	.load_bmA
		

.load_infoN:
	mov esi,[rsi+\
		TITEM.next]
	add rsi,r12
	cmp rsi,r12
	jnz	.load_infoA


.load_infoF:
	mov rcx,r12
	call [top64.free]

.load_infoE:
	mov rsp,rbp
	pop r12
	pop rsi
	pop rdi
	pop rbx
	pop rbp
	ret 0

	;#---------------------------------------------------ö
	;|                  SAVE_INFO                        |
	;ö---------------------------------------------------ü
.save_info:
	;--- in RCX labfile
	push rbp
	push rbx
	push rdi
	push rsi
	push r12

	mov rbp,rsp
	and rsp,-16
	sub rsp,128
	xor r12,r12

	mov rbx,rcx
	movzx esi,[rbx+\
		LABFILE.info]
	test esi,esi
	jz	.save_infoE

	test esi,LF_BM
	jz .save_infoE
	;--- create file ---

	mov rdx,rsp
	mov rcx,rbx
	call .frm_tmpname

	mov word[rsp+40],0
	
	mov rcx,rsp
	call art.is_file
	jnz .save_infoA
	;--- tmp\2FB2E186A3BD708D\DECC015175AFCD99.utf8

	mov rcx,rsp
	call apiw.createdir

.save_infoA:
	mov word[rsp+40],"\"

	mov rcx,rsp
	call art.fcreate_rw
	test rax,rax
	jle	.save_infoE
	mov r12,rax				;--- file handle

	sub rsp,1024
	mov rdi,rsp
	call wspace.frm_head

	mov r8,rdi
	sub r8,rsp
	mov rdx,rsp
	mov rcx,r12
	call art.fwrite

	;---	and esi,not LF_BM
	mov rdx,r12
	mov rcx,rbx
	call .save_bm

	mov rcx,r12
	call art.fclose

.save_infoE:
	mov rsp,rbp
	pop r12
	pop rsi
	pop rdi
	pop rbx
	pop rbp
	ret 0

	;#---------------------------------------------------ö
	;|                  FRM_TMPNAME                      |
	;ö---------------------------------------------------ü

.frm_tmpname:
	;--- in RCX labfile
	;--- in RDX buffer
	;--- tmp\2FB2E186A3BD708D.DECC015175AFCD99.utf8
	;--- tmp\  hash real dir .  hash filename .utf8
	push rbp
	push rbx
	push rdi

	mov rbp,rsp
	and rsp,-16
	sub rsp,32

	mov rbx,rcx
	mov rdi,rdx

	mov rax,[rbx+\
		LABFILE.dir]
	mov rdx,rax
	test [rax+DIR.type],\
		DIR_HASREF
	cmovnz rax,\
		[rdx+DIR.rdir]

	mov rcx,[rax+\
		DIR.hash]
	
	mov rax,\
		qword[uzTmpName]
	stosq
	sub edi,2
	mov eax,"\"
	stosw

	mov rdx,rsp
	call art.qword2a

	mov rdx,rdi
	mov rcx,rsp
	call art.qa2qu
	add rdi,32

	mov eax,"\"
	stosw

	lea rcx,[rbx+\
		sizeof.LABFILE]
	call utf16.zsdbm

	mov rdx,rsp
	mov rcx,rax
	call art.qword2a

	mov rcx,rsp
	mov rdx,rdi
	call art.qa2qu

	add rdi,32
	mov rax,qword[uzUtf8Ext]
	stosq
	mov al,"8"
	stosw
	xor eax,eax
	stosd

	mov rsp,rbp
	pop rdi
	pop rbx
	pop rbp
	ret 0

	;#---------------------------------------------------ö
	;|                  SAVE_BM                          |
	;ö---------------------------------------------------ü

.save_bm:
	;--- in RCX labfile
	;--- in RDX hFile
	push rbp
	push rbx
	push rdi
	push rsi
	push r12
	push r13

	mov rbp,rsp
	and rsp,-16
	sub rsp,32
	mov rsi,rsp

	mov rbx,rcx
	mov r13,rdx

	mov rdi,[rbx+\
		LABFILE.hSci]
	
	mov rcx,rdi
	call sci.get_firstvisline
	sub rsp,8
	mov [rsp],rax
	mov r12,rsp		;--- point to data
	xor rax,rax

.save_bmA:
	mov r9,\
		1 shl SC_MARK_CIRCLE
	mov r8,rax
	mov rcx,rdi
	call sci.mark_next
	push rax
	inc eax
	jnz .save_bmA

	mov rcx,rsp
	sub rcx,r12
	neg rcx
	and ecx,7FFFFh	;--- limit size 0FFFF bm * 8 num bmarks
	shl ecx,1				;--- 1 bm min 16 byte text
	add ecx,128			;--- stub
	@frame rcx

	mov rdi,rax
	mov al,09h
	stosb
	mov eax,'bm'
	stosw
	mov al,":"

.save_bmB:
	stosb
	mov al,"\"
	stosb
	@do_eol
	mov ax,0909h
	stosw
	mov al,"0"
	stosb
	
	mov rdx,rsi
	mov rcx,[r12]
	call art.qword2a

	mov r8,rsi
	add rsi,rdx
	mov ecx,eax
	rep movsb
	mov rsi,r8
	mov al,"h"
	stosb
	mov al,","
	sub r12,8
	mov rdx,[r12]
	inc rdx
	jnz	.save_bmB

	@do_eol

	mov r8,rdi
	sub r8,rsp

	mov rdx,rsp
	mov rcx,r13
	call art.fwrite

.save_bmE:
	mov rsp,rbp
	pop r13
	pop r12
	pop rsi
	pop rdi
	pop rbx
	pop rbp
	ret 0

   ;ü------------------------------------------ö
   ;|   update_BM                              |
   ;#------------------------------------------ä

.update_bm:
	;--- in RCX labfile
	;--- in RDX current line
	;--- in R8 +- lines
	push rbx
	push rdi
	push rsi
	push r12
	
	mov rbx,rcx
	mov rdi,rdx
	mov rsi,r8

	mov rax,[pDoc]
	mov r12,[rax+\
		DOCDLG.hLvwB]

	jmp	.update_bmA
	
.update_bmB:
	mov rdx,rdi
	mov rcx,r12
	call lvw.is_param
	test eax,eax
	jz .update_bmE

	sub rsp,\
		sizeof.LVITEMW
	mov r9,rsp
	mov [r9+\
		LVITEMW.mask],\
		LVIF_PARAM
	mov [r9+\
		LVITEMW.iItem],edx
	add rax,rsi
	inc rax
	mov [r9+\
		LVITEMW.lParam],rax
	xor edx,edx
	mov [r9+\
		LVITEMW.iSubItem],edx
	mov rcx,r12
	call lvw.set_item
	add rsp,\
		sizeof.LVITEMW
	inc rdi
	
.update_bmA:
	mov r9,\
		1 shl SC_MARK_CIRCLE
	mov r8,rdi
	mov rcx,[.labf.hSci]
	call sci.mark_next
	mov rdi,rax
	inc eax
	jnz .update_bmB

.update_bmE:
	mov rcx,rbx
	call .list_bm

	pop r12
	pop rsi
	pop rdi
	pop rbx
	ret 0

   ;ü------------------------------------------ö
   ;|   LIST_BM                                |
   ;#------------------------------------------ä

.list_bm:
	;--- in RCX labfile
	push rbx
	push rdi
	push r12

	mov rbx,rcx
	mov rax,[pDoc]
	mov r12,[rax+\
		DOCDLG.hLvwB]

	xor r9,r9
	mov r8,FALSE
	mov rdx,WM_SETREDRAW
	mov rcx,r12
	call apiw.sms

	mov rcx,r12
	call lvw.del_all

	test [.labf.type],\
		LF_TXT
	jz .list_bmE
	
	xor edi,edi
	jmp	.list_bmB

.list_bmA:
	mov rdx,rdi
	mov rcx,rbx
	call .ins_bm
	inc rdi

.list_bmB:
	mov r9,\
		1 shl SC_MARK_CIRCLE
	mov r8,rdi
	mov rcx,[.labf.hSci]
	call sci.mark_next
	mov rdi,rax
	inc eax
	jnz .list_bmA

.list_bmE:
	xor r9,r9
	mov r8,TRUE
	mov rdx,WM_SETREDRAW
	mov rcx,r12
	call apiw.sms

	;---	mov r8,TRUE
	;---	xor edx,edx
	;---	mov rcx,r12
	;---	call apiw.invrect

	pop r12
	pop rdi
	pop rbx
	ret 0


.toggle_bm:
	;--- in RCX labfile
	;--- in RDX line
	push rbx
	push rdi
	push rsi
	push r12
	push r13

	sub rsp,\
		sizeof.LVITEMW+\
		FILE_BUFLEN

	mov r13,[pDoc]
	mov rbx,rcx
	mov r12,rdx

	mov r8,rdx
	mov rcx,[.labf.hSci]
	call sci.mark_get
	
	mov rsi,sci.mark_add
	mov rdx,sci.mark_del

	test eax,\
		1 shl SC_MARK_CIRCLE
	cmovnz rsi,rdx
	
	mov r9,SC_MARK_CIRCLE
	mov r8,r12
	mov rcx,[.labf.hSci]
	call rsi

	cmp rsi,sci.mark_add
	jz	.toggle_bmA

.toggle_bmD:
	mov rdx,r12
	inc rdx
	mov rcx,[r13+\
		DOCDLG.hLvwB]
	call lvw.is_param
	test eax,eax
	jz .toggle_bmE

	mov r8,rdx
	mov rcx,[r13+\
		DOCDLG.hLvwB]
	call lvw.del_item
	jmp	.toggle_bmE

.toggle_bmA:
	mov rdx,r12
	mov rcx,rbx
	call .ins_bm

.toggle_bmE:
	add rsp,\
		sizeof.LVITEMW+\
		FILE_BUFLEN
	pop r13
	pop r12
	pop rsi
	pop rdi
	pop rbx
	ret 0

.ins_bm:
	;--- only in the listview
	;--- in RCX labfile
	;--- in RDX line
	push rbp
	push rbx
	push rdi
	push rsi
	push r12
	push r13
	push r14
	mov rbp,rsp

	and rsp,-16
	sub rsp,\
		sizea16.LVITEMW+\	;--- larger than TEXTRANGEW
		512+512	;--- max buffer

	mov rsi,rsp
	mov rbx,rcx
	mov r12,rdx
	mov r13,[pDoc]

	lea rdi,[rsp+\
		sizea16.LVITEMW]
	mov eax,"["
	stosw

	mov rdx,rsi
	mov rcx,r12
	inc rcx
	call art.dd2u

	mov rsi,rax
	rep movsb
	mov eax,"]"
	stosw
	mov eax," "
	stosw

	mov r8,r12
	mov rcx,[.labf.hSci]
	call sci.posfromline
	mov rsi,rax

	mov r8,r12
	mov rcx,[.labf.hSci]
	call sci.get_lineendpos

	mov r8,rsi
	mov r9,rax

	add rsi,128
	@min rax,rsi
	mov r9,rax

	mov rsi,rsp
	lea r14,[rsp+\
		sizea16.LVITEMW+512]
	mov [rsi+\
		TEXTRANGEW.chrg.cpMin],r8d
	mov [rsi+\
		TEXTRANGEW.chrg.cpMax],r9d
	mov [rsi+\
		TEXTRANGEW.lpstrText],r14

	mov r9,rsi
	mov rcx,[.labf.hSci]
	call sci.get_txtr

	mov rdx,rdi
	mov rcx,r14
	call utf8.to16

	;---	test rax,rax
	;---	jz	.saveE

	lea rdi,[rsp+\
		sizea16.LVITEMW]

	mov rcx,[r13+\
		DOCDLG.hLvwB]
	call lvw.get_count
	
	mov r9,rsi
	xor edx,edx
	mov [r9+\
		LVITEMW.mask],\
		LVIF_PARAM or \
		LVIF_TEXT
	mov [r9+\
		LVITEMW.iItem],eax
	inc r12
	mov [r9+\
		LVITEMW.lParam],r12
	mov [r9+\
		LVITEMW.iSubItem],edx
	mov [r9+\
		LVITEMW.pszText],rdi

	mov rcx,[r13+\
		DOCDLG.hLvwB]
	call lvw.ins_item

	mov rsp,rbp
	pop r14
	pop r13
	pop r12
	pop rsi
	pop rdi
	pop rbx
	pop rbp
	ret 0

	
   ;ü------------------------------------------ö
   ;|   SETUP GUI                              |
   ;#------------------------------------------ä

.setup:
	push rbx
	push rdi
	push rsi

	sub rsp,\
		sizeof.LVCOLUMNW

	mov rsi,rsp
	mov rdi,[pConf]
	mov rbx,[pDoc]

	mov r9d,[.conf.docs.bkcol]
	mov rcx,[.doc.hLvwA]
	call lvw.set_bkcol

	mov r9d,[.conf.docs.bkcol]
	mov rcx,[.doc.hLvwA]
	call lvw.set_txtbkcol

	mov r9d,00ECEDFEh
	mov rcx,[.doc.hLvwB]
	call lvw.set_bkcol

	mov r9d,00ECEDFEh
	mov rcx,[.doc.hLvwB]
	call lvw.set_txtbkcol

	mov r9,\
		LVS_EX_CHECKBOXES or\
		LVS_EX_FULLROWSELECT or \
		LVS_EX_AUTOSIZECOLUMNS or \
		LVS_EX_INFOTIP
	;---LVS_EX_JUSTIFYCOLUMNS ; or \
	;---LVS_EX_AUTOSIZECOLUMNS ;or \
	;---LVS_EX_GRIDLINES or \
	;---LVS_EX_FLATSB; or \

	xor r8,r8
	mov rcx,[.doc.hLvwA]
	call lvw.set_xstyle

	mov r9,[hsmSysList]
	mov r8,LVSIL_SMALL
	mov rcx,[.doc.hLvwA]
	call lvw.set_iml

	;---	lea rsi,[rsp+\
	;---		sizea16.LVCOLUMNW]

	;---;	push 0
	;---;	push 3
	;---;	push UZ_INFO_CDATE
	;---;	push 2
	;---;	push UZ_INFO_SIZE
	;---;	push 1
	;---;	push UZ_INFO_TYPE
	;---;	push 0
	;---;	push UZ_INFO_BUF

	;---;.setupB:
	;---;	pop rcx
	;---;	test rcx,rcx
	;---;	jz	.setupE

	;---.setupA:
	;---	mov r8,rsi
	;---	mov edx,U16
	;---	mov ecx,UZ_INFO_BUF
	;---	call [lang.get_uz]

	mov [.lvc.mask],\
		LVCF_IDEALWIDTH or \
		LVCF_WIDTH

	mov [.lvc.cx],600
	mov [.lvc.cxIdeal],100

	;---	LVCF_FMT or \
	;---	mov [.lvc.fmt],LVCFMT_LEFT
	;---	LVCF_TEXT or \
	;---	mov [.lvc.pszText],uzDefault;0;rsi
	;---	mov [.lvc.cchTextMax],-1
	;---	LVCF_SUBITEM
	;---	pop rax

	xor eax,eax
	;---	mov [.lvc.iSubItem],eax
	mov r9,rsi
	mov r8,rax
	mov rcx,[.doc.hLvwA]
	call lvw.ins_col

	mov r9,\
		LVS_EX_FULLROWSELECT or \
		LVS_EX_AUTOSIZECOLUMNS or \
		LVS_EX_DOUBLEBUFFER
	xor r8,r8
	mov rcx,[.doc.hLvwB]
	call lvw.set_xstyle

	mov [.lvc.mask],\
		LVCF_IDEALWIDTH or \
		LVCF_WIDTH
	mov [.lvc.cx],600
	mov [.lvc.cxIdeal],100
	xor eax,eax
	mov r9,rsi
	mov r8,rax
	mov rcx,[.doc.hLvwB]
	call lvw.ins_col

	add rsp,\
		sizeof.LVCOLUMNW
	pop rsi
	pop rdi
	pop rbx
	ret 0

   ;ü------------------------------------------ö
   ;|   .PROC                                  |
   ;#------------------------------------------ä

.proc:
@wpro rbp,\
		rbx rsi rdi

	cmp edx,\
		WM_INITDIALOG
	jz	.wm_initdialog
	cmp edx,\
		WM_WINDOWPOSCHANGED
	jz	.wm_poschged
	cmp edx,WM_NOTIFY
	jz	.wm_notify
	jmp	.ret0

	;#---------------------------------------------------ö
	;|      WM_NOTIFY                                    |
	;ö---------------------------------------------------ü

.wm_notify:
	mov rbx,[pDoc]
	mov rdx,[r9+NMHDR.hwndFrom]
	cmp rdx,[.doc.hLvwA]
	jz	.wm_notifyA
	cmp rdx,[.doc.hLvwB]
	jz	.wm_notifyB
	cmp rdx,[hTip]
	jz	.tip_notify
	jmp	.ret0

.tip_notify:
	mov rax,[r9+\
		NMHDR.idFrom]
	cmp rax,[.doc.hLvwA]
	jnz	.ret0

	mov edx,[r9+\
		NMHDR.code]
	cmp edx,\
		TTN_GETDISPINFOW
	jnz	.ret0

	mov rsi,r9
	mov rcx,[.doc.hLvwA]
	call lvw.gethit

;@break	
	xor eax,eax
	mov [rsi+\
		NMTTDISPINFO.lpszText],rax

	test edx,edx
	jz	.ret0

	mov rax,[rdx+\
		LABFILE.pOmni]
	test eax,eax
	jz	.ret0

	lea rdx,[rax+\
		sizeof.OMNI]
	mov [rsi+\
		NMTTDISPINFO.lpszText],rdx
	jmp	.ret0

.wm_notifyB:
	mov edx,[r9+NMHDR.code]
	cmp edx,\
		LVN_ITEMCHANGING
	jz	.notify_schgedB
	jmp	.ret0

.notify_schgedB:
	mov r8,\
		[r9+NM_LISTVIEW.lParam]
	test r8,r8
	jz	.ret0
	dec r8

	test [r9+\
		NM_LISTVIEW.uNewState],\
		LVIS_SELECTED ;or 		LVIS_FOCUSED 
	jz	.ret0

	mov rsi,[pEdit]
	mov rdi,[rsi+\
		EDIT.curlabf]
	test [rdi+LABFILE.type],\
		LF_TXT
	jz	.ret0

	;---	push r8
	;---	mov r8,1
	;---	mov rcx,[rdi+\
	;---		LABFILE.hSci]
	;---	call sci.set_focus
	;---	pop r8
	push r12
	push r13
	mov r12,r8

;@break

	mov rcx,[rdi+\
		LABFILE.hSci]
	call sci.screenlines
	shr eax,1
	mov r13,rax

	mov r8,r12
	mov rcx,[rdi+\
		LABFILE.hSci]
	call sci.goto_line

	mov rcx,[rdi+\
		LABFILE.hSci]
	call sci.get_firstvisline
	add r13,rax

;---	mov r8,r13
;---	mov rcx,[rdi+\
;---		LABFILE.hSci]
;---	call sci.goto_line

	sub r12,r13
	mov r9d,r12d
	xor r8,r8
	mov rcx,[rdi+\
		LABFILE.hSci]
	call sci.linescroll

	pop r13
	pop r12
	jmp	.ret1

.wm_notifyA:
	mov edx,[r9+NMHDR.code]
	cmp edx,\
		LVN_ITEMCHANGING
	jz	.notify_schgedA
	cmp edx,NM_DBLCLK
	jz	.notify_dblclkA
	cmp edx,\
		LVN_GETINFOTIPW
	jz	.notify_tip
	jmp	.ret0

.notify_tip:
;@break
;	mov eax,[r9+NMLVGETINFOTIP.iItem]
	
;---	xor eax,eax
;---	mov [r9+\
;---		NMLVGETINFOTIP.pszText],rax;uzDefault
	;---	mov rax,[r9+\
	;---		NMTVGETINFOTIPW.hItem]
	;---	mov r8,rax
	;---	mov rdx,rax
	;---	call art.cout2XX

	;---	test eax,eax
	;---	jz	winproc.ret0
	xor r8,r8
	xor r9,r9
	mov rcx,[hTip]
	call tip.popup
	jmp	.ret0

;---	mov eax,[r9+NMLVGETINFOTIP.dwFlags]
;---	mov rax,[r9+NMLVGETINFOTIP.pszText]
;---	mov [r9+NMLVGETINFOTIP.pszText],uzDefault
;---	mov [r9+NMLVGETINFOTIP.dwFlags],0

.notify_schgedA:
	mov rcx,\
		[r9+NM_LISTVIEW.lParam]
	test rcx,rcx
	jz	.ret0

	test [r9+\
		NM_LISTVIEW.uNewState],\
		LVIS_FOCUSED \
		or LVIS_SELECTED
	jz	.ret0

	mov rsi,[pEdit]
	cmp rcx,[rsi+\
		EDIT.curlabf]
	jz	.ret0

	call edit.view
	
	mov rcx,[rsi+\
		EDIT.curlabf]
	call .list_bm


;---	mov rax,[rsi+\
;---		EDIT.curlabf]
;---	mov r8,1
;---	mov rcx,[rax+\
;---		LABFILE.hSci]
;---	call sci.set_focus

	jmp .ret0

.notify_dblclkA:
	mov edx,[r9+\
		NMITEMACTIVATE.iItem]
	inc edx
	jz	.ret0

	dec edx
	xor eax,eax

	sub rsp,\
		sizea16.LVITEMW

	mov r9,rsp
	mov [r9+\
		LVITEMW.iItem],edx
	mov [r9+\
		LVITEMW.iSubItem],eax
	mov rcx,[.doc.hLvwA]
	call lvw.get_param

	mov rbx,[rsp+\
		LVITEMW.lParam]
	test rbx,rbx
	jz .ret0

	;--- test: may be rewritten
	mov edx,ASK_SAVE
	mov rcx,rbx
	call wspace.close_file

	;--- notify tree -> parent about change
	;--- use same stack for NMHDR
	;---	mov r9,[.lparam]
	;---	mov rax,[hTree]
	;---	mov [r9+NMHDR.hwndFrom],rax
	;---	mov eax,NM_DBLCLK
	;---	mov [r9+NMHDR.code],eax

	;---	xor r8,r8
	;---	mov edx,WM_NOTIFY
	;---	mov rcx,[hMain]
	;---	call apiw.sms
	jmp .exit

.wm_poschged:
	mov rbx,[pDoc]
	sub rsp,\
		sizeof.RECT
	mov rdx,rsp
	mov rcx,[.hwnd]
	call apiw.get_clirect

	mov edi,[rsp+RECT.bottom]
	shr edi,1
	mov esi,edi
	shr esi,2

	mov eax,SWP_NOZORDER

	mov r11,rsi
	add r11,r11
	add r11,rsi
	
	mov r10d,[rsp+RECT.right]
	xor r9,r9
	xor r8,r8
	mov rdx,HWND_TOP
	mov rcx,[.doc.hLvwA]
	call apiw.set_wpos

	mov rax,SWP_NOZORDER
	mov r11d,[rsp+RECT.bottom]
	sub r11,rsi
	sub r11,rsi
	sub r11,rsi
	sub r11,CY_GAP
	mov r10d,[rsp+RECT.right]
	mov r9,CY_GAP
	add r9,rsi
	add r9,rsi
	add r9,rsi
	xor r8,r8
	mov rdx,HWND_TOP
	mov rcx,[.doc.hLvwB]
	call apiw.set_wpos

	xor edx,edx
	mov rcx,[.doc.hLvwA]
	call lvw.set_colwidthH
	jmp	.ret0


.wm_initdialog:
	mov rbx,[pDoc]
	mov [.doc.hDlg],rcx

	mov rdi,\
		apiw.get_dlgitem

	mov rdx,DOC_LVWA
	mov rcx,[.hwnd]
	call rdi
	mov [.doc.hLvwA],rax
	mov [hDocs],rax

	;--- enable tool balloon for open documents
	mov r9,\
		LPSTR_TEXTCALLBACK
	mov r8,rax
	mov rdx,[.hwnd]
	mov rcx,[hTip]
	call tip.add


	mov rdx,DOC_LVWB
	mov rcx,[.hwnd]
	call rdi
	mov [.doc.hLvwB],rax



.ret1:				;message processed
	xor rax,rax
	inc rax
	jmp	.exit

.ret0:
	xor rax,rax
	jmp	.exit

.exit:
	@wepi
