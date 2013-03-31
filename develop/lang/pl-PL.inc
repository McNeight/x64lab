  
  ;#-------------------------------------------------ß
  ;|          lang MPL 2.0 License                   |
  ;|   Copyright (c) 2011-2012, Marc Rainer Kranz.   |
  ;|            All rights reserved.                 |   
  ;|                                                 |
  ;|   Polish language extention by Tomasz Ziajko    |
  ;|                First draft                      |
  ;ö-------------------------------------------------ä

  ;#-------------------------------------------------ß
  ;| uft-8 encoded üäößąćęłńśóźż
  ;| update: 29-09-2012 13:11
  ;| filename:lang_pl.inc
  ;ö-------------------------------------------------ä

	include "%x64devdir%/ide/x64lab.equ"
	include '%x64devdir%/shared/win64w_mrk.inc'
	include "%x64devdir%/macro/mrk_macrow.inc"
	include "lang.inc"

	@make_lang "pl-PL",0415h,\
		db ";*(no transl)",\
		UZ_ERR_NOFILE,db "Nie można odnaleźć wybranego pliku",\
		UZ_HOME,db "http://sites.google.com/site/x64lab/",\
		UZ_CONS_WIN,db "Konsola",\
    UZ_EDIT_PANE,db "Panel Edycji",\
    UZ_EDIT_UNTL,db "00_buffer.untitled",\
    UZ_ERR_NODIR,db "Lokalizacja nie istnieje",\
    UZ_WSPACE,db "x64lab Przestrzeń Robocza",\
    UZ_CURDIR,db "Aktualna lokalizacja",\
    UZ_FSAVE,db "Zapisz plik ",\
    UZ_MPWIN,db "Uniwersalny",\
		UZ_CPPROCS,db "Działający Proces",\
    UZ_CPDIRS,db "Pliki i foldery",\
    UZ_CPNOSEL,db "Brak zaznaczenia",\
		UZ_INFO_UTF8,db ";--- Uwaga!! utf8 bez BOM'u äöüßąćęłńśóźż",\
		UZ_INFO_TOP,db ";--- TOP format file for x64lab",\
		UZ_INFO_COPYR,db ";--- Copyright Marc Rainer Kranz 2009-2012",\
		UZ_INFO_CDATE,db "Cstamp",\
		UZ_INFO_SIZE,db "Rozmiar",\
		UZ_INFO_TYPE,db "Typ",\
		UZ_INFO_BUF,db "Nazwa",\
		UZ_INFO_SELITEM,<db \
			"Proszę wybrać pozycję z drzewa w Przestrzeni Roboczej,",13,10,\
			"nowe komponenty zostaną dodane.">,\
		UZ_OK,db "Ok",\
		UZ_NO,db "Nie",\
		UZ_CANCEL,db "Anuluj",\
		UZ_IO_SELDPF,db "Wybierz miejsce przeznaczenia oraz nazwę pliku",\
		UZ_IO_DPATH,db "(*) Dest. path",\
		UZ_IO_KDIR,db "Znane ścieżki",\
		UZ_IO_DFNAME,db "Dest. filename",\
		UZ_IO_EXT,db "nazwapliku.ext",\
		UZ_WSP_EXT,db "nazwapliku.x64lab",\
		UZ_OVERWFILE,db "Plik o wybranej nazwie już istnieje. Nadpisać ?",\
		UZ_COURNEW,db "Courier New",\
		UZ_IO_NEWWSP,db "Stwórz nową Przestrzeń Roboczą",\
		UZ_IO_SAVEWSP,db "Zapisz aktualną Przestrzeń Roboczą",\
		UZ_TOOLCMD,db "Komendy Narzędzi",\
		UZ_TOOLDESCR,db "Wybierz plik wykonywalny/wsadowy/pomoc itp.",\
		UZ_TOOLBYG,db "[Narzędzia według Grup]",\
		UZ_TOOLPICK,db "Wybierz Narzędzie",\
		MP_WSPACE,db "Work&space",\
			MI_WS_LOAD,db "&Wczytaj",\
			MI_WS_NEW,db "&Nowy",\
			MI_WS_ADD,db "Add &Project",\
			MI_WS_BACK,db "&Backup",\
			MI_WS_EXP,db "E&xport to archive",\
			MI_WS_SAVE,db "Zapisz wszystko",\
			MI_WS_SAVET,db "Zapisz jako szablon",\
			MI_WS_RECODE,db "Encode...",\
			MP_WS_REC,db "Ostatnia Przestrzeń Robocza",\
			MI_WS_EXIT,db "Wyjdź",\
		MP_FILE,db "&File",\
			MI_FI_OPEN,db "Otwórz dokumenty",\
			MI_FI_NEWB,db "Nowy pusty dokument",\
			MI_FI_NEWF,db "Nowy plik",\
			MI_FI_IMP,db "Zaimportuj do przestrzeni roboczej",\
			MI_FI_CLOSE,db "Zamknij dokument",\
			MI_FI_CCOPY,db "Stwórz kopię",\
			MI_FI_SAVE,db "Zapisz aktualny plik",\
			MI_FI_SAVEAS,db "Zapisz jako",\
			MI_FI_ENCO,db "Zakoduj aktualny",\
			MI_FI_BACK,db "Kopia zapasowa jako",\
		MP_EDIT,db "Edytuj",\
			MI_ED_LNK,db "Wstaw nowe inteligente łącze",\
			MI_ED_REMITEM,db "Usuń obiekt z Przestrzeni Roboczej",\
		MP_CONF,db "C&onfigure",\
		MI_CONF_KEY,db "Przypisanie klawiszy",\
			MP_LANG,db "Language",\
		MP_DEVT,db "Narzędzia Programisty",\
			MI_DEVT_ADD,db "Przeglądaj aby dodać nowe narzędzie",\
			MI_DEVT_ADDG,db "Dodaj nową etykietę GRUPA",\
			MI_DEVT_REM,db "Usuń narzędzie",\
			MI_DEVT_REMG,db "Usuń GRUPĘ",\
		MP_SCI,db "Scintilla",\
			MI_SCI_COMML,db "Zakomentuj linie",\
			MI_SCI_COMMB,db "Zakomentuj bloki",\
			MI_SCI_UNCOMML,db "Usuń komentarze w liniach",\
			MI_SCI_UNCOMMB,db "Usuń komentarze w blokach",\
			MI_SCI_RELSCICLS,db "Reload Scintilla classes",\
		MP_UPD,db "(*) Update",\
			MI_UPD_LANG,db "(*) Language update (script)",\
		MP_PATH,db "[?]",\
			MI_PA_CONS,db "Otwórz konsolę tutaj",\
			MI_PA_BROWSE,db "Przeglądaj",\
			MI_PA_FIND,db "Szukaj tutaj",\
			MI_PA_COPY,db "Skopiuj tą ścieżkę",\
			MI_PA_SETPROP,db "Włącz przeglądanie",\
			BB_NULL,db "Przeglądaj według kategorii",\
			BB_WSP,db "Przestrzeń robocza i pliki",\
			BB_FOLDER,db "Folder",\
			BB_CODE,db "Kod",\
			BB_CALL,db "Wywołanie",\
			BB_COMMENT,db "Komentarze",\
			BB_DATA,db "Ilości danych",\
			BB_EXPORT,db "Wyeksportowane funkcje",\
			BB_FLOW,db "Przepływ",\
			BB_IMM,db "Zmienne bezpośrednie",\
			BB_IMPORT,db "Zaimportowane funkcje",\
			BB_LABEL,db "Etykiety",\
			BB_MACRO,db "Makro",\
			BB_PROC,db "Procs and Calleé",\
			BB_PROCESS,db "Procesy",\
			BB_REG,db "Rejestry",\
			BB_RET,db "Powroty",\
			BB_SYS,db "System",\
			UZ_DESCR,db "Opis",\
			UZ_INFO_LNK,db "Stwórz nowe Inteligentne Łącze",\
			UZ_LNK_NAME,db "Nazwa Inteligentnego Łącza",\
			UZ_LNK_MAP,db "mapped by",\
			UZ_LNK_DESC,db "Wybierz lokalizację jako odniesienie",\
			UZ_DATEFRM,db "dddd','dd'.'MMMM'.'rrrr",\
			UZ_TIMEFRM,db "gg':'mm':'ss",\
			UZ_DEFUSER,db "Mr.Biberkopf",\
			UZ_TOOLGEN,db "Narzędzia wszystkich zastosowań",\
			UZ_MSG_U_TGREM,<db \
				"Usunięcie grupy [%ls] jest nieodwracalne. ",13,10,\
				"Narzędzia, które zawiera, również zostaną usunięte !",13,10,\
				"Usunąć trwale ?">,\
			UZ_MSG_TADDG,db "(*) Type something, press <enter> to create a Group",\
			UZ_MSG_SCIREL,<db \
				"Po zapisaniu plików klas Scintilli, proszę zamknąć i otworzyć ponownie",13,10,\
        "aktualny edytor również otwiera pliki w kolejności",13,10,\
        "aby wybrać zmiany koloru składni">,\
			UZ_MSG_REMITEM,<db \
				"Uwaga: Pozycja w Przestrzeni Roboczej zawiera sub-pozycje. Usunięcie jej",13,10,\
        "spowoduje również usunięcie zawieranych przez nią sub-pozycji. Jest to nieodwracalne.",13,10,\
        "Usunąć pozycję oraz jej sub-pozycje?">,\
			UZ_REBUILD,db "Przebuduj",\
			UZ_SET,db " Ustaw",\
			\;--- Courier New doesent have glyphs for the 3 circ. encl. c,a,s
			\;--- http://en.wikipedia.org/wiki/Enclosed_alphanumerics
			UZ_CTRL,db "(ⓒ) Ctrl",\
			UZ_ALT,db "(ⓐ) Alt",\
			UZ_SHIFT,db "(ⓢ) Shift",\
			\;---------------------------------------------------------------------
			UZ_NOINV,db "Nie ma odwrócenia",\
			UZ_NOTASS,db "Nie ma wyznaczonego zadania",\
			UZ_WZERO,db "0000",\
			UZ_RESTART,db "Please restart x64lab to apply change. Close it now ?",\
			UZ_MSG_LNK,<db "(*) The selected treeitem is empty.",13,10,\
				"Add this smartlink as its first child item ?">,\
			UZ_TEMPLATE,db "(*)Ready templates",\
			UZ_TMPL_MOD,db "(*) Bare-module templates"

			;---			MI_DEVT_MAN,db "Zarządzanie plikiem narzędzi (dla zaawansowanych Urzytkowników)",\
			;---			MI_DEVT_REL,db "Przeładuj Narzędzia",\
