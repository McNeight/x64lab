  
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

	include "%x64devdir%/ide/x64lab.equ"
	include '%x64devdir%/shared/win64w_mrk.inc'
	include "%x64devdir%/macro/mrk_macrow.inc"
	include "lang.inc"

	@make_lang "en-US",0409h,\
		db ";*(no transl)",\
		UZ_ERR_NOFILE,db "Cannot find specified file",\
		UZ_HOME,db "http://sites.google.com/site/x64lab/",\
		UZ_CONS_WIN,db "Console",\
    UZ_EDIT_PANE,db "Editor Panel",\
    UZ_EDIT_UNTL,db "00_buffer.untitled",\
    UZ_ERR_NODIR,db "Directory does not exist",\
    UZ_WSPACE,db "x64lab Workspace",\
    UZ_CURDIR,db "Current directory",\
    UZ_FSAVE,db "Save file ",\
    UZ_MPWIN,db "Multipurpose",\
		UZ_CPPROCS,db "Running Processes",\
    UZ_CPDIRS,db "Files and folders",\
    UZ_CPNOSEL,db "No selection",\
		UZ_INFO_UTF8,db ";--- Warning!! utf8 no-BOM äöüß",\
		UZ_INFO_TOP,db ";--- TOP format file for x64lab",\
		UZ_INFO_COPYR,db ";--- Copyright Marc Rainer Kranz 2009-2012",\
		UZ_INFO_CDATE,db "Cstamp",\
		UZ_INFO_SIZE,db "Size",\
		UZ_INFO_TYPE,db "Type",\
		UZ_INFO_BUF,db "Name",\
		UZ_INFO_SELITEM,<db \
			"Please select a treeitem from the Workspace",13,10,\
			"after which new stuff will be inserted.">,\
		UZ_OK,db "Ok",\
		UZ_NO,db "No",\
		UZ_CANCEL,db "Cancel",\
		UZ_IO_SELDPF,db "Select destination path and filename",\
		UZ_IO_DPATH,db "Dest. path",\
		UZ_IO_KDIR,db "Known paths",\
		UZ_IO_DFNAME,db "Dest. filename",\
		UZ_IO_EXT,db "filename.ext",\
		UZ_WSP_EXT,db "filename.x64lab",\
		UZ_OVERWFILE,db "File exists already. Overwrite ?",\
		UZ_COURNEW,db "Courier New",\
		UZ_IO_NEWWSP,db "Create a new Workspace",\
		UZ_IO_SAVEWSP,db "Save current Workspace",\
		UZ_TOOLCMD,db "Tool command",\
		UZ_TOOLDESCR,db "Select executable/batch/help file etc.",\
		UZ_TOOLBYG,db "[Tools listed by Groups]",\
		UZ_TOOLPICK,db "Pick tool",\
		MP_WSPACE,db "Work&space",\
			MI_WS_LOAD,db "&Load",\
			MI_WS_NEW,db "&New",\
			MI_WS_ADD,db "Add &Project",\
			MI_WS_BACK,db "&Backup",\
			MI_WS_EXP,db "E&xport to archive",\
			MI_WS_SAVE,db "Save all",\
			MI_WS_SAVET,db "Save as template",\
			MI_WS_RECODE,db "Encode...",\
			MP_WS_REC,db "Recent workspaces",\
			MI_WS_EXIT,db "Exit",\
		MP_FILE,db "&File",\
			MI_FI_OPEN,db "Open documents",\
			MI_FI_NEWB,db "New blank document",\
			MI_FI_NEWF,db "New file",\
			MI_FI_IMP,db "Import into workspace",\
			MI_FI_CLOSE,db "Close doc",\
			MI_FI_CCOPY,db "Create a copy",\
			MI_FI_SAVE,db "Save current file",\
			MI_FI_SAVEAS,db "Save as",\
			MI_FI_ENCO,db "Encode current",\
			MI_FI_BACK,db "Backup as",\
		MP_EDIT,db "Edit",\
			MI_ED_LNK,db "Insert new smartlink",\
			MI_ED_REMITEM,db "Remove item from workspace",\
		MP_CONF,db "C&onfigure",\
			MI_CONF_KEY,db "Key bindings",\
		MP_LANG,db "Language",\
		MP_DEVT,db "Developer tools",\
			MI_DEVT_ADD,db "Browse to add new tool",\
			MI_DEVT_ADDG,db "Add default GROUP label",\
			MI_DEVT_REM,db "Remove tool",\
			MI_DEVT_REMG,db "Remove GROUP",\
		MP_SCI,db "Scintilla",\
			MI_SCI_COMML,db "Comment by line/s",\
			MI_SCI_COMMB,db "Comment block/s",\
			MI_SCI_UNCOMML,db "Uncomment by line/s",\
			MI_SCI_UNCOMMB,db "Uncomment block/s",\
			MI_SCI_RELSCICLS,db "Reload Scintilla classes",\
		MP_UPD,db "Update",\
			MI_UPD_LANG,db "Language update (script)",\
		MP_PATH,db "[?]",\
			MI_PA_CONS,db "Open console here",\
			MI_PA_BROWSE,db "Browse",\
			MI_PA_FIND,db "Find here",\
			MI_PA_COPY,db "Copy this path",\
			MI_PA_SETPROP,db "Set browsing",\
			BB_NULL,db "Browse by categories",\
			BB_WSP,db "Workspace and files",\
			BB_FOLDER,db "Folder",\
			BB_CODE,db "Code",\
			BB_CALL,db "Call/er",\
			BB_COMMENT,db "Comments",\
			BB_DATA,db "Data quantities",\
			BB_EXPORT,db "Exported funcs",\
			BB_FLOW,db "Flow",\
			BB_IMM,db "Immediates",\
			BB_IMPORT,db "Imported funcs",\
			BB_LABEL,db "Labels",\
			BB_MACRO,db "Macro",\
			BB_PROC,db "Procs and Calleé",\
			BB_PROCESS,db "Processes",\
			BB_REG,db "Registers",\
			BB_RET,db "Returns",\
			BB_SYS,db "System",\
			\;---------------------------------------------
			UZ_DESCR,db "Description",\
			UZ_INFO_LNK,db "Create a new smartlink",\
			UZ_LNK_NAME,db "smartlinkname",\
			UZ_LNK_MAP,db "mapped by",\
			UZ_LNK_DESC,db "Choose a directory as reference",\
			UZ_DATEFRM,db "dddd','dd'.'MMMM'.'yyyy",\
			UZ_TIMEFRM,db "HH':'mm':'ss",\
			UZ_DEFUSER,db "Mr.Biberkopf",\
			UZ_TOOLGEN,db "All purpose tools",\
			UZ_MSG_U_TGREM,<db \
				"Removing group [%ls] cannot be undone. ",13,10,\
				"Tools contained into it will be removed too !",13,10,\
				"Remove it permanently ?">,\
			UZ_MSG_TADDG,db "Type something, press <enter> to create a Group",\
			UZ_MSG_SCIREL,<db \
				"After saving class files for Scintilla, please close and reopen",13,10,\
        "current editor open files too in order",13,10,\
        "to apply syntax colour changes to them">,\
			UZ_MSG_REMITEM,<db \
				"Warning: Item in workspace contains subitems. Removing it will",13,10,\
        "remove contained subitems too. This operation cannot be undone.",13,10,\
        "Remove item and subitems too ?">,\
			UZ_REBUILD,db "Rebuild",\
			UZ_SET,db " Set",\
			\;--- Courier New doesent have glyphs for the 3 circ. encl. c,a,s
			\;--- http://en.wikipedia.org/wiki/Enclosed_alphanumerics
			UZ_CTRL,db "(ⓒ) Ctrl",\
			UZ_ALT,db "(ⓐ) Alt",\
			UZ_SHIFT,db "(ⓢ) Shift",\
			\;---------------------------------------------------------------------
			UZ_NOINV,db "No invert",\
			UZ_NOTASS,db "No assignment",\
			UZ_WZERO,db "0000",\
			UZ_RESTART,db "x64lab needs restarting. Close it now ?",\
			UZ_MSG_LNK,<db "The selected treeitem is empty.",13,10,\
				"Add this smartlink as its first child item ?">,\
			UZ_TEMPLATE,db "Ready templates",\
			UZ_TMPL_MOD,db "Bare-module templates"
			

		;---			MI_DEVT_MAN,db "Manage tools file (expert user)",\
		;---			MI_DEVT_REL,db "Reload tools",\
