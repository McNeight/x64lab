  
  ;#-------------------------------------------------ß
  ;|          dock64  MPL 2.0 License                |
  ;|   Copyright (c) 2011-2012, Marc Rainer Kranz.   |
  ;|            All rights reserved.                 |
  ;ö-------------------------------------------------ä

  ;#-------------------------------------------------ß
  ;| uft-8 encoded üäöß
  ;| update:
  ;| filename:
  ;ö-------------------------------------------------ä

panel:
	;*----------------------------------------------------------
	;|                  PANEL.
	;*----------------------------------------------------------
	virtual at rbx
		.pnl PNL
	end virtual

	virtual at rsi
		.mdl MDL
	end virtual
	
	;*----------------------------------------------------------
	;|                  PANEL.WPROC
	;*----------------------------------------------------------

.proc:
@wpro rbp,\
	rbx rdi rsi
	cmp edx,WM_PAINT
	jz	.wm_paint
	cmp edx,WM_MOUSEMOVE
	jz	.wm_mmove
	cmp edx,WM_NCLBUTTONUP
	jz	.wm_nclbutup
	cmp edx,WM_NCLBUTTONDOWN
	jz	.wm_nclbutdw
	cmp edx,WM_LBUTTONUP
	jz	.wm_lbutup
	cmp edx,WM_LBUTTONDOWN
	jz	.wm_lbutdw
	cmp edx,WM_SYSCOMMAND
	jz	.wm_syscomm
	cmp rdx,WM_MOUSEACTIVATE
	jz	.wm_mactivate
	cmp edx,WM_CREATE
	jz	.wm_create
	cmp edx,WM_DESTROY
	jz	.wm_destroy
	jmp	.defwndproc

.get_struct:
	mov rcx,[.hwnd]
	call apiw.get_wldata
	test rax,rax
	jz	.err_gs
	mov rbx,rax
	mov rsi,[.pnl.mdl]
.err_gs:
	ret 0


.wm_mactivate:
	call .get_struct
	jz	.ret0
	
	mov rax,[.mdl.pLastAct]
	test rax,rax
	jz	.wm_mactivateA
	cmp rax,rbx
	jz	.ret0

	mov rcx,[rax+PNL.hwnd]
	mov [rax+PNL.active],FALSE

	xor r8,r8
	xor rdx,rdx
	call apiw.invrect
	
.wm_mactivateA:
	mov [.pnl.active],TRUE
	mov r8,FALSE;TRUE
	xor rdx,rdx
	mov rcx,[.pnl.hwnd]
	call apiw.invrect

.wm_mactivateB:	
	mov [.mdl.pLastAct],rbx
	mov rax,MA_ACTIVATE
	jmp	.exit

.wm_syscomm:
	call .get_struct
	jz	.defwndproc
	mov eax,[.wparam]
	and eax,0FFF0h
	cmp eax,SC_CLOSE
	jnz	.defwndproc
	jmp	.ret0

;--- ok deactivated for now
;---	or [.pnl.type],IS_HID
;---	mov rdx,SW_HIDE
;---	mov rcx,[.pnl.hwnd]
;---	call apiw.show
;---	jmp	.defwndproc

.lbutdw_part:
;---	push rax
;---	mov r8,rbx
;---	mov rdx,rax
;---	call art.cout2XX
;---	pop rax

	cmp eax,PART_CBUT
	jnz	.lbutdw_split
	jmp	.defwndproc

.lbutdw_split:
	mov [.mdl.sside],al
	test [.pnl.type],SHA_PA
	mov rcx,[.hwnd]
	jz	@f
;@break
;mov al,[.pnl.alignment]
;test al,ALIGN_V
	and al,[.pnl.alignment]
	jz	@f
;	movzx r8,[.pnl.alignment]
;	mov rdx,rax
;	call art.cout2XX
	

	mov rcx,rbx
	call dock64.get_sfisha
	mov rcx,[rax+PNL.hwnd]
@@:
	call apiw.set_capt

	mov [.mdl.flags],\
		F_SPLIT ;or F_SHADOW
	
	lea rdx,[.mdl.shadrc]
	mov rcx,[.hwnd]
	call apiw.get_winrect

	mov eax,SWP_NOZORDER\
		or SWP_SHOWWINDOW
	mov r11d,\
		[.mdl.shadrc.bottom]
	sub r11d,\
		[.mdl.shadrc.top]
	mov r10d,\
		[.mdl.shadrc.right]
	sub r10d,\
		[.mdl.shadrc.left]
	mov r9d,\
		[.mdl.shadrc.top]
	mov r8d,\
		[.mdl.shadrc.left]
	mov rdx,HWND_TOP
	mov rcx,\
		[.mdl.hShadow]
	call apiw.set_wpos
	jmp	.defwndproc


	;--- button down from a panel
.wm_lbutdw:
	call .get_struct
	jz	.defwndproc

	sub rsp,20h
	mov rcx,rsp
	call apiw.get_curspos

	mov rdx,[rsp]
	mov rcx,[.hwnd]
	call apiw.ddetect
	test rax,rax
	jz	.defwndproc;.ret0

	mov rdx,[rsp]
	mov rcx,rbx
	call dock64.is_pton
	test rax,rax
	jnz	.lbutdw_part

	mov rcx,rbx
	call dock64.lo_drop
	or [.pnl.type],IS_FLO

	mov rdx,rsi
	mov rcx,rbx
	call dock64.lo_set

	lea rdx,[.pnl.wrc]
	mov rcx,[.hwnd]
	call apiw.get_winrect


	;3) --- set style as FLOAT
	mov r8d,FLOAT_STYLE
	mov [.pnl.style],r8d
	mov rcx,[.pnl.hwnd]
	call apiw.set_wlstyle

	;4) --- re-parent to desktop
	mov rdx,0
	mov rcx,[.pnl.hwnd]
	call apiw.set_parent

	;5) --- update layout
	mov rdx,\
		WM_WINDOWPOSCHANGED
	mov rcx,rsi
	call dock64.layout

	mov eax,\
		SWP_FRAMECHANGED

	mov edx,[.pnl.wrc.bottom]
	sub edx,[.pnl.wrc.top]
	mov r11d,[.pnl.frc.bottom]
	sub r11d,[.pnl.frc.top]
	cmovle r11,rdx
	
	mov edx,[.pnl.wrc.right]
	sub edx,[.pnl.wrc.left]
	mov r10d,[.pnl.frc.right]
	sub r10d,[.pnl.frc.left]
	cmovle r10,rdx
	
	mov edx,r10d
	shr edx,2
	mov r8d,[rsp]
	sub r8,rdx

	movzx edx,[cy_caption]
	mov r9d,[rsp+4]
	sub r9,rdx

	mov rdx,HWND_TOP
	mov rcx,[.pnl.hwnd]
	call apiw.set_wpos

	lea rdx,[.pnl.wrc]
	mov rcx,[.pnl.hwnd]
	call apiw.get_winrect

	mov rax,[rsp]
	mov [.mdl.phit],rax

	;	mov r8,[rsp+8]
	;	mov rdx,qword[rsp]
	;	call art.cout2XX

	mov eax,[.pnl.wrc.left]
	sub [.mdl.phit.x],eax
	mov eax,[.pnl.wrc.top]
	sub [.mdl.phit.y],eax
	jmp	.wm_nclbutdwA

.wm_nclbutdw:
	mov eax,[.wparam]
	cmp eax,HTCAPTION
	jnz	.defwndproc

	call .get_struct
	jz	.defwndproc

	sub rsp,20h
	lea rcx,[.mdl.phit]
	call apiw.get_curspos

	lea rdx,[.pnl.frc]
	mov rcx,[.hwnd]
	call apiw.get_winrect

	mov eax,[.pnl.frc.left]
	sub [.mdl.phit.x],eax
	mov eax,[.pnl.frc.top]
	sub [.mdl.phit.y],eax
	
.wm_nclbutdwA:
	mov rcx,[.hwnd]
	call apiw.set_capt
	mov [.mdl.flags],\
		F_MOVE

	jmp	.defwndproc;.ret0

.wm_nclbutup:
;---	push rax
;---	mov r8,rax
;---	mov rdx,[.hwnd]
;---	call art.cout2XX
;---	pop rax

;	mov eax,[.wparam]
;	cmp eax,HTCLOSE
;	jnz	.wm_lbutup
;	;---
;	@break
;	jmp	.defwndproc

.wm_lbutup:
	;--- 1) get structure
	call .get_struct
	jz	.defwndproc
	call apiw.rel_capt

	test [.mdl.flags],\
		F_SPLIT
	jnz	.lbutup_split

	mov rdx,[.mdl.target]
	test rdx,rdx
	jz	.lbutup_hide

	mov rcx,rbx
	call dock64.lo_drop

	mov rdx,[.mdl.target]
	mov rcx,rbx
	call dock64.lo_repo

	mov rdx,[.mdl.hwnd]
	mov rcx,[.hwnd]
	call apiw.set_parent

	mov r8,CHILD_STYLE
	mov [.pnl.style],r8d
	mov rcx,[.pnl.hwnd]
	call apiw.set_wlstyle

;lea rdx,[.pnl.frc]
;mov rcx,[.hwnd]
;call apiw.get_winrect


.lbutupA:
	lea rdx,[.mdl.shadrc]
	mov rcx,[.mdl.hShadow]
	call apiw.get_winrect

	;	mov r8,[.mdl.shadrc+8]
	;	mov rdx,[.mdl.shadrc]
	;	call art.cout2XX

	mov eax,SWP_NOZORDER;\
		;or SWP_NOSENDCHANGING

	mov r11d,\
		[.mdl.shadrc.bottom]
	sub r11d,\
		[.mdl.shadrc.top]
	mov r10d,\
		[.mdl.shadrc.right]
	sub r10d,\
		[.mdl.shadrc.left]
	mov r9d,\
		[.mdl.shadrc.top]
	mov r8d,\
		[.mdl.shadrc.left]
	mov rdx,HWND_TOP
	mov rcx,\
		[.pnl.hwnd]
	call apiw.set_wpos

	mov rdx,WM_WINDOWPOSCHANGED
	mov rcx,rsi
	call dock64.layout

.lbutup_hide:
	mov rdx,SW_HIDE
	mov rcx,[.mdl.hShadow]
	call apiw.show

.lbutup_ok:
	mov [.mdl.flags],0
	mov [.mdl.cside],0
	jmp	.defwndproc

.lbutup_split:
	test [.pnl.type],\
		SHA_PA
	jz .lbutupA

;	movzx r8,[.pnl.ratio]
;	mov rdx,-1
;	call art.cout2XX

	mov rcx,rbx
	call dock64.get_sfisha
	mov rdi,r8
	sub rsp,16

	lea rdx,[rsp]
	mov rcx,[rdi+PNL.hwnd]
	call apiw.get_winrect

	mov ecx,[rsp+RECT.bottom]
	sub ecx,[rsp+RECT.top]

	movzx r8,[.pnl.ratio]
	movzx r9,[rdi+PNL.ratio]

	mov eax,r9d
	mov edx,[.mdl.shadrc.top]
	sub edx,[rsp+RECT.top]
	mul edx
	xor edx,edx
	test ecx,ecx
	jz .lbutup_hide
	div ecx
	mov [rdi+PNL.ratio],al
	add r9l,r8l
	sub r9l,al
	mov [.pnl.ratio],r9l
	
;	mov r8,rax
;	movzx rdx,[rdi+PNL.ratio]
;	call art.cout2XX

	add rsp,16
	jmp	.lbutupA


.wm_mmove:
	call .get_struct
	jz	.defwndproc;.ret0
	sub rsp,\
		sizeof.POINT+\	;--- x,y adjustemnt	
		sizeof.POINT+\	;--- x,y mouse movement
		sizeof.RECT			;--- shadow on side rect
	mov rcx,rsp
	call apiw.get_curspos

	xor eax,eax
	xor edi,edi
	mov rdi,rsi		;--- set RDI default target
	
	test [.mdl.flags],\
		F_MOVE
	jnz	.mmove_move
	test [.mdl.flags],\
		F_SPLIT
	jnz	.mmove_split

.mmove_check:
	test [.pnl.type],\
		IS_FLO
	jnz	.defwndproc
	mov r8,[rsp]
	mov [rsp+8],r8

	mov rdx,[rsp]
	mov rcx,rbx
	call dock64.is_pton

;	push rax
;	push rcx
;	push rdx
;	mov rdx,rax
;	mov r8,[rsp]
;	call art.cout2XX
;	pop rdx
;	pop rcx
;	pop rax


.mmove_checkE:
	cmp rcx,rdx
	jz	.defwndproc
	mov rcx,rdx
	call apiw.set_curs
	jmp	.defwndproc

.mmove_split:
	movzx rax,[.mdl.sside]
	and al,[.pnl.alignment]
	jnz	.mmove_splitA

	;--- apply shared panel policy
;	movzx r8,[.mdl.sside]
;	mov rdx,rbx
;	call art.cout2XX

	mov rcx,[rsp]
	call shadow.split_sharc
	test rax,rax
	jz	.defwndproc
	jmp	.mmove_splitB

.mmove_splitA:
;	movzx r8,[.mdl.sside]
;	mov rdx,rbx
;	call art.cout2XX

	mov rcx,[rsp]
	call shadow.split_rc
	test rax,rax
	jz	.defwndproc

.mmove_splitB:
	@reg2rect .mdl.shadrc,rax
	

	mov eax,SWP_NOZORDER;\
		;or SWP_NOSENDCHANGING
	mov r11d,\
		[.mdl.shadrc.bottom]
	sub r11d,\
		[.mdl.shadrc.top]
	mov r10d,\
		[.mdl.shadrc.right]
	sub r10d,\
		[.mdl.shadrc.left]
	mov r9d,\
		[.mdl.shadrc.top]
	mov r8d,\
		[.mdl.shadrc.left]
	mov rdx,HWND_TOP
	mov rcx,\
		[.mdl.hShadow]
	call apiw.set_wpos	

	jmp	.defwndproc

.mmove_move:
	mov r8,[rsp]
	mov [rsp+8],r8
	mov [rsp+16],r8

;mov r8,[rsp]
;mov rdx,[.mdl.phit]
;call art.cout2XX

	mov r8d,[rsp]
	mov r9d,[rsp+4]
	sub r8d,[.mdl.phit.x]
	sub r9d,[.mdl.phit.y]

	mov eax, SWP_NOZORDER\		;---0 
		or SWP_NOSENDCHANGING\
		or SWP_NOSIZE

	mov rdx,HWND_TOP
	mov rcx,[.hwnd]
	call apiw.set_wpos

	mov r9,1
	mov r8,rsp
	mov rdx,[.mdl.hwnd]
	mov rcx,0
	call apiw.map_wpt

	mov r8,\
		CWP_SKIPTRANSPARENT\
		or CWP_SKIPINVISIBLE
	mov rdx,[rsp]
	mov rcx,[.mdl.hwnd]
	call apiw.chwinfptx

	;push rax
	;	mov r8,[rsp+8]
	;	mov rdx,rax
	;	call art.cout2XX
	;pop rax

	test rax,rax
	jz	.mmove_moveH
	
	cmp rax,[.mdl.hwnd]
	jnz	.mmove_chi

	mov rax,[.mdl.src]
	mov [.mdl.shadrc],rax
	mov rax,[.mdl.src+8]
	mov [.mdl.shadrc+8],rax

	mov r9,2
	lea r8,[.mdl.shadrc]
	mov rdx,0
	mov rcx,[.mdl.hwnd]
	call apiw.map_wpt

;	mov r8,[.mdl.shadrc+8]
;	mov rdx,[.mdl.shadrc]
;	call art.cout2XX
	jmp	.mmove_chiA

.mmove_chi:
	mov rcx,rax
	call apiw.get_wldata
	test rax,rax
	jz	.mmove_moveH

	mov rdi,rax
	lea rdx,[rdi+PNL.wrc]
	mov rcx,[rdi+PNL.hwnd]
	call apiw.get_winrect

	mov rax,[rdi+PNL.wrc]
	mov [.mdl.shadrc],rax
	mov rax,[rdi+PNL.wrc+8]
	mov [.mdl.shadrc+8],rax

.mmove_chiA:
	mov edx,[rsp+8+POINT.y]
	mov ecx,[rsp+8+POINT.x]
	call dock64.get_side

	test eax,eax
	jz	.mmove_moveH
	cmp al,[.mdl.exclude]
	jz	.mmove_moveH
	test al,[.mdl.exclude]
	jnz	.mmove_moveH
	
	cmp al,[.pnl.exclude]
	jz	.mmove_moveH
	test al,[.pnl.exclude]
	jnz	.mmove_moveH
	;---
	jmp	.mmove_moveS

.mmove_moveH:
	xor edx,edx
	mov [.mdl.cside],dl
	mov [.mdl.target],rdx
	test [.mdl.flags],\
		F_SHADOW
	jz	.defwndproc;.ret0
	and [.mdl.flags],\
		not F_SHADOW

	mov eax,\
		SWP_NOZORDER or \
		SWP_HIDEWINDOW or \
		SWP_NOSIZE or\
		SWP_NOMOVE
	jmp	.mmove_moveP1

.mmove_moveS:
	xor edx,edx
	test [.mdl.flags],\
		F_SHADOW
	jz	.mmove_moveS2
	cmp rdi,[.mdl.target]
	jnz	.mmove_moveS2

.mmove_moveS3:
	cmp al,[.mdl.cside]
	jnz	.mmove_moveS2
	jmp	.defwndproc;.ret0

.mmove_moveS2:
	mov [.mdl.cside],al
	or [.mdl.flags],\
		F_SHADOW
	mov [.mdl.target],rdi

.mmove_moveP:
	movzx r8,[.mdl.cside]
	mov rdx,[.mdl.target]
	call art.cout2XX

	call shadow.size_rc

;	mov r8,[.mdl.shadrc+8]
;	mov rdx,[.mdl.shadrc]
;	call art.cout2XX

	mov eax,SWP_NOZORDER \
		or SWP_SHOWWINDOW

.mmove_moveP1:
	mov r11d,\
		[.mdl.shadrc.bottom]
	sub r11d,\
		[.mdl.shadrc.top]
	mov r10d,\
		[.mdl.shadrc.right]
	sub r10d,\
		[.mdl.shadrc.left]
	mov r9d,\
		[.mdl.shadrc.top]
	mov r8d,\
		[.mdl.shadrc.left]
	mov rdx,HWND_TOP
	mov rcx,\
		[.mdl.hShadow]
	call apiw.set_wpos

	jmp	.defwndproc;.ret0



	;*----------------------------------------------------------
	;|                  WM_DESTROY (PANEL)
	;*----------------------------------------------------------
.wm_destroy:
	call .get_struct
	jz	.ret0
	mov rcx,[.pnl.hControl]
	test rcx,rcx
	jz	.wm_destroyA
	call apiw.destroy

.wm_destroyA:
	mov rcx,rbx
	call art.a16free
	jmp	.ret0

	;*----------------------------------------------------------
	;|                  WM_CREATE (PANEL)
	;*----------------------------------------------------------
.wm_create:
	mov rbx,[r9]
	mov r8,rbx
	mov rdi,[.pnl.tmp]
	mov rsi,[.pnl.mdl]
	mov [.pnl.hwnd],rcx
	call apiw.set_wldata

;	mov [cside],0
;	xor edx,edx
	mov rdx,rdi
	mov rcx,rbx
	call dock64.lo_set

	;--------------- debugging 
	;sub rsp,110h
	;mov r9,rsp
	;mov r8,100h
	;mov rdx,WM_GETTEXT
	;mov rcx,[.hwnd]
	;call apiw.sms
	;mov r8,rsp
	;mov rdx,rbx
	;call art.cout2XU
	;add rsp,110h
	;------------------------

	;mov rax,[.pnl.hControl]
	;test rax,rax
	;jz	.ret0

	;mov rdx,[.pnl.hwnd]
	;mov rcx,rax
	;call apiw.set_parent
	inc [.mdl.nslots]
	mov eax,[.mdl.seed]
	call art.pmc_fuerst
	mov [.pnl.id],eax
	mov [.mdl.seed],eax

.ret0:
	xor rax,rax
	jmp	.exit

.ret1:
	xor rax,rax	
	inc eax
	jmp	.exit


	;*----------------------------------------------------------
	;|                  WM_PAINT (PANEL)
	;*----------------------------------------------------------
.wm_paint:
	call .get_struct
	jz	.ret0
	test [.pnl.type],\
		IS_HID
	jnz	.ret0

	sub rsp,\
		sizea16.PAINTSTRUCT+\
		FILE_BUFLEN
	mov rax,rsp
	push r12
	push r13

	mov r12,rax

	lea r9,[rax+\
		sizea16.PAINTSTRUCT]
	mov r8,100h
	mov rdx,WM_GETTEXT
	mov rcx,[.hwnd]
	call apiw.sms

	mov rdx,r12
	mov rcx,[.hwnd]
	call apiw.beg_paint
	mov rdi,rax

	lea rdx,[.pnl.crc]
	mov rcx,[.pnl.hwnd]
	call apiw.get_clirect

	mov rax,[.pnl.crc]
	mov [.pnl.ctrc],rax
	mov [.pnl.caprc],rax
	;mov [.pnl.cbutrc],rax
	mov rax,[.pnl.crc+8]
	mov [.pnl.ctrc+8],rax
	mov [.pnl.caprc+8],rax
	;mov [.pnl.cbutrc+8],rax

	movzx eax,[.pnl.alignment]
	movzx ecx,[cx_border]
	movzx edx,[cy_edge]
	movzx r8d,[cx_fxframe]
	movzx r9d,[cx_smbsize]
	;mov r9,8

	test [.pnl.type],IS_FLO
	jnz	.wm_paintB

	cmp al,ALIGN_LEFT
	jz	.wm_paintLX
	cmp al,ALIGN_TOP
	jz	.wm_paintUP
	cmp al,ALIGN_RIGHT
	jz	.wm_paintRX
	cmp al,ALIGN_BOTTOM
	jz	.wm_paintDW

.wm_paintCC:
	mov [.pnl.caprc.top],ecx
	mov [.pnl.caprc.bottom],r8d
	add [.pnl.caprc.bottom],r9d
	mov [.pnl.caprc.left],ecx
	sub [.pnl.caprc.right],ecx
	sub [.pnl.caprc.right],r8d
	sub [.pnl.caprc.right],r9d

	mov [.pnl.ctrc.left],ecx
	mov eax,[.pnl.caprc.right]
	add eax,r9d
	mov [.pnl.ctrc.right],eax
	mov eax,[.pnl.caprc.bottom]
	add eax,edx
	mov [.pnl.ctrc.top],eax

	;mov r8,[.pnl.ctrc+8]
	;mov rdx,[.pnl.ctrc]
	;call art.cout2XX
	jmp	.wm_paintA

.wm_paintRX:
	mov [.pnl.caprc.top],r8d
	mov [.pnl.caprc.bottom],r8d
	add [.pnl.caprc.bottom],r9d

	mov [.pnl.caprc.left],ecx
	add [.pnl.caprc.left],r8d

	sub [.pnl.caprc.right],ecx
	sub [.pnl.caprc.right],r8d
	sub [.pnl.caprc.right],r9d

	mov [.pnl.ctrc.left],ecx
	add [.pnl.ctrc.left],r8d
	mov eax,[.pnl.caprc.right]
	add eax,r9d
	mov [.pnl.ctrc.right],eax
	mov eax,[.pnl.caprc.bottom]
	add eax,edx
	mov [.pnl.ctrc.top],eax
	jmp	.wm_paintA

.wm_paintDW:
	mov [.pnl.caprc.top],r8d
	add [.pnl.caprc.top],ecx
	add [.pnl.caprc.top],edx

	mov [.pnl.caprc.bottom],r8d
	add [.pnl.caprc.bottom],r9d
	add [.pnl.caprc.bottom],ecx
	add [.pnl.caprc.bottom],edx

	mov [.pnl.caprc.left],ecx
	sub [.pnl.caprc.right],ecx
	sub [.pnl.caprc.right],r8d
	sub [.pnl.caprc.right],r9d

	mov [.pnl.ctrc.left],ecx
	mov eax,[.pnl.caprc.right]
	add eax,r9d
	mov [.pnl.ctrc.right],eax
	mov eax,[.pnl.caprc.bottom]
	add eax,edx
	mov [.pnl.ctrc.top],eax
	jmp	.wm_paintA

.wm_paintUP:
	mov [.pnl.caprc.top],r8d
	mov [.pnl.caprc.bottom],r8d
	add [.pnl.caprc.bottom],r9d
	mov [.pnl.caprc.left],ecx
	sub [.pnl.caprc.right],ecx
	sub [.pnl.caprc.right],r8d
	sub [.pnl.caprc.right],r9d

	mov [.pnl.ctrc.left],ecx
	mov eax,[.pnl.caprc.right]
	add eax,r9d
	mov [.pnl.ctrc.right],eax
	mov eax,[.pnl.caprc.bottom]
	add eax,edx
	mov [.pnl.ctrc.top],eax
	sub [.pnl.ctrc.bottom],ecx
	sub [.pnl.ctrc.bottom],edx
	jmp	.wm_paintA

.wm_paintLX:
	mov [.pnl.caprc.top],r8d
	mov [.pnl.caprc.bottom],r8d
	add [.pnl.caprc.bottom],r9d
	mov [.pnl.caprc.left],ecx

	sub [.pnl.caprc.right],ecx
	sub [.pnl.caprc.right],edx
	sub [.pnl.caprc.right],r8d
	sub [.pnl.caprc.right],r9d
		
	mov [.pnl.ctrc.left],ecx
	mov eax,[.pnl.caprc.right]
	add eax,r9d
	mov [.pnl.ctrc.right],eax
	mov eax,[.pnl.caprc.bottom]
	add eax,edx
	mov [.pnl.ctrc.top],eax
	;	mov r8,[.pnl.ctrc+8]
	;	mov rdx,[.pnl.ctrc]
	;	call art.cout2XX

.wm_paintA:
	mov r10d,[.pnl.ctrc.bottom]
	mov r9d,[.pnl.ctrc.right]
	mov r8d,[.pnl.ctrc.top]
	mov edx,[.pnl.ctrc.left]
	mov rcx,rdi
	call apiw.excl_cliprect	

	mov r8,[hBrPanel]
	lea rdx,[.pnl.crc]
	mov rcx,rdi
	call apiw.fillrect

	mov r8,[hBrActCapt]
	mov r9,[hBrInactCapt]
	cmp [.pnl.active],TRUE
	cmovnz r8,r9

	lea rdx,[.pnl.caprc]
	mov rcx,rdi
	call apiw.fillrect

	mov rdx,TRANSPARENT
	mov rcx,rdi
	call apiw.set_bkmode

	mov r10,DT_LEFT or \
		DT_VCENTER or \
		DT_NOCLIP or \
		DT_SINGLELINE	or \
		DT_END_ELLIPSIS
	lea r9,[.pnl.caprc]
	or r8,-1
	lea rdx,[r12+\
		sizea16.PAINTSTRUCT]
	mov rcx,rdi
	call apiw.drawtext

	mov eax,[.pnl.caprc.right]
	mov ecx,[.pnl.caprc.left]
	inc eax
	mov [.pnl.caprc.left],eax
	mov [.pnl.caprc.right],eax
	add [.pnl.caprc.right],17
	
	xor r11,r11
	lea r10,[.pnl.caprc]
	mov r9,CBS_NORMAL
	mov r8,WP_SMALLCLOSEBUTTON
	mov rdx,rdi
	mov rcx,[hThmWin]
	call apiw.th_drawbkg

.wm_paintB:
	mov eax,SWP_NOZORDER \
		or SWP_NOSENDCHANGING\
		or 0;SWP_NOREDRAW
	mov r11d,[.pnl.ctrc.bottom]
	sub r11d,[.pnl.ctrc.top]
	mov r10d,[.pnl.ctrc.right]
	sub r10d,[.pnl.ctrc.left]
	mov r9d,[.pnl.ctrc.top]
	mov r8d,[.pnl.ctrc.left]
	mov rdx,HWND_TOP
	mov rcx,[.pnl.hControl]
	call apiw.set_wpos

.wm_paintE:
	mov rdx,r12
	mov rcx,[.hwnd]
	call apiw.end_paint
	pop r13
	pop r12
	jmp	.defwndproc


.defwndproc:
	mov r9,[.lparam]
	mov r8,[.wparam]
	mov rdx,[.msg]
	mov rcx,[.hwnd]
	sub rsp,20h
	call [DefWindowProcW]

.exit:
@wepi


