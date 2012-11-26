;---/**
;--- * @file adapted for fasm. original from
;--- * @author  James Brown
;--- * @version 1.0
;--- *
;--- * Copyright (C) 2012 James Brown
;--- * Please refer to the file LICENCE.TXT for copying permission
;--- * HexView win32 control
;--- * www.catch22.net
;--- */

;--- * HexView styles
;--- *
;--- * Set using the HexView_SetStyle message
;--- * 
;--- *	Be sure to update the HVS_xxx_MASK values if you change anything!!
;--- */
;---//! Hex column styles

HVS_FORMAT_HEX	equ	0x0000		;--- // hex format is the default
HVS_FORMAT_DEC	equ		0x0001		;--- // decimal formatting
HVS_FORMAT_OCT	equ		0x0002		;--- // octal formatting
HVS_FORMAT_BIN	equ		0x0003		;--- // binary formatting
HVS_FORMAT_MASK	equ	0x0003

;---/! Address column styles
HVS_ADDR_HEX	equ		0x0000		;--- // hex address (default)
HVS_ADDR_VISIBLE	equ	0x0000	;--- 	// visible (default)
HVS_ADDR_DEC	equ		0x0004		;--- // decimal address 
HVS_ADDR_RESIZING	equ	0x0008		;--- // auto resize address
HVS_ADDR_ENDCOLON	equ	0x0010		;--- // place a colon : at the end of the address
HVS_ADDR_MIDCOLON	equ	0x0020		;--- // place a colon in middle (hex address only)
HVS_ADDR_INVISIBLE	equ	0x0040		;--- // hide the address
HVS_ADDR_MASK	equ		0x007C

;---* // grouping now specified via HVM_SETGROUPING message
HVS_WIDTH_BYTE	equ		0x0000		;--- // single-byte grouping is default
HVS_WIDTH_WORD	equ		0x0100		;--- // word (16bit) grouping of bytes
HVS_WIDTH_DWORD	equ		0x0200	;--- 	// dword (32bit) grouping
HVS_WIDTH_MASK	equ		0x0300*/

;---/ Endian display mode (for hex column, with grouping enabled)
HVS_ENDIAN_LITTLE	equ	0x0000	;--- 	// little endian is default
HVS_ENDIAN_BIG	equ		0x0400		;--- // big endian (only when WORD/DWORD grouping)
HVS_ENDIAN_MASK	equ		0x0400

;---/ Ascii column styles
HVS_ASCII_VISIBLE	equ	0x0000		;--- // visible (default)
HVS_ASCII_SHOWCTRLS	equ	0x0800	;--- 	// show control (0-31) chars
HVS_ASCII_SHOWEXTD	equ	0x1000		;--- // show extended chars (128-255)
HVS_ASCII_INVISIBLE	equ 0x2000		;--- // hide the ascii display
HVS_ASCII_MASK	equ		0x3800

;---/ Basic HexView control styles
HVS_FORCE_FIXEDCOLS	equ 0x80		;--- // force whole-sized hex columns
HVS_FIXED_EDITMODE	equ  0x0100	;--- 	// prevent user from using INSERT to change edit mode
HVS_DISABLE_UNDO	equ	0x0200		;--- // prevent undo/redo functionality
HVS_ALWAYSDELETE	equ	0x4000		;--- // backspace/delete work even in OVR mode
HVS_HEX_INVISIBLE	equ   0x8000	;--- 	// hide the hex display
HVS_UPPERCASEHEX	equ	0x000000	;--- // hex characters (A-F) are upper-case (default)
HVS_LOWERCASEHEX	equ	0x010000	;--- // hex characters (A-F) are lower-case
HVS_FITTOWINDOW	equ		0x020000	;--- // adjust columns to fit in window		
HVS_SHOWMODS	equ		0x040000	;--- // show modifications to the file
HVS_REPLACESEL	equ		0x080000	;--- // typing replaces selection
HVS_ENABLEDRAGDROP	equ	0x100000	;--- // enable drag-and-drop
HVS_INSERTMODEDEF	equ	0x200000	;--- // insert mode is default (replace is usually)
HVS_LINKDROPFILES	equ	0x400000	;--- // link any files dropped from explorer (default)
HVS_BRINGTOTOP	equ		0x800000	;--- // bring window to foreground during drag+drop

;---/ Editing styles
HVS_OVERSTRIKE	equ		0x0000000	;--- // overstrike (default)
HVS_INSERT	equ			0x1000000	;--- // insertion
HVS_READONLY	equ		0x2000000	;--- // readonly (no editing)
HVS_QUICKSAVE	equ		0x4000000	;--- // quicksave

HVS_HEXPANE	equ			0x0000000	;--- // cursor in hex pane (default)
HVS_ASCPANE	equ			0x8000000	;--- // cursor in ascii pane

HVS_ALWAYSVSCROLL	equ   0x10000000
HVS_ALWAYSHSCROLL	equ   0x20000000
HVS_RESIZEBAR	equ	    0x40000000
HVS_INVERTSELECTION	equ 0x80000000

;---/ Editing mode
HVMODE_READONLY	equ			0		;--- 	// readonly (no editing)
HVMODE_INSERT	equ			1			;--- // insertion
HVMODE_OVERWRITE	equ		2			;--- // overstrike (default)
HVMODE_QUICKSAVE	equ		0x4000000	;--- // quicksave

;---/
;---/	HexView_OpenFile flags
;---/
HVOF_DEFAULT	equ			0
HVOF_READONLY	equ			1		;--- 	// open the file as read-only
HVOF_QUICKLOAD	equ			2		;--- 	// enable quickload - keep file on disk + use minimal memory
HVOF_QUICKSAVE	equ			4		;--- 	// enable quicksave - only writes modified portions of a file to disk
HVOF_AUTOQUICKLOAD	equ		(8 or HVOF_QUICKLOAD) ;--- // always quickload for larger files

;---/
;---/	HexView_Bookmark flags
;---/
HVBF_DEFAULT	equ			0
HVBF_NOPERSIST	equ			1	;--- // mark as non-persistant
HVBF_NOBOOKNOTE	equ			2	;--- // don't display the note-tab
HVBF_NOENUM	equ				4	;--- // don't return in bookmark enumerations

;---*
;---*	HexView_Find flags
;---*/
HVFF_SCOPE_ALL	equ			0
HVFF_SCOPE_SELECTION	equ	1
HVFF_CASE_INSENSITIVE	equ	2

;---*
;---*	Colour support
;---*  Modify the colour palete using the HexView_SetColor message
;---*/
HVC_BACKGROUND	equ	0			;--- ///< normal background colour
HVC_SELECTION	equ  1	;--- 		///< selection background colour
HVC_SELECTION2	equ 2	;--- 		//! secondary selection background colour
HVC_ADDRESS	equ		3			;--- //! address text
HVC_HEXODD	equ			4			;--- //! odd column text
HVC_HEXODDSEL	equ	5			;--- //! odd selected text
HVC_HEXODDSEL2	equ	6			;--- //! odd selected text (secondary)
HVC_HEXEVEN	equ		7			;--- //! even column text
HVC_HEXEVENSEL	equ	8			;--- //! even selected text
HVC_HEXEVENSEL2	equ	9		;--- 	//! even selected text (secondary
HVC_ASCII	equ			10			;--- //! ascii text
HVC_ASCIISEL	equ		11			;--- //! ascii selection text
HVC_ASCIISEL2	equ	12		;--- 	//! ascii selection text
HVC_MODIFY	equ			13			;--- //! modified bytes colour
HVC_MODIFYSEL	equ	14		;--- 	//! modified bytes selected
HVC_MODIFYSEL2	equ	15		;--- 	//! modified bytes selected
HVC_BOOKMARK_FG	equ	16	;--- 		//! bookmarks
HVC_BOOKMARK_BG	equ	17	;--- 		//! bookmarks
HVC_BOOKSEL	equ			18		;--- 	//! selected bookmark
HVC_RESIZEBAR	equ		19		;--- 	//! resizing bar
HVC_SELECTION3	equ   20	;--- 		//! secondary selection background colour
HVC_SELECTION4	equ		21
HVC_MATCHED	equ			22		;--- 	//! matched pattern background
HVC_MATCHEDSEL	equ		23		;--- 	//! selected pattern match			
HVC_MATCHEDSEL2	equ	24	;--- 		//! selected pattern match (secondary)
HVC_MAX_COLOURS	equ	25

HEX_GET_COLOR	equ		0x00ffffff	;--- // mask to 
HEX_SYS_COLOR	equ		0x80000000	;--- // top bit in a COLORREF indicates that it is a COLOR_xx index 

;---/ create a HexView color based on one of the GetSysColor COLOR_* system color codes
;---/ the resulting
;---define HEX_SYSCOLOR(code) (HEX_SYS_COLOR | (code))	

;---/ Find (realise) the real colour
;---/ an RGB value will not have the top byte set to anything,
;---/ so we can tell if we have a specific colour or not.
;---/ we can set the top byte to a meaningful value to indicate
;---/ that we are using a system colour - just mask the low triple
;---/ bytes to get the COLOR_* value
;---define HexView_RealiseColour(cr) (((cr) & HEX_SYS_COLOR) ? GetSysColor((cr) & HEX_GET_COLOR) : (cr))


;---*
;---*	HexView-specific messages that can be sent to a HexView control
;---*  using the SendMessage API
;---*
;---*  Refer to the corresponding HexView_xxx message macros at the bottom of
;---*  this file for details about what parameters each message takes.
;---*
;---*/

HVM_FIRST equ WM_USER

HVM_HIGHLIGHT	equ		(HVM_FIRST + 2)
HVM_GETCURPOS	equ		(HVM_FIRST + 3)
HVM_GETSELSTART	equ		(HVM_FIRST + 4)
HVM_GETSELEND	equ		(HVM_FIRST + 5)
HVM_GETSELSIZE	equ		(HVM_FIRST + 6)
HVM_SETSEARCHPAT	equ	(HVM_FIRST + 7)
HVM_GETDATACUR	equ		(HVM_FIRST + 8)
HVM_SETDATACUR	equ		(HVM_FIRST + 9)
;---/#define HVM_INSERTDATA		(HVM_FIRST + 10)
;---/#define HVM_REPLACEDATA		(HVM_FIRST + 11)
HVM_ERASEDATA	equ		(HVM_FIRST + 12)
HVM_UNDO	equ			(HVM_FIRST + 13)
HVM_REDO	equ			(HVM_FIRST + 14)

HVM_SETSTYLE	equ		(HVM_FIRST + 0)
HVM_SETGROUPING	equ		(HVM_FIRST + 1)

HVM_SETEDITMODE	equ		(HVM_FIRST + 15)
HVM_GETEDITMODE	equ		(HVM_FIRST + 16)
HVM_OPENFILE equ	HVM_FIRST + 17
HVM_SAVEFILE	equ		(HVM_FIRST + 18)
HVM_SELECTALL	equ		(HVM_FIRST + 19)
HVM_CANUNDO		equ		(HVM_FIRST + 20)
HVM_CANREDO	equ			(HVM_FIRST + 21)
HVM_SETCONTEXTMENU	equ  (HVM_FIRST + 22)
HVM_CLEAR	equ			(HVM_FIRST + 23)
HVM_ADDBOOKMARK	equ		(HVM_FIRST + 24)
HVM_CLEARBOOKMARKS	equ	(HVM_FIRST + 25)
HVM_GETBOOKMARK	equ		(HVM_FIRST + 26)
HVM_SETBOOKMARK	equ		(HVM_FIRST + 27)
HVM_SETCURPOS	equ		(HVM_FIRST + 28)
HVM_SETSELSTART	equ		(HVM_FIRST + 29)
HVM_SETSELEND	equ		(HVM_FIRST + 30)
HVM_SCROLLTO	equ		(HVM_FIRST + 31)
HVM_GETSTYLE	equ		(HVM_FIRST + 32)
HVM_GETGROUPING	equ		(HVM_FIRST + 33)
HVM_FORMATDATA	equ		(HVM_FIRST + 34)
HVM_GETLINELEN	equ		(HVM_FIRST + 35)
HVM_SETLINELEN	equ		(HVM_FIRST + 36)
HVM_ISDRAGLOOP	equ		(HVM_FIRST + 37)
HVM_GETDATAADV	equ		(HVM_FIRST + 38)
HVM_SETDATAADV	equ		(HVM_FIRST + 39)
HVM_GETFILESIZE	equ		(HVM_FIRST + 40)
HVM_FINDINIT	equ		(HVM_FIRST + 41)
HVM_FINDNEXT	equ		(HVM_FIRST + 42)
HVM_FINDPREV	equ		(HVM_FIRST + 43)
HVM_FINDCANCEL	equ		(HVM_FIRST + 44)
HVM_GETFILEHANDLE	equ	(HVM_FIRST + 45)
HVM_GETCURPANE	equ		(HVM_FIRST + 46)
HVM_SETCURPANE	equ		(HVM_FIRST + 47)
HVM_GETFILENAME	equ		(HVM_FIRST + 48)
HVM_ISREADONLY	equ		(HVM_FIRST + 49)
HVM_GETCURCOORD		equ	(HVM_FIRST + 50)
HVM_REVERT	equ			(HVM_FIRST + 51)
HVM_FILLDATA	equ		(HVM_FIRST + 52)
HVM_IMPORTFILE	equ		(HVM_FIRST + 53)
HVM_DELBOOKMARK	equ		(HVM_FIRST + 54)
HVM_ENUMBOOKMARK	equ	(HVM_FIRST + 55)
HVM_INITBUF	equ			(HVM_FIRST + 56)
HVM_INITBUF_SHARED	equ  (HVM_FIRST + 57)
HVM_SETFONTSPACING	equ  (HVM_FIRST + 58)
HVM_SETCOLOR	equ		(HVM_FIRST + 59)
HVM_GETCOLOR	equ		(HVM_FIRST + 60)
HVM_SETPADDING	equ		(HVM_FIRST + 61)
;---/#define HVM_GETPADDING		(HVM_FIRST + 62)
HVM_SETADDROFFSET	equ   (HVM_FIRST + 63)
HVM_SCROLLTOP	equ       (HVM_FIRST + 64)
HVM_GETLINECHARS	equ	(HVM_FIRST + 65)


;---/
;---/	HexView notifications
;---/	sent via the WM_NOTIFY message
;---/

HVN_BASE	equ				(WM_USER)
HVN_CURSOR_CHANGE	equ		(HVN_BASE + 0)  ;--- // the cursor has changed location
HVN_SELECTION_CHANGE	equ	(HVN_BASE + 1)  ;--- // the selection has changed
HVN_EDITMODE_CHANGE	equ		(HVN_BASE + 2);---   // the edit mode (insert/delete/readonly) has changed
HVN_CHANGED	equ				(HVN_BASE + 3)  ;--- // the file content has changed (see NMHVCHANGED structure)
HVN_ESCAPE	equ				(HVN_BASE + 4)  ;--- // the escape key was pressed
HVN_PROGRESS	equ			(HVN_BASE + 5)  ;--- // NMHVPROGRESS
HVN_BOOKCLOSE	equ			(HVN_BASE + 6) ;---  // a bookmark has been closed
HVN_CONTEXTMENU		equ		(HVN_BASE + 7)  ;--- // the context menu is being displayed
