  
  ;#-------------------------------------------------ß
  ;|          lang MPL 2.0 License                   |
  ;|   Copyright (c) 2011-2012, Marc Rainer Kranz.   |
  ;|            All rights reserved.                 |
  ;ö-------------------------------------------------ä

  ;#-------------------------------------------------ß
  ;| uft-8 encoded üäöß
  ;| update:
  ;| filename:
  ;ö-------------------------------------------------ä

	VERBOSE equ TRUE

	UR	equ 1	;--- read only
	UW	equ 2	;--- can write
	U8	equ 8	;--- utf8
	U16	equ 16	;--- utf16

	struct RESTABLE
		lang db 16 dup (0)
		lcid dw 0 ;--- culture name
		ids	 dw 0
		dlen dw 0 ;--- data len
		flen dw 0 ;--- file len
		dave dw 0 ;--- avverage data len
		resi dw 0
				dw 0,0
	ends

	struct RESDEF
		id		dw 0
		next	dw 0	;--- offset from res_r
		len		dw 0	;--- essential len 
		;--- follow utf8+0+0 aligned 2 string
	ends
	
	macro @make_lang argidname,arglcid,\
		argnotransl*,[argid,argstr]{
	common
		local .tmpNT
		label res_h		;--- header
		.lang db argidname,0
		@align 16,0
		.lcid	dw arglcid
		.ids	dw 0
		.dlen	dw 0
		.flen dw 0
		.dave dw 0			
		.resi dw res_i
			dw 2 dup (9090h)
		dd -1
		dw 0
		label .tmpNT
			argnotransl
		store WORD ($-.tmpNT) at (.tmpNT -2)
		dw 0
		@align 16,0
		label res_i		;--- indexes
			dw 256 dup (-1)
		label res_r		;--- resource utf8 str
		ids=0
		dlen=0
		flen=0

		forward
		local tmN,tmL,tmQ,tmR,tmZ
		label tmQ
			dw argid
		label tmN
			dw 0			;--- next
		label tmL
			dw 0
		label tmR
			argstr
		store WORD ($-tmR) at tmL
			dw 0
			@align 2,0
			ids = ids + 1
			dlen = dlen + ($-tmR)

			load ref WORD from res_i+((argid and 0FFh)*2)
			store WORD tmQ-res_r at res_i+((argid and 0FFh)*2)
			store WORD ref at tmN

		common
			store WORD ids at res_h.ids
			store WORD dlen at res_h.dlen
		@align 16,0
			store WORD $ at res_h.flen
			store WORD (dlen/ids) at res_h.dave

		match =TRUE,VERBOSE\{
			display "(AVE.) TLEN = "
			display_decimal dlen/ids
			display 13,10
			display "fLEN = "
			display_decimal $
			display 13,10
		\}
	}

