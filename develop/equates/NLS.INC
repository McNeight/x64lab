define GEOID_NOT_AVAILABLE (-1)
define LOCALE_NAME_MAX_LENGTH 85 ;--- num codepoints
define MAX_LEADBYTES   12
define MAX_DEFAULTCHAR 2
define LOCALE_ALL 0x00
define LOCALE_NOUSEROVERRIDE   0x80000000
define LOCALE_USE_CP_ACP   0x40000000
define LOCALE_RETURN_NUMBER    0x20000000
define LOCALE_RETURN_GENITIVE_NAMES  0x10000000
define LOCALE_ILANGUAGE    1
define LOCALE_SLANGUAGE    2
define LOCALE_SENGLANGUAGE 0x1001
define LOCALE_SABBREVLANGNAME  3
define LOCALE_SNATIVELANGNAME  4
define LOCALE_ICOUNTRY 5
define LOCALE_SCOUNTRY 6
define LOCALE_SENGCOUNTRY  0x1002
define LOCALE_SABBREVCTRYNAME  7
define LOCALE_SNATIVECTRYNAME  8
define LOCALE_IDEFAULTLANGUAGE 9
define LOCALE_IDEFAULTCOUNTRY  10
define LOCALE_IDEFAULTCODEPAGE 11
define LOCALE_IDEFAULTANSICODEPAGE 0x1004
define LOCALE_IDEFAULTMACCODEPAGE 0x1011
define LOCALE_SLIST    12
define LOCALE_IMEASURE 13
define LOCALE_SDECIMAL 14
define LOCALE_STHOUSAND    15
define LOCALE_SGROUPING    16
define LOCALE_IDIGITS  17
define LOCALE_ILZERO   18
define LOCALE_INEGNUMBER   0x1010
define LOCALE_SNATIVEDIGITS    19
define LOCALE_SCURRENCY    20
define LOCALE_SINTLSYMBOL  21
define LOCALE_SMONDECIMALSEP   22
define LOCALE_SMONTHOUSANDSEP  23
define LOCALE_SMONGROUPING 24
define LOCALE_ICURRDIGITS  25
define LOCALE_IINTLCURRDIGITS  26
define LOCALE_ICURRENCY    27
define LOCALE_INEGCURR 28
define LOCALE_SDATE    29
define LOCALE_STIME    30
define LOCALE_SSHORTDATE   31
define LOCALE_SLONGDATE    32
define LOCALE_STIMEFORMAT  0x1003
define LOCALE_IDATE    33
define LOCALE_ILDATE   34
define LOCALE_ITIME    35
define LOCALE_ITIMEMARKPOSN    0x1005
define LOCALE_ICENTURY 36
define LOCALE_ITLZERO  37
define LOCALE_IDAYLZERO    38
define LOCALE_IMONLZERO    39
define LOCALE_S1159    40
define LOCALE_S2359    41
define LOCALE_ICALENDARTYPE    0x1009
define LOCALE_IOPTIONALCALENDAR    0x100B
define LOCALE_IFIRSTDAYOFWEEK  0x100C
define LOCALE_IFIRSTWEEKOFYEAR 0x100D
define LOCALE_SDAYNAME1    42
define LOCALE_SDAYNAME2    43
define LOCALE_SDAYNAME3    44
define LOCALE_SDAYNAME4    45
define LOCALE_SDAYNAME5    46
define LOCALE_SDAYNAME6    47
define LOCALE_SDAYNAME7    48
define LOCALE_SABBREVDAYNAME1  49
define LOCALE_SABBREVDAYNAME2  50
define LOCALE_SABBREVDAYNAME3  51
define LOCALE_SABBREVDAYNAME4  52
define LOCALE_SABBREVDAYNAME5  53
define LOCALE_SABBREVDAYNAME6  54
define LOCALE_SABBREVDAYNAME7  55
define LOCALE_SMONTHNAME1  56
define LOCALE_SMONTHNAME2  57
define LOCALE_SMONTHNAME3  58
define LOCALE_SMONTHNAME4  59
define LOCALE_SMONTHNAME5  60
define LOCALE_SMONTHNAME6  61
define LOCALE_SMONTHNAME7  62
define LOCALE_SMONTHNAME8  63
define LOCALE_SMONTHNAME9  64
define LOCALE_SMONTHNAME10 65
define LOCALE_SMONTHNAME11 66
define LOCALE_SMONTHNAME12 67
define LOCALE_SMONTHNAME13 0x100E
define LOCALE_SABBREVMONTHNAME1    68
define LOCALE_SABBREVMONTHNAME2    69
define LOCALE_SABBREVMONTHNAME3    70
define LOCALE_SABBREVMONTHNAME4    71
define LOCALE_SABBREVMONTHNAME5    72
define LOCALE_SABBREVMONTHNAME6    73
define LOCALE_SABBREVMONTHNAME7    74
define LOCALE_SABBREVMONTHNAME8    75
define LOCALE_SABBREVMONTHNAME9    76
define LOCALE_SABBREVMONTHNAME10   77
define LOCALE_SABBREVMONTHNAME11   78
define LOCALE_SABBREVMONTHNAME12   79
define LOCALE_SABBREVMONTHNAME13   0x100F
define LOCALE_SPOSITIVESIGN    80
define LOCALE_SNEGATIVESIGN    81
define LOCALE_SSCRIPTS         108
define LOCALE_IPOSSIGNPOSN 82
define LOCALE_INEGSIGNPOSN 83
define LOCALE_IPOSSYMPRECEDES  84
define LOCALE_IPOSSEPBYSPACE   85
define LOCALE_INEGSYMPRECEDES  86
define LOCALE_INEGSEPBYSPACE   87
define LOCALE_FONTSIGNATURE    88
define LOCALE_SISO639LANGNAME  89
define LOCALE_SISO3166CTRYNAME 90
define LOCALE_SNAME            92
define LOCALE_SSCRIPTS 108
define LOCALE_SYSTEM_DEFAULT   0x800
define LOCALE_USER_DEFAULT 0x400
define LOCALE_IREADINGLAYOUT       0x0070
define LOCALE_INEUTRAL             0x0071

define LOCALE_SLOCALIZEDDISPLAYNAME  0x00000002   ;// localized name of locale, eg "German (Germany)" in UI language
define LOCALE_SENGLISHDISPLAYNAME    0x00000072   ;// Display name (language + country usually) in English, eg "German (Germany)"
define LOCALE_SNATIVEDISPLAYNAME     0x00000073   ;// Display name in native locale language, eg "Deutsch (Deutschland)
define LOCALE_SLOCALIZEDLANGUAGENAME 0x0000006f   ;// Language Display Name for a language, eg "German" in UI language
define LOCALE_SENGLISHLANGUAGENAME   0x00001001   ;// English name of language, eg "German"
define LOCALE_SNATIVELANGUAGENAME    0x00000004   ;// native name of language, eg "Deutsch"
define LOCALE_SLOCALIZEDCOUNTRYNAME  0x00000006   ;// localized name of country, eg "Germany" in UI language

define LOCALE_ALLOW_NEUTRAL_NAMES 0x08000000
