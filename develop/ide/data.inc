  
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

section '.data' data readable writeable
	curDir	dq sizeof.DIR
	dirHash	dq 400h*8
	extHash dq 100h*8
	
	pConf		dq sizeof.CONFIG
	pCons 	dq sizeof.CONS
	pMp			dq sizeof.MPURP
	pIo			dq sizeof.IODLG * 4
	pHu			dq sizeof.HU
	pEdit		dq sizeof.EDIT
	pDevT		dq sizeof.DEVT
	pTool		dq sizeof.TOOLDLG
	pTmpl		dq sizeof.TMPL
	pDoc		dq sizeof.DOCDLG
	pKdlg		dq sizeof.KEYDLG
	pTime		dq sizeof.SYSTIME
	pKeya		dq (MI_OTHER-MNU_X64LAB) * sizeof.KEYA
	NUM_ITEMS = ($-curDir)/8

	hSciDll	dq 0
	hDocker	dq 0
	hHexDll	dq 0

	pExtClass	dq 0
	pBinExt		dq 0
	pLangRes	dq 0

	hTree			dq 0
	hRootWsp	dq 0
	hDocs			dq 0
	pLabfWsp	dq 0

	hTip			dq 0
	hIcon			dq 0
	hInst			dq 0
	hAccel		dq 0
	hMain			dq 0
	hMnuMain	dq 0
	hFloat		dq 0
	hlaSysList	dq 0
	hsmSysList	dq 0
	hMnuFont		dq 0
	pTopStr	dq 0
	pTopExt	dq 0
	hBmpIml	dq 0

	pTopCmd	dq 0

	appDir		dq 0
	backDir		dq 0
	confDir		dq 0
	;logDir		dq 0
	;mountDir	dq 0
	helpDir		dq 0
	plugDir		dq 0
	projDir		dq 0
	templDir	dq 0
	tmpDir		dq 0
	toolDir		dq 0
  DEF_DIRS	= ($-appDir)/8

	match n,\`MAINCLASS {	uzClass	du n,0 }
	match =TRUE,DEBUG {
		uzTitle du TITLE," (DEBUG) "
	}
	match =FALSE,DEBUG {
		uzTitle du TITLE," v. "
	}
	match v,VERSION {
    uzVers du `v,0 }

		szCharExt 	db "_999999",0

		rexpSOL1	db "^.*\S" 	;--- comment line SOL
		rexpSOL2a	db "^\(\s*"	;--- follow needle for SOL+patt
		rexpSOL2b	db "\)\(.*\)"
		rexpTAG2	db "\2",0
		szDefLang	db "en-US",0
		szCourierN	db "Courier New",0

	;---mydummy db "path",0
	;---myval   db "%path%;E:\PellesC",0

	@szhash	back,bold,\
		clearall,commline,commstart,commend,\
		font,fontsize,fore,\
		italic,\
		keyword,\
		lexer,\
		multisel,\
		stylebits,selback,style,\
		tabwidth,\
		\	;------- config
		atime,\
		cons,cdate,ctime,curs,\
		docs,\
		env,ext,\
		fshow,\
		language,\
		owner,\
		pos,\
		tree,\
		session,\
		version,\
		wspace

		align 2
		tmMnuSize	SIZE 6,28
		uzExtName		du "ext",0
		uzBackName	du "backup",0
		uzAccelName du "accel",0
		uzConfName	du "config",0
		uzLogName   du "log",0
		uzHelpName	du "help",0
		uzMountName	du "mount",0
		uzPlugName	du "plugin",0
		uzLangName	du "lang",0
		uzProjName	du "project",0
		uzTemplName du "template",0
		uzWspName		du "workspace",0
		uzModName		du "module",0
		uzSnipName	du "snippet",0
		uzTmpName	  du "tmp",0
		uzToolName 	du "tool",0
		uzDevTName	du "devtool",0
		uzMenuName	du "menu",0
		uzExplore		du "explore",0
		uzDocking		du "docking",0
		uzDefLang		du "en-US",0
		uzHexDll		du "hexview.dll",0
		uzHexClass	du "HexView32",0
		uzUpdate		du "update",0
		uzJob				du "job",0
		uzCommand		du "command",0

		uzDefault  du "default"		;<--- follows
		uzLabExt   du "."
		uzAppName  du TITLE,0
		uzUtf8Ext  du ".utf8",0
		uzBinExt   du "."
		uzBinName	 du "bin",0
		uzPngExt   du ".png",0
		uzExeExt   du ".exe",0
		uzSciExt   du ".sci",0
		uzBmpExt	 du ".bmp",0
		uzVbsExt	 du ".vbs",0
		uzWsfExt	 du ".wsf",0
		usOptC		 du "/C"
		usOptU		 du "/U"
		usOptA		 du "/A"
		usCmd 		 du "cmd " ;--- 16 bytes
		uzCscript	 du "cscript",0
		uzNoLogo	 du "//nologo",0
		uzR				 du "r /e" 
		;--- "explore" "r /e"  ',"path"'
		;--- uzStart du "cmd /C  ",0

		uzTreeClass	du "SysTreeView32",0
		uzLvwClass	du "SysListView32",0
		uzStcClass	du "STATIC",0

		uzCbexClass	du "ComboBoxEx32",0
		uzStbClass	du "msctls_statusbar32",0
		uzTipClass	du "tooltips_class32",0
		uzSciDll		du "Scilexer64.dll",0
		uzSciClass	du "Scintilla",0

		;---uzDummy du "äöüßDatenträger",0
		;---uzDummy1 db "многоязычных",0
		
		;--- menu -----------------------------------------
		macro @mni argname,argicon,argtysta,argflags{
			t#argname equ \
				((argflags and 0FFFFh) shl 48) or \
				((argtysta and 0FFFFh) shl 32) or \
				((argicon shl 16) and 0FFFF0000h) or \
				(argname and 0FFFFh)
		}

		macro @mnp argname,\
			argicon,\
			argtysta,\
			argflags {
			common
				h#argname dq 0
			@mni \
				argname,\
				argicon,\	
				argtysta,\
				argflags
			;---		display_hex 64,t#argname
			;---		display 13,10
			}

		OWN equ MFT_OWNERDRAW
		DIF	equ MIIM_DATA or MIIM_ID or MIIM_FTYPE
		ISS equ MIIM_ID or MIIM_SUBMENU or MIIM_STRING
		RJU equ MFT_RIGHTJUSTIFY

		align 8
		@mni MI_SEP,0,MFT_SEPARATOR,0
		;---		@mni MI_MBREAK,0,MFT_MENUBARBREAK, MIIM_TYPE

		@mnp MP_WSPACE,  -1,0,ISS
			@mni MI_WS_LOAD,9,OWN,DIF

			@mni MI_WS_NEW,	0,OWN,DIF
			@mni MI_FI_IMP, 6,OWN,DIF
			@mni MI_FI_NEWF,1,OWN,DIF
			@mni MI_ED_LNK,		8,OWN,DIF
			@mni MI_ED_REMITEM,0,OWN,DIF

			@mni MI_WS_SAVE,3,OWN,DIF
			@mni MI_WS_EXIT,7,OWN,DIF

		@mnp MP_FILE,  -1,0,ISS
			@mni MI_FI_OPEN,4,OWN,DIF
			@mni MI_FI_NEWB,0,OWN,DIF
			@mni MI_FI_SAVE,2,OWN,DIF
			@mni MI_FI_CLOSE,5,OWN,DIF
			@mnp MP_FI_CMD,17,OWN,DIF or MIIM_SUBMENU

		@mnp MP_EDIT,  -1,0,ISS
			@mnp MP_SCI, -1,OWN,DIF or MIIM_SUBMENU
				@mni MI_SCI_RELSCICLS,	0,OWN,DIF
				@mni MI_SCI_COMML,	0,OWN,DIF
				@mni MI_SCI_UNCOMML,	0,OWN,DIF

		@mnp MP_CONF,  -1,0,ISS
			@mni MI_CONF_KEY,	14,OWN,DIF
			@mnp MP_LANG,13,OWN,DIF or MIIM_SUBMENU
			@mnp MP_DEVT,11,OWN,DIF or MIIM_SUBMENU
				@mni MI_DEVT_ADD,	10,OWN,DIF
				@mni MI_DEVT_REM,	12,OWN,DIF
				@mni MI_DEVT_ADDG, 0,OWN,DIF
				@mni MI_DEVT_REMG, 0,OWN,DIF
			@mni MI_CONF_RELCMDS,0,OWN,DIF

		@mnp MP_UPD,   0,OWN,DIF or MIIM_SUBMENU
				@mni MI_UPD_LANG,	15,OWN,DIF

		@mnp MP_PATH,  -1,RJU,ISS or MIIM_FTYPE
			@mni MI_PA_BROWSE,	20,OWN,DIF
			@mni MI_PA_CONS,		18,OWN,DIF

			;---@mni MI_PA_SETPROP,		0,OWN,DIF
			;---	MP_WSPACE,		1,MFS_DISABLED,MIIM_STATE or MIIM_STRING
			;---	UZ_EDIT_PANE,1,MFS_DISABLED,MIIM_STATE or MIIM_STRING

			@mnp MT_WSP,  -1,0,ISS
			@mnp MT_FILE, -1,0,ISS
			@mnp MT_SECT, -1,0,ISS

		;--- generic start ownerdraw command item
		;---		@mni MI_CMDG,16,OWN,DIF or MIIM_SUBMENU
		;---		@mni MI_CMD,17,OWN,DIF

		@mni MI_CMDI,0,OWN,DIF



		display "--- Size of data "
		display_decimal $-$$
		display 13,10



