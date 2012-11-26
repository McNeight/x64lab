hex:

.create:
	;--- in RCX parent -----
	push rbp
	mov rbp,rsp
	and rsp,-16

	push 0
	push [hInst]
	push 0
	push rcx
	push 0
	push 0
	push 0
	push 0

	sub rsp,20h
	mov r9,WS_CHILD or \
		WS_VSCROLL or \
 		WS_CLIPCHILDREN or \
		WS_VISIBLE
	mov r8,0
	mov rdx,\
		uzHexClass
	mov rcx,WS_EX_CLIENTEDGE
	call [CreateWindowExW]

	mov rsp,rbp
	pop rbp
	ret 0

