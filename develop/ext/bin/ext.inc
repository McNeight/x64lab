  
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

macro @xsdbmu argstr,argresult,argprime {
	common 
	local	lo,hi,result,cpts,prime,..tmp
	argresult equ 0
	if argprime eq
		prime = 6121
	else
		prime = argprime
	end if
	virtual at 0
		..tmp:
		du argstr
		result = prime

	;--- 32 bit range ---------
	repeat $/2
		load cpts word from %*2 -2
		lo = (cpts and 0x000000FF)
		hi = (cpts and 0x0000FF00) shr 8
		result = ((lo xor hi) and 0x000000FF )+\
			((result shl 6) and 0xffffffff)+ \
			((result shl 17)  and 0xffffffff) - \
			result
	end repeat
	end virtual
	argresult equ (result and 0xffffffff)
}

EXT_BCK equ 1
EXT_3DI equ 2
EXT_AUD equ 4
EXT_CAD equ 8
EXT_CAM equ 10h
EXT_COM equ 20h
EXT_DBA equ 40h
EXT_DSK equ 80h
EXT_ENC equ 100h
EXT_EXE equ 200h
EXT_FNT equ 400h
EXT_GAM equ 800h
EXT_GIS equ 1000h
EXT_PAG equ 2000h
EXT_PLU equ 4000h
EXT_RAS equ 8000h
EXT_SET equ 10000h
EXT_SPR equ 20000h
EXT_SYS equ 40000h
EXT_VEC equ 80000h
EXT_VID equ 100000h
EXT_WEB equ 200000h
EXT_DEV equ 400000h

macro @make_dbext [argext,argtype] {
	common
	base dd 2048 dup (0)
	forward
	local tmp,res,result,len
	result equ 0
	@xsdbmu argext,result
	
	virtual
		tmp:	
		du argext
		lenext = $-tmp
	end virtual

	res:
	;--- record -------
	dd 0		;--- next in the linked list
	dd argtype
	dd result
	db lenext
	db 0
	dw 0
	du argext,0

	load ref DWORD from base+((result and 07FFh)*4)
	store DWORD res at base+((result and 07FFh)*4)
	store DWORD ref at res
}


@make_dbext \
"$$$",EXT_BCK,\
"$db",EXT_BCK,\
"$er",EXT_DBA,\
"^^^",EXT_DBA,\
"__a",EXT_BCK,\
"__b",EXT_BCK,\
"0",EXT_COM or EXT_GAM or EXT_SYS,\
"000",EXT_COM or EXT_DSK or EXT_SYS,\
"001",EXT_BCK or EXT_GAM or EXT_RAS,\
"002",EXT_BCK,\
"0xe",EXT_EXE,\
"113",EXT_BCK,\
"123",EXT_CAD or EXT_SPR,\
"123c",EXT_CAD,\
"123d",EXT_CAD,\
"123dx",EXT_CAD,\
"256",EXT_SET,\
"264",EXT_VID,\
"2bp",EXT_RAS,\
"2d",EXT_CAD,\
"2fs",EXT_SYS,\
"2mg",EXT_DSK,\
"2sf",EXT_AUD,\
"2sflib",EXT_AUD,\
"32x",EXT_GAM,\
"360",EXT_RAS,\
"386",EXT_SYS,\
"3d",EXT_3DI or EXT_GIS,\
"3d2",EXT_3DI,\
"3d4",EXT_3DI,\
"3da",EXT_3DI,\
"3dc",EXT_3DI or EXT_3DI or EXT_CAD or EXT_GIS,\
"3dd",EXT_GIS,\
"3df",EXT_3DI,\
"3dl",EXT_3DI or EXT_CAD or EXT_GIS,\
"3dm",EXT_3DI,\
"3dmf",EXT_3DI,\
"3dmk",EXT_3DI,\
"3don",EXT_3DI,\
"3dp",EXT_3DI,\
"3ds",EXT_3DI,\
"3dv",EXT_3DI,\
"3dw",EXT_3DI,\
"3dx",EXT_3DI,\
"3dxml",EXT_3DI,\
"3fr",EXT_CAM,\
"3g2",EXT_VID,\
"3ga",EXT_AUD,\
"3gp",EXT_VID,\
"3gp2",EXT_VID,\
"3gpp",EXT_VID,\
"3gpp2",EXT_VID,\
"3mm",EXT_VID,\
"3p2",EXT_VID,\
"411",EXT_RAS,\
"477",EXT_GIS,\
"4dd",EXT_DBA,\
"4dl",EXT_DBA,\
"4mp",EXT_AUD,\
"4ui",EXT_PAG,\
"555",EXT_GAM,\
"60d",EXT_VID,\
"669",EXT_AUD,\
"6cm",EXT_AUD,\
"73b",EXT_BCK,\
"73i",EXT_RAS,\
"73k",EXT_EXE,\
"73u",EXT_SYS,\
"787",EXT_VID,\
"7z",EXT_COM,\
"7z.001",EXT_COM,\
"7z.002",EXT_COM,\
"890",EXT_VID,\
"89k",EXT_EXE,\
"8ba",EXT_PLU,\
"8bc",EXT_PLU,\
"8be",EXT_PLU,\
"8bf",EXT_PLU,\
"8bi",EXT_PLU,\
"8bi8",EXT_PLU,\
"8bl",EXT_PLU,\
"8bs",EXT_PLU,\
"8bx",EXT_PLU,\
"8by",EXT_PLU,\
"8cm",EXT_AUD,\
"8ld",EXT_GAM,\
"8li",EXT_PLU,\
"8med",EXT_AUD,\
"8pbs",EXT_RAS,\
"8st",EXT_SET,\
"8svx",EXT_AUD,\
"8xi",EXT_RAS,\
"8xu",EXT_SYS,\
"a00",EXT_COM,\
"a01",EXT_COM,\
"a02",EXT_COM,\
"a26",EXT_GAM,\
"a2c",EXT_3DI,\
"a2l",EXT_CAD,\
"a2m",EXT_AUD or EXT_SET,\
"a2theme",EXT_SET,\
"a52",EXT_AUD or EXT_GAM,\
"a6p",EXT_EXE,\
"a8s",EXT_3DI,\
"aa",EXT_AUD or EXT_DSK,\
"aa3",EXT_AUD,\
"aac",EXT_AUD,\
"aaf",EXT_VID,\
"aao",EXT_GAM,\
"aaui",EXT_PLU,\
"aax",EXT_AUD,\
"ab",EXT_AUD or EXT_BCK,\
"aba",EXT_BCK or EXT_PLU,\
"abbu",EXT_BCK,\
"abc",EXT_AUD or EXT_VEC,\
"abf",EXT_BCK or EXT_FNT,\
"abi",EXT_PLU,\
"abk",EXT_BCK or EXT_GAM or EXT_GAM,\
"abm",EXT_AUD or EXT_RAS,\
"ac",EXT_EXE,\
"ac3",EXT_AUD,\
"ac5",EXT_VEC,\
"ac6",EXT_VEC,\
"acb",EXT_SET or EXT_SET,\
"acbl",EXT_SET,\
"accda",EXT_PLU,\
"accdb",EXT_DBA,\
"accdc",EXT_DBA,\
"accde",EXT_DBA,\
"accdr",EXT_DBA,\
"accdt",EXT_DBA,\
"accdu",EXT_PLU,\
"accdw",EXT_DBA,\
"accft",EXT_DBA,\
"accountpicture-ms",EXT_RAS,\
"acd-bak",EXT_AUD,\
"acd-zip",EXT_AUD,\
"acd",EXT_AUD,\
"ace",EXT_COM,\
"acf",EXT_GAM or EXT_SET,\
"acfm",EXT_FNT,\
"acm",EXT_AUD,\
"aco",EXT_SET,\
"acorn",EXT_RAS,\
"acp",EXT_AUD or EXT_BCK,\
"acr",EXT_BCK or EXT_EXE or EXT_RAS,\
"acrobatsecuritysettings",EXT_SET,\
"acrodata",EXT_SET,\
"acroplugin",EXT_PLU,\
"act",EXT_3DI or EXT_AUD or EXT_CAD or EXT_SET,\
"action",EXT_EXE,\
"actm",EXT_EXE,\
"acv",EXT_SET,\
"acw",EXT_SET,\
"acx",EXT_GAM,\
"adb",EXT_DBA or EXT_DBA,\
"adc",EXT_RAS,\
"addon",EXT_PLU,\
"ade",EXT_DBA,\
"adf",EXT_DBA or EXT_DSK,\
"adg",EXT_AUD,\
"adi",EXT_BCK or EXT_CAD,\
"adm",EXT_SYS,\
"adml",EXT_SYS,\
"admx",EXT_SYS,\
"adn",EXT_DBA,\
"ado",EXT_SET,\
"adp",EXT_DBA,\
"adpp",EXT_SET,\
"adt",EXT_AUD or EXT_CAD or EXT_GAM,\
"adts",EXT_AUD,\
"adv",EXT_AUD or EXT_SYS,\
"adz",EXT_DSK,\
"aea",EXT_BCK or EXT_SET,\
"aec",EXT_VID,\
"aep",EXT_ENC or EXT_VID,\
"aepx",EXT_VID,\
"aes",EXT_ENC,\
"aet",EXT_VID,\
"aetx",EXT_VID,\
"af2",EXT_VEC,\
"af3",EXT_VEC,\
"afc",EXT_AUD,\
"afd",EXT_CAD or EXT_DSK,\
"aff",EXT_DSK,\
"afm",EXT_DSK or EXT_FNT,\
"afp",EXT_ENC or EXT_PAG,\
"afs",EXT_CAD,\
"afx",EXT_RAS,\
"age3scn",EXT_GAM,\
"agif",EXT_RAS,\
"agm",EXT_AUD,\
"agp",EXT_RAS,\
"agr",EXT_AUD,\
"ahk",EXT_EXE,\
"ahl",EXT_SET,\
"ahs",EXT_SET,\
"ahu",EXT_SET,\
"ahx",EXT_AUD,\
"ai",EXT_GAM or EXT_VEC,\
"aia",EXT_SET,\
"aic",EXT_RAS,\
"aif",EXT_AUD,\
"aifc",EXT_AUD,\
"aiff",EXT_AUD,\
"aimppl",EXT_AUD,\
"ain",EXT_COM or EXT_GAM,\
"aip",EXT_PLU,\
"air",EXT_EXE or EXT_GAM,\
"ais",EXT_AUD or EXT_RAS,\
"ait",EXT_SET,\
"aiu",EXT_SET,\
"ajp",EXT_VID,\
"akp",EXT_AUD,\
"al",EXT_AUD,\
"alac",EXT_AUD,\
"alaw",EXT_AUD,\
"albm",EXT_RAS,\
"alc",EXT_AUD,\
"ale",EXT_VID,\
"alf",EXT_DBA,\
"all",EXT_AUD or EXT_SET,\
"alp",EXT_PLU,\
"alr",EXT_GAM,\
"als",EXT_AUD,\
"alv",EXT_SET,\
"alx",EXT_SET,\
"alz",EXT_COM,\
"am",EXT_VID,\
"am1",EXT_GAM,\
"amc",EXT_VID,\
"amf",EXT_AUD,\
"amfm",EXT_FNT,\
"aml",EXT_SYS,\
"amp",EXT_SET,\
"amr",EXT_AUD,\
"ams",EXT_AUD or EXT_AUD or EXT_SET,\
"amv",EXT_VID,\
"amx",EXT_PLU or EXT_VID,\
"amxd",EXT_AUD,\
"amxx",EXT_PLU,\
"amz",EXT_AUD,\
"an2",EXT_GAM,\
"an8",EXT_3DI,\
"ani",EXT_SYS,\
"anim",EXT_3DI or EXT_VID,\
"animset",EXT_3DI,\
"animset_ingame",EXT_3DI,\
"anm",EXT_3DI,\
"ann",EXT_SYS,\
"antispam5",EXT_SET,\
"any",EXT_CAD,\
"aob",EXT_AUD,\
"aof",EXT_3DI,\
"aoi",EXT_3DI,\
"aois",EXT_SET,\
"aom",EXT_SET,\
"aos",EXT_SYS,\
"apd",EXT_PLU or EXT_RAS,\
"ape",EXT_AUD or EXT_PLU,\
"apf",EXT_AUD,\
"api",EXT_PLU or EXT_SET,\
"apk",EXT_EXE,\
"apl",EXT_AUD or EXT_GIS or EXT_PLU,\
"aplg",EXT_PLU,\
"aplp",EXT_PLU,\
"apm",EXT_RAS,\
"apng",EXT_RAS,\
"app",EXT_EXE or EXT_EXE or EXT_EXE,\
"applescript",EXT_EXE,\
"application",EXT_SET,\
"appref-ms",EXT_SET,\
"apr",EXT_GIS,\
"aps",EXT_RAS,\
"apx",EXT_RAS,\
"apz",EXT_COM,\
"aqm",EXT_GIS,\
"aqt",EXT_VID,\
"ar",EXT_COM or EXT_GAM,\
"arc",EXT_BCK or EXT_BCK or EXT_COM or EXT_GAM,\
"arch00",EXT_GAM,\
"arcut",EXT_VID,\
"ard",EXT_CAD,\
"arena",EXT_GAM,\
"arf",EXT_VID,\
"arg",EXT_SET,\
"arh",EXT_COM,\
"ari",EXT_CAM or EXT_COM,\
"aria",EXT_AUD,\
"ariax",EXT_AUD,\
"arj",EXT_COM,\
"ark",EXT_COM,\
"arl",EXT_SET,\
"arp",EXT_GAM or EXT_SET,\
"arpack",EXT_PLU,\
"arr",EXT_RAS,\
"ars",EXT_GAM or EXT_SET,\
"arscript",EXT_EXE,\
"art",EXT_CAD or EXT_RAS or EXT_VEC,\
"artb",EXT_VEC,\
"artwork",EXT_RAS,\
"arw",EXT_CAM or EXT_RAS,\
"arx",EXT_PLU,\
"as4",EXT_BCK,\
"asat",EXT_3DI,\
"asb",EXT_EXE,\
"asc",EXT_CAD or EXT_ENC,\
"asd",EXT_AUD or EXT_BCK,\
"ase",EXT_AUD or EXT_SET,\
"asec",EXT_SYS,\
"asf",EXT_VID,\
"ash",EXT_GAM or EXT_GAM,\
"ashbak",EXT_BCK,\
"ashdisc",EXT_DSK,\
"ask",EXT_DBA or EXT_SET,\
"asl",EXT_SET,\
"asm",EXT_CAD,\
"asset",EXT_GAM,\
"ast",EXT_SET or EXT_SPR,\
"asv",EXT_SET,\
"asw",EXT_RAS,\
"aswcs",EXT_SET,\
"asws",EXT_SET,\
"asx",EXT_VID,\
"asy",EXT_CAD or EXT_VEC,\
"at3",EXT_AUD,\
"at5",EXT_GIS,\
"atc",EXT_SET,\
"ate",EXT_BCK,\
"atf",EXT_SET,\
"ath",EXT_SET,\
"ati",EXT_BCK,\
"atl",EXT_3DI,\
"atm",EXT_3DI or EXT_GAM,\
"atn",EXT_SET,\
"atr",EXT_DSK,\
"atrac",EXT_AUD,\
"att",EXT_CAD,\
"atx",EXT_GIS or EXT_PLU,\
"atz",EXT_SET,\
"au",EXT_AUD or EXT_AUD,\
"aud",EXT_AUD,\
"aup",EXT_AUD,\
"automaticdestinations-ms",EXT_SYS,\
"aux",EXT_GIS or EXT_SET,\
"avastsounds",EXT_AUD,\
"avatar",EXT_RAS,\
"avb",EXT_VID,\
"avc",EXT_VID,\
"avd",EXT_VID,\
"ave",EXT_SET,\
"avery",EXT_PAG,\
"avhd",EXT_DSK,\
"avi",EXT_VID,\
"avl",EXT_GIS,\
"avp",EXT_VID,\
"avr",EXT_AUD,\
"avs",EXT_SET or EXT_SET or EXT_SET or EXT_VID or EXT_VID,\
"avv",EXT_VID,\
"avx",EXT_PLU or EXT_PLU,\
"awb",EXT_AUD,\
"awcav",EXT_SET,\
"awd",EXT_RAS or EXT_RAS,\
"awg",EXT_VEC,\
"aws",EXT_SET or EXT_SPR,\
"ax",EXT_PLU,\
"axe",EXT_GIS,\
"axm",EXT_VID,\
"axp",EXT_SET,\
"axt",EXT_GIS or EXT_SET,\
"axx",EXT_ENC,\
"ay",EXT_AUD,\
"azw2",EXT_EXE,\
"b",EXT_GAM,\
"b1",EXT_COM,\
"b2a",EXT_ENC,\
"b3d",EXT_3DI,\
"b4s",EXT_AUD,\
"b5i",EXT_DSK,\
"b5t",EXT_DSK,\
"b64",EXT_COM,\
"b6i",EXT_DSK,\
"b6t",EXT_DSK,\
"ba",EXT_COM,\
"bac",EXT_BCK,\
"backupdb",EXT_BCK,\
"bak",EXT_BCK or EXT_BCK or EXT_BCK,\
"bak~",EXT_BCK,\
"band",EXT_AUD,\
"bap",EXT_AUD,\
"bar",EXT_GAM or EXT_GAM,\
"bash_history",EXT_SYS,\
"bash_profile",EXT_SYS,\
"bashrc",EXT_SYS,\
"bau",EXT_SET,\
"bav",EXT_PLU,\
"bay",EXT_CAM,\
"bbb",EXT_BCK,\
"bbcd",EXT_CAD,\
"bblm",EXT_PLU,\
"bbz",EXT_BCK,\
"bcd",EXT_CAD or EXT_SYS,\
"bcf",EXT_PAG,\
"bck",EXT_BCK,\
"bckp",EXT_BCK,\
"bcm",EXT_BCK,\
"bcmx",EXT_SET,\
"bcp",EXT_PAG or EXT_SET or EXT_SET,\
"bcs",EXT_AUD or EXT_SET or EXT_SET,\
"bdae",EXT_GAM,\
"bdb",EXT_BCK,\
"bdc",EXT_CAD,\
"bdd",EXT_AUD,\
"bdf",EXT_DSK or EXT_FNT,\
"bdl",EXT_CAD,\
"bdm",EXT_VID,\
"bdmv",EXT_VID,\
"bdt2",EXT_VID,\
"bdt3",EXT_VID,\
"beam",EXT_EXE,\
"bf",EXT_GAM,\
"bfa",EXT_ENC,\
"bff",EXT_BCK,\
"bfg",EXT_GAM,\
"bfs",EXT_GAM,\
"bgi",EXT_SET,\
"bgl",EXT_GAM,\
"bgz",EXT_GAM,\
"bh",EXT_COM,\
"bhx",EXT_ENC,\
"bic",EXT_GAM or EXT_GAM,\
"bidule",EXT_AUD,\
"bif",EXT_BCK or EXT_DSK or EXT_GAM,\
"bifx",EXT_BCK,\
"big",EXT_GAM,\
"bik",EXT_GAM or EXT_VID,\
"bil",EXT_GIS,\
"bin",EXT_DSK or EXT_ENC or EXT_EXE or EXT_GAM or EXT_SET or EXT_SYS or EXT_VID,\
"bio",EXT_3DI or EXT_SYS,\
"bip",EXT_3DI,\
"biq",EXT_GAM,\
"bit",EXT_CAD,\
"bitpim",EXT_SET,\
"bix",EXT_GAM or EXT_VID,\
"biz",EXT_PAG,\
"bk1",EXT_BCK or EXT_SYS,\
"bk2",EXT_SYS,\
"bkc",EXT_BCK,\
"bkf",EXT_BCK,\
"bkp",EXT_BCK or EXT_BCK,\
"bks",EXT_SET or EXT_SPR,\
"bkup",EXT_BCK,\
"bkz",EXT_BCK or EXT_PLU,\
"blb",EXT_GAM,\
"blend",EXT_3DI,\
"blend1",EXT_BCK,\
"blend2",EXT_BCK,\
"blf",EXT_SYS,\
"blk",EXT_CAD,\
"blkrt",EXT_RAS,\
"blob",EXT_SET,\
"blp",EXT_GAM or EXT_GAM,\
"bls",EXT_GAM,\
"blt",EXT_SET,\
"blu",EXT_PLU,\
"blw",EXT_SET,\
"blz",EXT_GAM or EXT_RAS,\
"bm2",EXT_RAS,\
"bm3",EXT_BCK,\
"bmc",EXT_RAS,\
"bmd",EXT_GAM or EXT_GAM,\
"bme",EXT_GAM,\
"bmf",EXT_CAD or EXT_RAS,\
"bmg",EXT_GAM,\
"bmi",EXT_PLU,\
"bmk",EXT_BCK or EXT_SYS or EXT_VID,\
"bmp",EXT_RAS,\
"bms",EXT_GAM,\
"bmx",EXT_RAS,\
"bmz",EXT_GAM or EXT_RAS,\
"bng",EXT_GAM,\
"bnk",EXT_GAM,\
"bnp",EXT_VID,\
"bns",EXT_GAM,\
"bnz",EXT_GAM,\
"bom",EXT_SYS,\
"bonk",EXT_AUD,\
"boo",EXT_COM,\
"book",EXT_PAG,\
"boot",EXT_SET,\
"box",EXT_AUD or EXT_VID,\
"bpa",EXT_BCK,\
"bpb",EXT_BCK,\
"bpf",EXT_PAG,\
"bpk",EXT_ENC,\
"bpm",EXT_BCK,\
"bpn",EXT_BCK,\
"bps",EXT_BCK,\
"bpw",EXT_GIS,\
"br3",EXT_3DI,\
"br4",EXT_3DI,\
"br5",EXT_3DI,\
"br6",EXT_3DI,\
"br7",EXT_3DI,\
"brd",EXT_CAD or EXT_CAD,\
"brg",EXT_3DI or EXT_SET,\
"bri",EXT_PLU,\
"brk",EXT_RAS,\
"brlyt",EXT_GAM,\
"brm",EXT_PLU,\
"brn",EXT_GAM or EXT_RAS,\
"bro",EXT_3DI or EXT_PAG or EXT_PAG or EXT_PLU,\
"brres",EXT_GAM,\
"brsar",EXT_GAM,\
"brstm",EXT_AUD,\
"brt",EXT_RAS,\
"bs1",EXT_GAM,\
"bs4",EXT_VID,\
"bs7",EXT_SET,\
"bsa",EXT_GAM,\
"bsb",EXT_GAM,\
"bsf",EXT_VID,\
"bsk",EXT_3DI or EXT_ENC,\
"bsp",EXT_GAM,\
"bss",EXT_RAS,\
"bt",EXT_GIS,\
"bti",EXT_RAS,\
"bto",EXT_3DI,\
"btoa",EXT_ENC,\
"btr",EXT_DBA,\
"btsearch",EXT_SET,\
"btw",EXT_PAG,\
"bun",EXT_AUD,\
"bundle",EXT_PLU,\
"bup",EXT_BCK or EXT_BCK,\
"bus",EXT_GAM,\
"bvd",EXT_ENC,\
"bvh",EXT_3DI,\
"bvr",EXT_VID,\
"bwa",EXT_DSK or EXT_GAM,\
"bwf",EXT_AUD,\
"bwg",EXT_AUD,\
"bwi",EXT_DSK,\
"bws",EXT_DSK,\
"bwt",EXT_DSK,\
"bww",EXT_AUD,\
"bwz",EXT_DSK,\
"bxl",EXT_CAD,\
"bxx",EXT_SET,\
"byu",EXT_VID,\
"bz",EXT_COM,\
"bz2",EXT_COM,\
"bza",EXT_COM,\
"bzip",EXT_COM,\
"bzip2",EXT_COM,\
"bzw",EXT_GAM,\
"c00",EXT_COM,\
"c01",EXT_AUD or EXT_COM,\
"c02",EXT_COM,\
"c10",EXT_COM,\
"c2d",EXT_DSK,\
"c2r",EXT_SET,\
"c32",EXT_SYS,\
"c3z",EXT_3DI,\
"c4",EXT_RAS,\
"c4d",EXT_3DI,\
"c4k",EXT_GAM,\
"cab",EXT_SYS,\
"cad",EXT_CAD,\
"caf",EXT_3DI or EXT_AUD,\
"caff",EXT_AUD,\
"cag",EXT_VEC,\
"cal",EXT_3DI or EXT_3DI or EXT_PAG or EXT_RAS,\
"cals",EXT_RAS,\
"cam",EXT_CAD or EXT_RAS,\
"camp",EXT_SET,\
"camproj",EXT_VID,\
"camrec",EXT_VID,\
"camv",EXT_VID,\
"can",EXT_RAS,\
"car",EXT_COM,\
"carc",EXT_GAM,\
"cas",EXT_3DI,\
"case",EXT_SET,\
"cat",EXT_DBA or EXT_SYS,\
"catpart",EXT_CAD,\
"catproduct",EXT_CAD,\
"cb7",EXT_COM,\
"cba",EXT_COM,\
"cbf",EXT_GAM or EXT_PAG,\
"cbh",EXT_GAM,\
"cbk",EXT_BCK,\
"cbr",EXT_COM,\
"cbs",EXT_BCK or EXT_GAM,\
"cbt",EXT_COM,\
"cbu",EXT_BCK,\
"cbv",EXT_GAM,\
"cbz",EXT_COM,\
"ccd",EXT_DSK,\
"ccf",EXT_ENC,\
"ccip",EXT_PLU,\
"ccx",EXT_PLU or EXT_VEC,\
"cd",EXT_DSK,\
"cd2",EXT_PAG,\
"cd5",EXT_RAS,\
"cda",EXT_AUD,\
"cdb",EXT_DBA or EXT_DBA or EXT_DBA,\
"cdc",EXT_RAS,\
"cdd",EXT_VEC,\
"cdda",EXT_AUD,\
"cddx",EXT_CAD,\
"cdf",EXT_PAG,\
"cdg",EXT_RAS,\
"cdi",EXT_DSK,\
"cdl",EXT_CAD or EXT_PLU,\
"cdlx",EXT_AUD,\
"cdm",EXT_DSK,\
"cdmm",EXT_VEC,\
"cdmp",EXT_SYS,\
"cdmt",EXT_VEC,\
"cdmtz",EXT_VEC,\
"cdmz",EXT_VEC,\
"cdo",EXT_AUD,\
"cdp",EXT_GAM,\
"cdp2",EXT_GAM,\
"cdr",EXT_AUD or EXT_DSK or EXT_VEC,\
"cdt",EXT_DSK or EXT_SET or EXT_VEC,\
"cdw",EXT_CAD,\
"cdx",EXT_VEC or EXT_VEC,\
"ce",EXT_RAS,\
"ced",EXT_VID,\
"cedprj",EXT_PAG,\
"cef",EXT_ENC,\
"cel",EXT_AUD or EXT_CAD or EXT_EXE or EXT_VID,\
"celx",EXT_EXE,\
"cem",EXT_GAM,\
"cex",EXT_SET,\
"cf",EXT_SET,\
"cf2",EXT_CAD,\
"cfa",EXT_AUD,\
"cff",EXT_CAD,\
"cfg",EXT_3DI or EXT_GAM or EXT_SET or EXT_SET or EXT_SET or EXT_SET or EXT_SET,\
"cfge",EXT_GAM,\
"cfr",EXT_GAM,\
"cfs",EXT_DSK,\
"cfxr",EXT_AUD,\
"cg",EXT_3DI,\
"cg3",EXT_3DI,\
"cga",EXT_3DI,\
"cgf",EXT_GAM,\
"cgfx",EXT_3DI,\
"cgm",EXT_VEC,\
"cgp",EXT_ENC,\
"cgr",EXT_CAD or EXT_SET,\
"cgz",EXT_GAM or EXT_SYS,\
"ch3",EXT_PAG,\
"cha",EXT_FNT or EXT_SET,\
"chd",EXT_GAM,\
"chesstitanssave-ms",EXT_GAM,\
"chg",EXT_SYS,\
"chk",EXT_GAM or EXT_SYS,\
"chl",EXT_SET,\
"chm",EXT_WEB,\
"chml",EXT_ENC,\
"chr",EXT_3DI or EXT_3DI or EXT_FNT,\
"chrparams",EXT_3DI,\
"cht",EXT_GAM or EXT_SYS,\
"chx",EXT_SET,\
"ci",EXT_SYS,\
"cidb",EXT_AUD,\
"cif",EXT_DSK,\
"cil",EXT_VEC,\
"cimg",EXT_RAS,\
"cin",EXT_RAS,\
"cine",EXT_VID,\
"cip",EXT_VID,\
"circuit",EXT_CAD,\
"cit",EXT_RAS,\
"ck9",EXT_BCK,\
"ckb",EXT_AUD,\
"ckd",EXT_CAD,\
"ckf",EXT_AUD,\
"ckp",EXT_DBA,\
"cl2arc",EXT_PAG,\
"cl2doc",EXT_PAG,\
"cl2lyt",EXT_PAG,\
"cl2tpl",EXT_PAG,\
"cl5",EXT_DSK,\
"clb",EXT_SYS,\
"cld",EXT_PAG,\
"cleo",EXT_PLU,\
"clg",EXT_SET,\
"clpi",EXT_VID,\
"clr",EXT_SET or EXT_SET,\
"clt",EXT_PAG,\
"clx",EXT_ENC,\
"cm",EXT_GAM or EXT_SET,\
"cm2",EXT_3DI,\
"cma",EXT_DBA,\
"cme",EXT_GAM,\
"cmf",EXT_3DI or EXT_AUD or EXT_BCK,\
"cml",EXT_GAM,\
"cmmp",EXT_VID,\
"cmmtheme",EXT_SET,\
"cmmtpl",EXT_VID,\
"cmod",EXT_3DI,\
"cmp",EXT_CAD or EXT_CAD or EXT_PLU or EXT_SET,\
"cmproj",EXT_VID,\
"cmrec",EXT_VID,\
"cmx",EXT_VEC,\
"cmz",EXT_3DI,\
"cnc",EXT_CAD or EXT_CAD,\
"cnd",EXT_CAD,\
"cndx",EXT_PAG,\
"cnf",EXT_SET or EXT_SET,\
"cng",EXT_ENC,\
"cns",EXT_GAM,\
"cnt",EXT_SYS,\
"cnv",EXT_VEC,\
"codaplugin",EXT_PLU,\
"cof",EXT_EXE,\
"col",EXT_GAM,\
"colorpicker",EXT_PLU,\
"colz",EXT_RAS,\
"com",EXT_EXE,\
"comfycakessave-ms",EXT_GAM,\
"comicdoc",EXT_PAG,\
"command",EXT_EXE,\
"component",EXT_PLU,\
"compositefont",EXT_FNT,\
"con",EXT_GAM,\
"conform",EXT_AUD,\
"controls",EXT_SET,\
"copreset",EXT_SET,\
"copy",EXT_AUD,\
"cor",EXT_GIS or EXT_VEC,\
"cos",EXT_GAM or EXT_SET,\
"costyle",EXT_SET,\
"cov",EXT_PAG,\
"cox",EXT_PLU,\
"cp9",EXT_COM,\
"cpa",EXT_CAD,\
"cpc",EXT_RAS,\
"cpd",EXT_DBA or EXT_RAS,\
"cpe",EXT_PAG,\
"cpf",EXT_SET,\
"cpg",EXT_GAM or EXT_RAS or EXT_SET,\
"cpgz",EXT_COM,\
"cph",EXT_PAG,\
"cpi",EXT_SYS or EXT_VID,\
"cpio",EXT_ENC,\
"cpk",EXT_GAM,\
"cpl",EXT_SYS,\
"cpn",EXT_GAM,\
"cpq",EXT_SYS,\
"cpr",EXT_AUD or EXT_SET or EXT_SYS,\
"cps",EXT_GAM or EXT_RAS,\
"cpt",EXT_AUD or EXT_COM or EXT_ENC or EXT_RAS,\
"cpx",EXT_GAM or EXT_RAS or EXT_SET,\
"cpy",EXT_3DI or EXT_PAG,\
"cr2",EXT_3DI or EXT_CAM,\
"craft",EXT_GAM,\
"crash",EXT_SYS,\
"crds",EXT_BCK,\
"crf",EXT_3DI,\
"crs",EXT_GAM,\
"crtr",EXT_PAG,\
"crv",EXT_CAD,\
"crw",EXT_CAM,\
"crx",EXT_PLU,\
"crypted",EXT_ENC,\
"cryptra",EXT_ENC,\
"crysisjmsf",EXT_GAM,\
"crysispsf",EXT_GAM,\
"crz",EXT_3DI,\
"cs",EXT_GAM,\
"csaplan",EXT_SET,\
"csd",EXT_3DI or EXT_PAG,\
"csf",EXT_3DI or EXT_RAS or EXT_SET,\
"csh",EXT_AUD or EXT_EXE,\
"cskin",EXT_SET,\
"csm",EXT_3DI,\
"cso",EXT_DSK,\
"csplan",EXT_SET,\
"cst",EXT_PAG or EXT_SET or EXT_VID,\
"csy",EXT_VEC,\
"ct",EXT_GAM or EXT_RAS,\
"ctb",EXT_SET,\
"ctbodyfitting",EXT_SET,\
"ctm",EXT_GAM,\
"cts",EXT_AUD,\
"ctx",EXT_GAM,\
"cty",EXT_GAM,\
"cub",EXT_GIS,\
"cue",EXT_DSK or EXT_DSK,\
"cui",EXT_SET,\
"cuix",EXT_SET,\
"cur",EXT_SYS,\
"cus",EXT_SET,\
"cut",EXT_RAS,\
"cv5",EXT_VEC,\
"cva",EXT_SET,\
"cvc",EXT_VID,\
"cvg",EXT_VEC,\
"cvi",EXT_GIS or EXT_VEC,\
"cvs",EXT_VEC,\
"cvt",EXT_PLU,\
"cvw",EXT_PAG,\
"cvx",EXT_VEC,\
"cw",EXT_PAG,\
"cwb",EXT_AUD,\
"cwf",EXT_SET,\
"cwp",EXT_AUD,\
"cx3",EXT_VID,\
"cxf",EXT_VEC,\
"cyberducklicense",EXT_SET,\
"cyberduckprofile",EXT_SET,\
"cyp",EXT_CAD,\
"cyw",EXT_EXE,\
"czd",EXT_CAD,\
"czip",EXT_COM,\
"d00",EXT_AUD or EXT_DSK,\
"d01",EXT_AUD or EXT_DSK,\
"d2s",EXT_GAM,\
"d2v",EXT_VID,\
"d3d",EXT_3DI,\
"d3dbsp",EXT_GAM,\
"d3v",EXT_VID,\
"d64",EXT_DSK,\
"d88",EXT_DSK,\
"da0",EXT_BCK,\
"daa",EXT_DSK,\
"daconnections",EXT_DBA,\
"dacpac",EXT_DBA,\
"dad",EXT_DBA,\
"dadiagrams",EXT_DBA,\
"dae",EXT_3DI,\
"dam",EXT_GAM,\
"dao",EXT_DSK,\
"dar",EXT_COM,\
"daschema",EXT_DBA,\
"dat",EXT_GAM or EXT_GAM or EXT_SYS or EXT_VID,\
"dat_mcr",EXT_GAM,\
"dat_old",EXT_GAM,\
"dav",EXT_VID,\
"dax",EXT_DSK,\
"day",EXT_GAM,\
"daz",EXT_3DI,\
"dazip",EXT_GAM,\
"db-shm",EXT_DBA,\
"db-wal",EXT_DBA,\
"db",EXT_DBA or EXT_DBA or EXT_GAM,\
"db1",EXT_CAD,\
"db2",EXT_DBA,\
"db3",EXT_DBA,\
"dba",EXT_BCK,\
"dbb",EXT_SET,\
"dbc",EXT_3DI or EXT_DBA,\
"dbf",EXT_DBA,\
"dbg",EXT_SET,\
"dbk",EXT_BCK or EXT_BCK,\
"dbl",EXT_3DI,\
"dbm",EXT_3DI,\
"dbq",EXT_CAD,\
"dbr",EXT_DSK,\
"dbs",EXT_3DI or EXT_DBA,\
"dbt",EXT_DBA,\
"dbv",EXT_DBA,\
"dbx",EXT_DBA or EXT_PLU,\
"dc",EXT_CAD,\
"dc1",EXT_CAD,\
"dc2",EXT_CAD or EXT_CAD or EXT_RAS,\
"dc3",EXT_CAD,\
"dc4",EXT_ENC,\
"dcb",EXT_DBA,\
"dcd",EXT_CAD or EXT_ENC,\
"dce",EXT_VID,\
"dcf",EXT_AUD or EXT_DSK or EXT_ENC,\
"dck",EXT_VID,\
"dcl",EXT_SET,\
"dcm",EXT_AUD or EXT_RAS,\
"dco",EXT_ENC,\
"dcp",EXT_SET,\
"dcr",EXT_CAM or EXT_VID or EXT_VID,\
"dcs",EXT_VEC,\
"dcst",EXT_SET,\
"dct",EXT_AUD or EXT_DBA,\
"dcx",EXT_DBA or EXT_PAG or EXT_RAS,\
"dd",EXT_COM,\
"ddat",EXT_VID,\
"ddb",EXT_GAM or EXT_RAS,\
"ddd",EXT_3DI,\
"ddf",EXT_SET,\
"ddl",EXT_DBA,\
"ddrw",EXT_VEC,\
"dds",EXT_RAS,\
"ddt",EXT_AUD or EXT_GAM or EXT_RAS,\
"deb",EXT_COM,\
"ded",EXT_VEC,\
"def",EXT_GAM or EXT_SPR,\
"dek",EXT_EXE or EXT_GAM or EXT_GAM or EXT_GAM,\
"dem",EXT_GAM or EXT_GIS,\
"des",EXT_3DI or EXT_CAD,\
"desc",EXT_GAM,\
"design",EXT_VEC,\
"desklink",EXT_SYS,\
"deskthemepack",EXT_SYS,\
"dev",EXT_SYS,\
"dewf",EXT_AUD,\
"dex",EXT_SPR,\
"df2",EXT_AUD,\
"dfc",EXT_AUD,\
"dff",EXT_3DI,\
"dfg",EXT_SPR,\
"dfont",EXT_FNT,\
"dfp",EXT_PLU,\
"dfs",EXT_3DI,\
"dft",EXT_CAD,\
"dfu",EXT_SYS,\
"dfx",EXT_CAD,\
"dgb",EXT_CAD,\
"dgc",EXT_COM,\
"dgk",EXT_CAD,\
"dgn",EXT_CAD,\
"dgt",EXT_RAS,\
"dhs",EXT_VEC,\
"dia",EXT_VEC,\
"diagcab",EXT_SYS,\
"diagcfg",EXT_SYS,\
"diagpkg",EXT_SYS,\
"dib",EXT_RAS,\
"dicom",EXT_RAS,\
"dicproof",EXT_SET,\
"dif",EXT_3DI or EXT_GAM or EXT_VID,\
"dig",EXT_AUD or EXT_AUD,\
"dim",EXT_ENC,\
"dimax",EXT_SYS,\
"dime",EXT_ENC,\
"dinfo",EXT_SET,\
"dir",EXT_VID,\
"directory",EXT_SET,\
"dis",EXT_SPR,\
"disc",EXT_DSK,\
"disk",EXT_DSK,\
"dist",EXT_COM,\
"dit",EXT_SYS,\
"div",EXT_GIS,\
"diva",EXT_GAM,\
"divx",EXT_VID,\
"dix",EXT_GIS,\
"diy",EXT_BCK,\
"djr",EXT_AUD,\
"djv",EXT_RAS,\
"djvu",EXT_RAS,\
"dl",EXT_GAM,\
"dl_",EXT_COM,\
"dlc",EXT_ENC,\
"dld",EXT_EXE,\
"dlg",EXT_GIS,\
"dll",EXT_SYS,\
"dlo",EXT_PLU,\
"dls",EXT_AUD,\
"dlu",EXT_PLU,\
"dlv",EXT_CAD,\
"dlx",EXT_CAD or EXT_SYS or EXT_VID,\
"dm",EXT_AUD,\
"dm_68",EXT_GAM,\
"dm_82",EXT_GAM,\
"dm_83",EXT_GAM,\
"dm_84",EXT_GAM,\
"dm2",EXT_GAM,\
"dm3",EXT_GAM or EXT_RAS,\
"dmb",EXT_VID,\
"dmc",EXT_3DI or EXT_AUD or EXT_EXE,\
"dmf",EXT_AUD or EXT_GIS,\
"dmg",EXT_DSK,\
"dmgpart",EXT_DSK,\
"dmo",EXT_GAM or EXT_GAM,\
"dmp",EXT_SYS,\
"dms",EXT_DSK or EXT_GAM,\
"dmsa",EXT_AUD,\
"dmsd",EXT_VID,\
"dmsd3d",EXT_VID,\
"dmse",EXT_AUD,\
"dmsm",EXT_VID,\
"dmsm3d",EXT_VID,\
"dmss",EXT_VID,\
"dmtemplate",EXT_PAG,\
"dmx",EXT_VID,\
"dn1",EXT_GAM,\
"dn2",EXT_GAM,\
"dn3",EXT_GAM,\
"dna",EXT_BCK,\
"dnc",EXT_VID,\
"dnf",EXT_GAM,\
"dng",EXT_CAM,\
"dnh",EXT_GAM,\
"dns",EXT_GAM,\
"dol",EXT_GAM,\
"dolphinview",EXT_SET,\
"dot",EXT_PAG,\
"dov",EXT_BCK,\
"downloadhost",EXT_SET,\
"dp1",EXT_DBA,\
"dpa",EXT_VID,\
"dpb",EXT_BCK,\
"dpd",EXT_PAG,\
"dpg",EXT_VID,\
"dpm",EXT_PLU,\
"dpp",EXT_VEC,\
"dpr",EXT_VEC,\
"dps",EXT_SET,\
"dpv",EXT_SET,\
"dpx",EXT_RAS or EXT_VEC,\
"dqy",EXT_DBA,\
"dra",EXT_AUD or EXT_CAD or EXT_CAD,\
"drawing",EXT_VEC,\
"drawit",EXT_VEC,\
"dream",EXT_VID,\
"drf",EXT_3DI,\
"drg",EXT_AUD or EXT_CAD,\
"drm",EXT_GAM or EXT_SET,\
"drpm",EXT_SYS,\
"drv",EXT_SYS,\
"drw",EXT_VEC or EXT_VEC,\
"drwdot",EXT_CAD,\
"drz",EXT_RAS,\
"ds",EXT_3DI or EXT_AUD or EXT_EXE or EXT_GAM,\
"ds_store",EXT_SET,\
"ds2",EXT_AUD,\
"dsa",EXT_3DI,\
"dsb",EXT_3DI or EXT_BCK,\
"dsd",EXT_3DI or EXT_SET,\
"dse",EXT_3DI,\
"dsf",EXT_3DI or EXT_AUD or EXT_VEC,\
"dsg",EXT_CAD or EXT_GAM,\
"dsi",EXT_3DI or EXT_3DI,\
"dsk",EXT_DBA or EXT_DSK,\
"dsm",EXT_AUD,\
"dsn",EXT_CAD or EXT_DBA,\
"dso",EXT_3DI,\
"dsp",EXT_AUD,\
"dss",EXT_AUD or EXT_SYS,\
"dst",EXT_CAD or EXT_CAD,\
"dsv",EXT_3DI,\
"dsw",EXT_SET,\
"dsx",EXT_SET,\
"dsy",EXT_VID,\
"dt0",EXT_GIS,\
"dt1",EXT_GIS,\
"dt2",EXT_GIS or EXT_RAS,\
"dtm",EXT_AUD,\
"dtp",EXT_PAG,\
"dts",EXT_AUD,\
"dtshd",EXT_AUD,\
"dtsx",EXT_DBA,\
"dtw",EXT_RAS,\
"dtx",EXT_PAG,\
"duc",EXT_GAM,\
"duck",EXT_SET,\
"dun",EXT_SET,\
"dv-avi",EXT_VID,\
"dv",EXT_VID,\
"dv2",EXT_GAM,\
"dv4",EXT_VID,\
"dvc",EXT_GIS,\
"dvd",EXT_DSK or EXT_SYS,\
"dvdmedia",EXT_VID,\
"dvdr",EXT_DSK,\
"dvf",EXT_AUD,\
"dvg",EXT_CAD,\
"dvl",EXT_RAS,\
"dvr-ms",EXT_VID,\
"dvr",EXT_VID,\
"dvx",EXT_VID,\
"dwa",EXT_AUD,\
"dwd",EXT_AUD,\
"dwdoc",EXT_PAG,\
"dwf",EXT_3DI,\
"dwfx",EXT_CAD,\
"dwg",EXT_CAD,\
"dwp",EXT_GAM,\
"dws",EXT_CAD,\
"dwt",EXT_CAD,\
"dxb",EXT_VEC,\
"dxe",EXT_CAD,\
"dxf",EXT_CAD,\
"dxl",EXT_DBA or EXT_EXE,\
"dxls",EXT_SET,\
"dxp",EXT_DSK or EXT_SET,\
"dxr",EXT_VID,\
"dxs",EXT_GAM,\
"dxx",EXT_CAD,\
"dyc",EXT_SYS,\
"dz",EXT_COM or EXT_GAM,\
"dzip",EXT_GAM,\
"dzm",EXT_VID,\
"dzp",EXT_VID,\
"dzt",EXT_VID,\
"e_e",EXT_EXE,\
"e00",EXT_GIS,\
"e01",EXT_DSK,\
"e2gm",EXT_GAM,\
"e4a",EXT_ENC,\
"e57",EXT_3DI,\
"eap",EXT_SET,\
"ear",EXT_AUD or EXT_EXE,\
"easm",EXT_CAD,\
"eaz",EXT_PLU,\
"ebm",EXT_EXE,\
"ebs",EXT_EXE,\
"ebs2",EXT_EXE,\
"ecf",EXT_EXE or EXT_PLU,\
"ecl",EXT_GAM,\
"ecm",EXT_DSK,\
"eco",EXT_DBA,\
"ecs",EXT_COM,\
"ecw",EXT_RAS,\
"ecx",EXT_DBA,\
"eda",EXT_DSK,\
"edat",EXT_GAM,\
"edb",EXT_DBA,\
"ede",EXT_DSK,\
"edj",EXT_SYS,\
"edk",EXT_DSK,\
"edl",EXT_VID,\
"edn",EXT_CAD,\
"edq",EXT_DSK,\
"edrw",EXT_CAD,\
"edrwx",EXT_PAG,\
"eds",EXT_DSK,\
"edv",EXT_DSK,\
"eepf",EXT_GAM,\
"efa",EXT_AUD,\
"efe",EXT_AUD,\
"efi",EXT_SYS,\
"efires",EXT_SYS,\
"efk",EXT_AUD,\
"efl",EXT_ENC,\
"efq",EXT_AUD,\
"efr",EXT_ENC,\
"efs",EXT_AUD,\
"eftx",EXT_SET,\
"efu",EXT_ENC,\
"efv",EXT_AUD,\
"efw",EXT_COM,\
"egg",EXT_3DI or EXT_COM,\
"egm",EXT_GAM,\
"eham",EXT_EXE,\
"eix",EXT_GAM,\
"elf",EXT_EXE or EXT_GAM or EXT_SYS,\
"elm",EXT_GAM or EXT_SET,\
"emc",EXT_ENC,\
"emd",EXT_AUD,\
"emerald",EXT_SYS,\
"emf",EXT_VEC,\
"emp",EXT_AUD,\
"emx",EXT_AUD,\
"emy",EXT_AUD,\
"emz",EXT_VEC,\
"enc",EXT_ENC or EXT_GAM or EXT_PAG,\
"eng",EXT_GAM,\
"enp",EXT_SET,\
"ens",EXT_SET,\
"env",EXT_SET or EXT_SET,\
"enz",EXT_SET,\
"eot",EXT_FNT,\
"epc",EXT_GAM,\
"epi",EXT_COM,\
"epk",EXT_GAM,\
"epk2",EXT_PLU,\
"epp",EXT_RAS,\
"epr",EXT_SET,\
"eps",EXT_VEC,\
"epsf",EXT_VEC,\
"eqf",EXT_SET,\
"eql",EXT_SET,\
"eqn",EXT_CAD,\
"eqp",EXT_SET,\
"erb",EXT_GAM,\
"erf",EXT_CAM or EXT_GAM,\
"erp",EXT_GAM,\
"ers",EXT_GIS,\
"es",EXT_EXE,\
"esg",EXT_GAM,\
"esh",EXT_EXE,\
"esm",EXT_GAM or EXT_GAM,\
"esp",EXT_GAM or EXT_GAM,\
"esps",EXT_AUD,\
"ess",EXT_GAM or EXT_SPR,\
"est",EXT_GIS,\
"eta",EXT_GIS,\
"etff",EXT_SET,\
"etl",EXT_SYS,\
"etx",EXT_FNT,\
"euf",EXT_FNT,\
"eui",EXT_DSK,\
"eum",EXT_SET,\
"ev3",EXT_SET,\
"evo",EXT_VID,\
"evt",EXT_SYS,\
"evtx",EXT_SYS,\
"ewb",EXT_CAD,\
"ewd",EXT_CAD,\
"ex_",EXT_EXE or EXT_EXE,\
"ex4",EXT_EXE,\
"exc",EXT_GAM,\
"exe",EXT_EXE or EXT_EXE,\
"exe1",EXT_EXE,\
"exe4j",EXT_SET,\
"exopc",EXT_EXE,\
"exp",EXT_3DI or EXT_SET,\
"expressionmap",EXT_AUD,\
"exr",EXT_RAS,\
"exs",EXT_GAM,\
"ext",EXT_PLU,\
"exv",EXT_PLU,\
"eye",EXT_VID,\
"ezc",EXT_CAD,\
"ezp",EXT_CAD,\
"ezs",EXT_EXE,\
"ezt",EXT_EXE or EXT_VID,\
"f",EXT_COM,\
"f2r",EXT_AUD,\
"f32",EXT_AUD,\
"f3f",EXT_FNT,\
"f3r",EXT_AUD,\
"f4a",EXT_AUD,\
"f4p",EXT_VID,\
"f4v",EXT_VID,\
"f64",EXT_AUD,\
"fac",EXT_RAS,\
"face",EXT_RAS,\
"facefx",EXT_3DI,\
"facefx_ingame",EXT_3DI,\
"fal",EXT_RAS,\
"fan",EXT_CAD,\
"far",EXT_AUD or EXT_GAM,\
"fas",EXT_EXE or EXT_EXE,\
"fat",EXT_SET,\
"favoritemetadata",EXT_SET,\
"fax",EXT_RAS,\
"fbc",EXT_BCK,\
"fbf",EXT_BCK,\
"fbk",EXT_BCK or EXT_BCK,\
"fbl",EXT_GIS,\
"fbm",EXT_RAS,\
"fbr",EXT_VID or EXT_VID,\
"fbrb",EXT_GAM,\
"fbu",EXT_BCK,\
"fbw",EXT_BCK,\
"fbx",EXT_3DI,\
"fbz",EXT_VID,\
"fc2",EXT_3DI,\
"fc2map",EXT_GAM,\
"fcc",EXT_SET,\
"fcd",EXT_CAD or EXT_DBA or EXT_DSK,\
"fcdt",EXT_PAG,\
"fcm",EXT_GAM,\
"fcp",EXT_3DI or EXT_VID,\
"fcproject",EXT_VID,\
"fcs",EXT_SPR,\
"fcstd",EXT_CAD,\
"fcw",EXT_CAD,\
"fcz",EXT_3DI,\
"fd",EXT_SET,\
"fd2",EXT_PAG,\
"fda",EXT_AUD,\
"fdb",EXT_DBA,\
"fdc",EXT_SET,\
"fdd",EXT_DSK or EXT_PAG,\
"fdi",EXT_DSK,\
"fdp",EXT_AUD or EXT_COM,\
"fds",EXT_GAM or EXT_GIS,\
"fdt",EXT_PAG,\
"fev",EXT_AUD or EXT_SET,\
"ff",EXT_GAM,\
"ffa",EXT_SYS,\
"ffd",EXT_GAM or EXT_VID,\
"fff",EXT_AUD or EXT_CAM,\
"ffil",EXT_FNT,\
"ffl",EXT_SYS,\
"ffo",EXT_SYS,\
"ffs",EXT_GIS,\
"fft",EXT_PLU,\
"ffx",EXT_SET or EXT_SYS,\
"fg",EXT_3DI,\
"fgd",EXT_GAM,\
"fh",EXT_BCK,\
"fh10",EXT_VEC,\
"fh11",EXT_VEC,\
"fh7",EXT_VEC,\
"fh8",EXT_VEC,\
"fh9",EXT_VEC,\
"fhd",EXT_VEC,\
"fhf",EXT_BCK,\
"fic",EXT_DBA,\
"fid",EXT_SYS,\
"fif",EXT_VEC,\
"fig",EXT_3DI or EXT_VEC,\
"fil",EXT_RAS,\
"fila",EXT_GAM,\
"fit",EXT_GIS,\
"fits",EXT_RAS,\
"fky",EXT_EXE,\
"fl",EXT_GAM,\
"flac",EXT_AUD,\
"flb",EXT_PAG,\
"flc",EXT_VID,\
"fld",EXT_GAM,\
"flg",EXT_DSK,\
"flh",EXT_VID,\
"fli",EXT_VID,\
"flka",EXT_BCK,\
"flkb",EXT_BCK,\
"flp",EXT_AUD or EXT_DSK,\
"fls",EXT_AUD or EXT_GIS,\
"flst",EXT_SET,\
"flt",EXT_3DI or EXT_PLU or EXT_PLU or EXT_SET,\
"flv",EXT_VID,\
"flx",EXT_CAD or EXT_VID,\
"fm",EXT_PAG or EXT_SPR,\
"fm3",EXT_SET,\
"fm5",EXT_DBA,\
"fme",EXT_GIS,\
"fmi",EXT_GIS,\
"fml",EXT_GAM,\
"fmod",EXT_SET,\
"fmp",EXT_DBA or EXT_SET,\
"fmp12",EXT_DBA,\
"fmplugin",EXT_PLU,\
"fmpsl",EXT_DBA,\
"fmt",EXT_SET,\
"fmv",EXT_GIS or EXT_VEC,\
"fmw",EXT_GIS,\
"fmx",EXT_PLU,\
"fmz",EXT_CAD,\
"fnc",EXT_3DI or EXT_CAD or EXT_SET,\
"fnt",EXT_FNT,\
"fnta",EXT_GAM,\
"fods",EXT_SPR,\
"fol",EXT_DBA,\
"fomod",EXT_GAM,\
"fon",EXT_FNT,\
"forge",EXT_GAM,\
"fos",EXT_GAM,\
"fot",EXT_FNT,\
"fota",EXT_SYS,\
"fox",EXT_GAM,\
"fp",EXT_3DI or EXT_SPR,\
"fp3",EXT_3DI or EXT_DBA or EXT_PAG,\
"fp4",EXT_DBA,\
"fp5",EXT_DBA,\
"fp7",EXT_DBA,\
"fpbf",EXT_SYS,\
"fpd",EXT_CAD,\
"fpe",EXT_3DI,\
"fpenc",EXT_ENC,\
"fpf",EXT_3DI,\
"fpg",EXT_GAM or EXT_RAS,\
"fpi",EXT_EXE,\
"fpid",EXT_GAM,\
"fpj",EXT_3DI,\
"fpk",EXT_GAM,\
"fpmb",EXT_GAM,\
"fpmo",EXT_GAM,\
"fpop",EXT_GAM,\
"fpos",EXT_RAS,\
"fpp",EXT_CAD or EXT_GAM,\
"fps",EXT_GAM,\
"fpt",EXT_DBA,\
"fpx",EXT_RAS,\
"fr3",EXT_PAG,\
"frc",EXT_GAM or EXT_SET,\
"frf",EXT_PAG,\
"frg",EXT_AUD,\
"frm",EXT_DBA or EXT_RAS,\
"frr",EXT_SET,\
"frs",EXT_EXE,\
"fry",EXT_3DI,\
"frz",EXT_GAM,\
"fs",EXT_PLU or EXT_VEC,\
"fs2",EXT_GAM,\
"fsb",EXT_AUD or EXT_PLU,\
"fsg",EXT_GAM,\
"fsh",EXT_3DI,\
"fsm",EXT_AUD or EXT_ENC or EXT_GAM,\
"fsq",EXT_3DI,\
"fssave",EXT_GAM,\
"fst",EXT_GAM,\
"ft",EXT_SET,\
"ft10",EXT_VEC,\
"ft11",EXT_VEC,\
"ft7",EXT_VEC,\
"ft8",EXT_VEC,\
"ft9",EXT_VEC,\
"ftg",EXT_SYS,\
"fth",EXT_SET or EXT_SET,\
"ftm",EXT_AUD,\
"ftn",EXT_VEC,\
"ftpquota",EXT_SET,\
"fts",EXT_SYS,\
"ful",EXT_BCK,\
"fwt",EXT_SET,\
"fx",EXT_3DI,\
"fxa",EXT_3DI,\
"fxb",EXT_PLU,\
"fxg",EXT_VEC,\
"fxl",EXT_3DI,\
"fxm",EXT_3DI or EXT_PAG,\
"fxp",EXT_EXE or EXT_PLU,\
"fxs",EXT_3DI,\
"fxt",EXT_3DI or EXT_GAM or EXT_PLU,\
"fz",EXT_CAD,\
"fza",EXT_BCK,\
"fzb",EXT_AUD or EXT_BCK,\
"fzf",EXT_AUD,\
"fzip",EXT_PLU,\
"fzp",EXT_CAD or EXT_PLU,\
"fzv",EXT_AUD,\
"fzz",EXT_CAD,\
"g",EXT_CAD,\
"g3",EXT_RAS,\
"g3d",EXT_CAD,\
"g3x",EXT_GAM,\
"g41",EXT_DSK,\
"g721",EXT_AUD,\
"g723",EXT_AUD,\
"g726",EXT_AUD,\
"gadget",EXT_EXE,\
"galaxy",EXT_GAM,\
"gam",EXT_GAM,\
"game",EXT_GAM or EXT_GAM,\
"gar",EXT_GAM,\
"gb",EXT_GAM,\
"gb1",EXT_BCK,\
"gba",EXT_GAM,\
"gbc",EXT_GAM,\
"gbi",EXT_DSK,\
"gbp",EXT_BCK,\
"gbproj",EXT_AUD,\
"gbr",EXT_RAS,\
"gbs",EXT_AUD,\
"gbx",EXT_CAD or EXT_GAM,\
"gc",EXT_GAM,\
"gca",EXT_COM,\
"gcd",EXT_CAD or EXT_DSK,\
"gcdp",EXT_RAS,\
"gcf",EXT_GAM,\
"gci",EXT_GAM,\
"gcm",EXT_GAM,\
"gcs",EXT_GAM,\
"gcsx",EXT_SET,\
"gct",EXT_GAM,\
"gdb",EXT_DBA,\
"gdiagramstyle",EXT_SET,\
"gdr",EXT_FNT,\
"gdraw",EXT_VEC,\
"gdrive",EXT_DSK,\
"gds",EXT_CAD,\
"gdw",EXT_GAM,\
"gem",EXT_PAG or EXT_VEC,\
"gen",EXT_GAM,\
"geo",EXT_3DI,\
"geojson",EXT_GIS,\
"gf",EXT_FNT,\
"gfb",EXT_RAS,\
"gfie",EXT_RAS,\
"gfp",EXT_VID,\
"gfw",EXT_GIS,\
"gg",EXT_GAM,\
"gho",EXT_BCK,\
"ghs",EXT_BCK,\
"gi",EXT_DSK,\
"gid",EXT_SET,\
"gif",EXT_RAS,\
"gig",EXT_AUD,\
"gih",EXT_RAS,\
"gim",EXT_RAS,\
"gin",EXT_SET,\
"ginspect_prj",EXT_CAD,\
"gio",EXT_AUD or EXT_AUD,\
"gjd",EXT_GAM,\
"gkh",EXT_DSK,\
"gks",EXT_VEC,\
"gl",EXT_VID,\
"glb",EXT_GAM or EXT_GIS,\
"glox",EXT_VEC,\
"gls",EXT_VEC,\
"gm",EXT_AUD,\
"gmap",EXT_GIS,\
"gmbck",EXT_RAS,\
"gme",EXT_GAM,\
"gmf",EXT_3DI or EXT_GIS,\
"gml",EXT_GIS,\
"gmmod",EXT_3DI,\
"gmmp",EXT_SYS,\
"gmres",EXT_GAM,\
"gmspr",EXT_RAS,\
"gmt",EXT_3DI,\
"gmv",EXT_GAM,\
"gnp",EXT_GAM,\
"god",EXT_GAM,\
"gom",EXT_VID,\
"goomod",EXT_GAM,\
"gp4",EXT_RAS,\
"gp5",EXT_AUD,\
"gpbank",EXT_AUD,\
"gpd",EXT_RAS,\
"gpe",EXT_EXE,\
"gpf",EXT_GAM or EXT_GAM or EXT_GIS,\
"gpk",EXT_AUD,\
"gprx",EXT_GIS,\
"gps",EXT_GIS or EXT_SET or EXT_SET,\
"gpu",EXT_EXE,\
"gpx",EXT_AUD or EXT_GIS,\
"gqsx",EXT_SET,\
"gr2",EXT_GAM,\
"graffle",EXT_VEC,\
"grasp",EXT_VID,\
"grb",EXT_GIS,\
"grd",EXT_SET,\
"grf",EXT_GAM or EXT_GAM,\
"grl",EXT_SYS,\
"grn",EXT_3DI,\
"gro",EXT_AUD or EXT_RAS,\
"grob",EXT_RAS,\
"groove",EXT_AUD,\
"group",EXT_SYS,\
"growlticket",EXT_SET,\
"grp",EXT_GAM or EXT_SYS,\
"gry",EXT_RAS,\
"gs",EXT_EXE,\
"gs0",EXT_GAM,\
"gsb",EXT_GIS,\
"gsc",EXT_GAM,\
"gsd",EXT_VEC,\
"gsheet",EXT_SPR,\
"gsi",EXT_GIS,\
"gsm",EXT_AUD or EXT_AUD or EXT_CAD or EXT_GIS,\
"gsr",EXT_GIS,\
"gsr2",EXT_GIS,\
"gst",EXT_GIS,\
"gstencil",EXT_VEC,\
"gsx",EXT_GAM,\
"gtemplate",EXT_VEC,\
"gtkrc",EXT_SET,\
"gtp",EXT_SET,\
"gts",EXT_VID,\
"gvi",EXT_VID,\
"gvimrc",EXT_SET,\
"gvp",EXT_VID,\
"gwi",EXT_DBA,\
"gws",EXT_GIS or EXT_SET,\
"gxc",EXT_CAD,\
"gxd",EXT_CAD,\
"gxf",EXT_FNT,\
"gxh",EXT_CAD,\
"gxk",EXT_ENC,\
"gxm",EXT_CAD,\
"gxt",EXT_SET,\
"gz",EXT_COM,\
"gz2",EXT_COM,\
"gza",EXT_COM,\
"gzi",EXT_COM,\
"gzip",EXT_COM,\
"h0",EXT_AUD,\
"h1s",EXT_SYS,\
"h264",EXT_VID,\
"h2o",EXT_GAM,\
"h3m",EXT_GAM,\
"h4r",EXT_GAM,\
"ha",EXT_COM,\
"ham",EXT_EXE or EXT_GAM,\
"hbc",EXT_COM,\
"hbc2",EXT_COM,\
"hbe",EXT_COM,\
"hbx",EXT_ENC,\
"hcp",EXT_CAD,\
"hcr",EXT_PAG,\
"hd2",EXT_3DI,\
"hdb",EXT_DBA,\
"hdd",EXT_DSK,\
"hdi",EXT_DSK,\
"hdmov",EXT_VID,\
"hdmp",EXT_SYS,\
"hdp",EXT_AUD or EXT_RAS,\
"hdr",EXT_GIS or EXT_RAS,\
"hdrp",EXT_RAS,\
"hds",EXT_DSK,\
"hdt",EXT_SET,\
"hdz",EXT_3DI,\
"heartssave-ms",EXT_GAM,\
"help",EXT_SYS,\
"hex",EXT_ENC,\
"hf",EXT_RAS,\
"hfd",EXT_PAG,\
"hfs",EXT_DSK,\
"hft",EXT_PAG,\
"hfv",EXT_DSK,\
"hgl",EXT_VEC,\
"hgt",EXT_GIS,\
"hhc",EXT_SYS,\
"hhk",EXT_SYS,\
"hhsl",EXT_GAM,\
"hi",EXT_GAM,\
"hid",EXT_SET,\
"hip",EXT_3DI,\
"hipnc",EXT_3DI,\
"his",EXT_DBA,\
"hit",EXT_GAM,\
"hiv",EXT_SYS,\
"hki",EXT_COM,\
"hki1",EXT_COM,\
"hki2",EXT_COM,\
"hki3",EXT_COM,\
"hkm",EXT_VID,\
"hlp",EXT_SYS,\
"hlsl",EXT_3DI,\
"hma",EXT_AUD,\
"hme",EXT_SET,\
"hmi",EXT_AUD,\
"hmk",EXT_PAG,\
"hmp",EXT_GAM,\
"hms",EXT_EXE,\
"hog",EXT_GAM,\
"honmod",EXT_GAM,\
"hot",EXT_GAM,\
"hpd",EXT_PAG,\
"hpf",EXT_EXE,\
"hpg",EXT_VEC,\
"hpgl",EXT_VEC,\
"hpi",EXT_RAS,\
"hpj",EXT_SYS,\
"hpk",EXT_COM,\
"hpl",EXT_VEC,\
"hps",EXT_GAM,\
"hpt",EXT_PAG,\
"hqx",EXT_ENC,\
"hr",EXT_RAS,\
"hr2",EXT_3DI,\
"hrf",EXT_RAS,\
"hrz",EXT_3DI,\
"hs",EXT_GAM,\
"hsb",EXT_AUD,\
"hsc",EXT_CAD,\
"hsf",EXT_CAD,\
"hsh",EXT_SYS,\
"ht",EXT_SET,\
"hta",EXT_EXE,\
"htt",EXT_SYS,\
"hus",EXT_CAD,\
"hvpl",EXT_PLU,\
"hwd",EXT_GAM,\
"hwmap",EXT_GAM,\
"hws",EXT_GAM,\
"hxm",EXT_GAM,\
"hxn",EXT_3DI,\
"hyp",EXT_COM,\
"i00",EXT_DSK,\
"i01",EXT_DSK,\
"i02",EXT_DSK,\
"i3d",EXT_RAS,\
"i3pack",EXT_GAM,\
"iaf",EXT_SET,\
"iam",EXT_CAD,\
"ib",EXT_DBA,\
"ib2",EXT_GAM,\
"ib3",EXT_GAM,\
"iba",EXT_CAD,\
"ibp",EXT_DSK,\
"ibplugin",EXT_PLU,\
"ibq",EXT_DSK,\
"ibro",EXT_GAM,\
"ibt",EXT_GAM,\
"ic1",EXT_RAS,\
"ic2",EXT_RAS,\
"ic3",EXT_RAS,\
"ica",EXT_RAS or EXT_SET,\
"icap",EXT_PAG,\
"icb",EXT_RAS,\
"icbu",EXT_BCK,\
"icc",EXT_SET,\
"icd",EXT_EXE or EXT_SET,\
"ice",EXT_COM,\
"icf",EXT_BCK,\
"icl",EXT_SYS,\
"icm",EXT_SET,\
"icml",EXT_PAG,\
"icn",EXT_RAS,\
"icns",EXT_SYS,\
"ico",EXT_SYS,\
"icon",EXT_RAS,\
"iconpackage",EXT_SET,\
"icpr",EXT_RAS,\
"ics",EXT_AUD or EXT_CAD,\
"icursorfx",EXT_SET,\
"idap",EXT_PAG,\
"idb",EXT_DBA,\
"ide",EXT_CAD,\
"idea",EXT_VEC,\
"idf",EXT_SET,\
"idml",EXT_PAG,\
"idms",EXT_PAG,\
"idpk",EXT_PAG,\
"idpp",EXT_SET,\
"idv",EXT_CAD,\
"idw",EXT_CAD,\
"idx",EXT_SYS,\
"idx0",EXT_GAM,\
"idx255",EXT_GAM,\
"if",EXT_CAD,\
"ifc",EXT_3DI,\
"ifcxml",EXT_CAD,\
"ifczip",EXT_CAD,\
"ifd",EXT_PAG,\
"iff",EXT_AUD,\
"ifo",EXT_VID,\
"ifp",EXT_GAM,\
"iges",EXT_3DI,\
"igm",EXT_3DI,\
"igp",EXT_AUD,\
"igr",EXT_AUD or EXT_SET,\
"igs",EXT_3DI or EXT_CAD,\
"igt",EXT_VEC,\
"igx",EXT_VEC,\
"ihw",EXT_SET,\
"ihx",EXT_DBA,\
"iim",EXT_EXE,\
"iip",EXT_SET or EXT_SET,\
"iiq",EXT_CAM,\
"iit",EXT_SET,\
"ik",EXT_3DI,\
"ilbm",EXT_RAS,\
"ildoc",EXT_PAG,\
"ima",EXT_DSK,\
"image",EXT_DSK,\
"imd",EXT_GIS or EXT_VEC,\
"ime",EXT_SYS,\
"imf",EXT_AUD,\
"img",EXT_DSK or EXT_DSK or EXT_DSK or EXT_GAM or EXT_GIS or EXT_GIS or EXT_RAS,\
"img3",EXT_SYS,\
"imga",EXT_GAM,\
"imi",EXT_GIS,\
"imj",EXT_RAS,\
"immodules",EXT_SET,\
"imovieproj",EXT_VID,\
"imovieproject",EXT_VID,\
"imp",EXT_AUD,\
"imz",EXT_DSK,\
"incd",EXT_PAG,\
"inct",EXT_PAG,\
"incx",EXT_PAG,\
"ind",EXT_PAG,\
"indb",EXT_PAG,\
"indd",EXT_PAG,\
"indesignplugin",EXT_PLU,\
"indl",EXT_PAG,\
"indp",EXT_PAG,\
"inds",EXT_PAG,\
"indt",EXT_PAG,\
"inf",EXT_SET,\
"info",EXT_RAS,\
"infopathxml",EXT_PAG,\
"ini",EXT_SET or EXT_SET or EXT_SET,\
"ink",EXT_RAS or EXT_VEC or EXT_VEC,\
"inms",EXT_SET,\
"inp",EXT_GAM or EXT_PAG,\
"inprogress",EXT_BCK,\
"ins",EXT_AUD or EXT_AUD or EXT_SET or EXT_SYS,\
"int",EXT_RAS,\
"inv",EXT_GAM,\
"inx",EXT_PAG or EXT_PLU,\
"ion",EXT_SYS,\
"ioplist",EXT_SYS,\
"ipa",EXT_EXE,\
"ipd",EXT_BCK,\
"ipf",EXT_CAD or EXT_DSK or EXT_EXE,\
"ipg",EXT_COM,\
"ipj",EXT_CAD,\
"ipk",EXT_COM,\
"ipl",EXT_GAM,\
"ipn",EXT_CAD,\
"ipod",EXT_SYS,\
"ips",EXT_GAM,\
"ipt",EXT_CAD,\
"iptheme",EXT_SET,\
"ipx",EXT_RAS,\
"ircp",EXT_VID,\
"irf",EXT_VID,\
"iros",EXT_SET,\
"irs",EXT_SET,\
"isd",EXT_PAG,\
"ise",EXT_CAD,\
"ish",EXT_COM,\
"ism",EXT_VID,\
"isma",EXT_AUD,\
"ismc",EXT_VID,\
"ismv",EXT_VID,\
"iso",EXT_CAD or EXT_DSK,\
"isoz",EXT_CAD,\
"isp",EXT_SET,\
"isr",EXT_GAM,\
"iss",EXT_SET or EXT_SET,\
"isu",EXT_EXE,\
"isz",EXT_DSK,\
"it",EXT_AUD,\
"ita",EXT_COM,\
"itc2",EXT_RAS,\
"itdb",EXT_DBA,\
"itemdata-ms",EXT_SYS,\
"ithmb",EXT_RAS,\
"iti",EXT_AUD,\
"itk",EXT_GAM,\
"itr",EXT_GAM,\
"its",EXT_AUD or EXT_SYS,\
"itt",EXT_SET,\
"itw",EXT_DBA,\
"ius",EXT_SYS,\
"iv",EXT_3DI,\
"iv2i",EXT_BCK,\
"iva",EXT_VID,\
"ive",EXT_3DI,\
"ivf",EXT_VID,\
"ivr",EXT_RAS or EXT_VID,\
"ivs",EXT_VID,\
"ivt",EXT_GAM,\
"ivue",EXT_RAS,\
"iwd",EXT_GAM,\
"iwi",EXT_RAS,\
"ix",EXT_SET,\
"ixa",EXT_DSK,\
"ize",EXT_COM,\
"izz",EXT_VID,\
"izzy",EXT_VID,\
"j",EXT_COM or EXT_RAS,\
"j2c",EXT_RAS,\
"j2i",EXT_GAM,\
"j2k",EXT_RAS,\
"j2l",EXT_GAM,\
"j3o",EXT_3DI,\
"ja",EXT_GAM,\
"jag",EXT_GAM,\
"jam",EXT_AUD or EXT_AUD or EXT_CAD or EXT_GAM,\
"jar",EXT_EXE,\
"jar.pack",EXT_COM,\
"jas",EXT_3DI or EXT_RAS,\
"jb2",EXT_RAS,\
"jbc",EXT_CAD,\
"jbf",EXT_RAS,\
"jbig",EXT_RAS,\
"jbig2",EXT_RAS,\
"jbk",EXT_BCK,\
"jbmp",EXT_RAS,\
"jbr",EXT_RAS,\
"jdc",EXT_BCK,\
"jdf",EXT_SET,\
"jfi",EXT_RAS,\
"jfif",EXT_RAS,\
"jg4",EXT_GAM,\
"jgw",EXT_GIS,\
"jgz",EXT_COM,\
"jia",EXT_RAS,\
"jic",EXT_COM,\
"jif",EXT_RAS,\
"jiff",EXT_RAS,\
"jigsaw",EXT_GAM,\
"jkm",EXT_SET,\
"jng",EXT_RAS,\
"jo-7z",EXT_AUD,\
"jo",EXT_AUD,\
"job",EXT_CAD or EXT_SYS,\
"joy",EXT_SET,\
"jp2",EXT_RAS,\
"jpc",EXT_RAS,\
"jpd",EXT_RAS,\
"jpe",EXT_RAS,\
"jpeg",EXT_RAS,\
"jpf",EXT_RAS,\
"jpg",EXT_RAS,\
"jpg2",EXT_RAS,\
"jpgw",EXT_GIS,\
"jpn",EXT_SYS,\
"jpr",EXT_GIS,\
"jps",EXT_RAS,\
"jpw",EXT_GIS,\
"jpx",EXT_RAS,\
"jrc",EXT_GAM,\
"jrz",EXT_GAM,\
"js",EXT_EXE,\
"jse",EXT_EXE,\
"jsf",EXT_SET,\
"jss",EXT_VID,\
"jsx",EXT_EXE,\
"jsxbin",EXT_PLU,\
"jt",EXT_CAD,\
"jtf",EXT_RAS,\
"jtp",EXT_PAG,\
"jts",EXT_VID,\
"jtv",EXT_VID,\
"jtx",EXT_DBA or EXT_PAG or EXT_PAG,\
"jvsg",EXT_CAD,\
"jwl",EXT_RAS,\
"jws",EXT_SET,\
"jxr",EXT_RAS,\
"k25",EXT_AUD,\
"k26",EXT_AUD,\
"k2s",EXT_GAM,\
"k3g",EXT_VID,\
"kag",EXT_GAM,\
"kar",EXT_AUD,\
"kb2",EXT_BCK,\
"kbd",EXT_SET or EXT_SYS,\
"kcl",EXT_GAM,\
"kdb",EXT_DBA,\
"kdc",EXT_CAM,\
"kde",EXT_ENC,\
"kdi",EXT_RAS,\
"kdk",EXT_RAS,\
"kds",EXT_SET,\
"kexi",EXT_DBA,\
"kexic",EXT_DBA,\
"kexis",EXT_DBA,\
"kext",EXT_SYS,\
"key",EXT_SET or EXT_SYS,\
"kfm",EXT_3DI,\
"kfn",EXT_AUD,\
"kfx",EXT_RAS,\
"kgb",EXT_COM,\
"kic",EXT_RAS,\
"kin",EXT_AUD,\
"kit",EXT_AUD or EXT_CAD,\
"kix",EXT_EXE,\
"kmc",EXT_3DI,\
"kmcobj",EXT_3DI,\
"kml",EXT_GIS,\
"kmm",EXT_PLU,\
"kmp",EXT_AUD,\
"kmz",EXT_GIS,\
"ko",EXT_SYS,\
"kodak",EXT_RAS,\
"kodu",EXT_GAM,\
"kor",EXT_SYS,\
"koz",EXT_AUD or EXT_AUD,\
"kpg",EXT_RAS,\
"kpl",EXT_AUD,\
"krz",EXT_AUD,\
"ksc",EXT_AUD,\
"ksf",EXT_AUD,\
"ksh",EXT_EXE,\
"ksm",EXT_AUD,\
"kt2",EXT_AUD,\
"kt3",EXT_AUD,\
"ktp",EXT_AUD,\
"ktz",EXT_3DI,\
"kv6",EXT_GAM,\
"kwreplay",EXT_GAM,\
"kyb",EXT_SET,\
"kys",EXT_SET,\
"kz",EXT_COM,\
"l",EXT_AUD,\
"l01",EXT_DSK,\
"l3d",EXT_GAM,\
"l4d",EXT_SET,\
"la",EXT_AUD,\
"lab",EXT_PAG,\
"laby",EXT_GAM,\
"lan",EXT_GIS,\
"lang",EXT_SET,\
"lay",EXT_SET or EXT_SET,\
"layout",EXT_SET,\
"lbl",EXT_PAG,\
"lbm",EXT_RAS,\
"lbr",EXT_COM,\
"lbu",EXT_SET,\
"lcb",EXT_BCK,\
"lcd",EXT_DSK,\
"lcf",EXT_CAD,\
"ldb",EXT_GAM,\
"ldm",EXT_3DI,\
"ldr",EXT_CAD,\
"ldt",EXT_CAD,\
"ldw",EXT_GAM,\
"lemon",EXT_COM,\
"lfs",EXT_SYS,\
"lgc",EXT_DBA,\
"lgl",EXT_GAM,\
"lgp",EXT_GAM,\
"lgt",EXT_SET,\
"lha",EXT_COM,\
"library-ms",EXT_SYS,\
"lif",EXT_RAS,\
"lily",EXT_SET,\
"lin",EXT_CAD,\
"lip",EXT_GAM or EXT_GAM,\
"ljp",EXT_RAS,\
"ll",EXT_GAM,\
"llm",EXT_3DI,\
"llx",EXT_BCK,\
"lmk",EXT_VEC,\
"lmu",EXT_GAM,\
"lnd",EXT_3DI,\
"lng",EXT_PLU or EXT_PLU,\
"lnk",EXT_SYS,\
"lnst",EXT_SET,\
"lnx",EXT_COM or EXT_DSK,\
"lo",EXT_EXE,\
"loaders",EXT_SET,\
"lock",EXT_GAM,\
"lockfile",EXT_SYS,\
"lod",EXT_GAM,\
"lof",EXT_AUD,\
"log1",EXT_SYS,\
"log2",EXT_SYS,\
"logic",EXT_AUD,\
"look",EXT_SET,\
"lop",EXT_SET,\
"love",EXT_GAM,\
"lp",EXT_3DI,\
"lpb",EXT_GAM,\
"lpd",EXT_SYS or EXT_SYS,\
"lpk",EXT_GIS,\
"lps",EXT_3DI,\
"lqr",EXT_COM,\
"lqt",EXT_AUD,\
"lrec",EXT_VID,\
"lrf",EXT_GAM,\
"lrplugin",EXT_PLU,\
"lrsmcol",EXT_SET,\
"lrtemplate",EXT_SET,\
"lrwebengine",EXT_PLU,\
"ls",EXT_EXE,\
"lsd",EXT_GAM,\
"lsf",EXT_VID,\
"lso",EXT_AUD,\
"lst",EXT_SYS,\
"lsw",EXT_GAM,\
"lsx",EXT_VID,\
"lt2",EXT_3DI,\
"ltf",EXT_PAG,\
"ltg",EXT_GAM,\
"ltx",EXT_GAM,\
"ltz",EXT_3DI,\
"luxb",EXT_GAM,\
"lva",EXT_SET,\
"lvf",EXT_SET,\
"lvivt",EXT_ENC,\
"lvl",EXT_GAM,\
"lvp",EXT_AUD,\
"lwfn",EXT_FNT,\
"lwo",EXT_3DI,\
"lws",EXT_3DI,\
"lwv",EXT_AUD,\
"lxcp",EXT_SET,\
"lxf",EXT_3DI,\
"lxo",EXT_3DI,\
"lxsopt",EXT_SET,\
"lyc",EXT_CAD,\
"lyr",EXT_CAD,\
"lyt",EXT_SET or EXT_SET,\
"lz",EXT_COM,\
"lzh",EXT_COM,\
"lzm",EXT_COM,\
"lzma",EXT_COM,\
"lzo",EXT_COM,\
"lzx",EXT_COM,\
"m15",EXT_VID,\
"m1a",EXT_AUD,\
"m1pg",EXT_VID,\
"m1v",EXT_VID,\
"m2",EXT_GAM,\
"m21",EXT_VID or EXT_VID,\
"m2a",EXT_VID,\
"m2p",EXT_PLU or EXT_VID,\
"m2s",EXT_SET,\
"m2t",EXT_VID,\
"m2ts",EXT_VID,\
"m2v",EXT_VID,\
"m3",EXT_3DI,\
"m3d",EXT_3DI or EXT_3DI,\
"m3g",EXT_EXE,\
"m3u",EXT_AUD,\
"m3u8",EXT_AUD,\
"m4a",EXT_AUD,\
"m4b",EXT_AUD,\
"m4e",EXT_VID,\
"m4p",EXT_AUD,\
"m4r",EXT_AUD,\
"m4u",EXT_VID,\
"m4v",EXT_VID,\
"m75",EXT_VID,\
"ma",EXT_3DI,\
"ma1",EXT_AUD,\
"mac",EXT_RAS,\
"mae",EXT_GAM,\
"maf",EXT_DBA,\
"mailhost",EXT_SET,\
"make",EXT_SET,\
"mal",EXT_SET,\
"mam",EXT_EXE,\
"mani",EXT_VID,\
"manifest",EXT_SYS,\
"manm",EXT_GAM,\
"map",EXT_GAM or EXT_GAM or EXT_GAM or EXT_GIS or EXT_GIS,\
"mapimail",EXT_SYS,\
"maplet",EXT_GAM,\
"maq",EXT_DBA,\
"mar",EXT_DBA or EXT_SPR,\
"mars",EXT_PAG,\
"marshal",EXT_DBA,\
"mas",EXT_DBA or EXT_GAM,\
"mask",EXT_SET,\
"masseffectprofile",EXT_GAM,\
"masseffectsave",EXT_GAM,\
"mat",EXT_3DI or EXT_PLU or EXT_RAS,\
"material",EXT_SET,\
"mato",EXT_GAM,\
"mav",EXT_DBA,\
"maw",EXT_DBA,\
"max",EXT_3DI or EXT_GAM or EXT_PAG or EXT_RAS,\
"maxc",EXT_3DI,\
"maz",EXT_GAM,\
"mb",EXT_3DI,\
"mbbk",EXT_PAG,\
"mbf",EXT_BCK,\
"mbi",EXT_DSK,\
"mbk",EXT_BCK,\
"mbm",EXT_RAS or EXT_RAS,\
"mbr",EXT_AUD or EXT_SYS,\
"mbw",EXT_BCK,\
"mc5",EXT_3DI,\
"mc6",EXT_3DI,\
"mc9",EXT_CAD,\
"mca",EXT_GAM,\
"mcd",EXT_CAD,\
"mcf",EXT_FNT,\
"mcgame",EXT_GAM,\
"mcl",EXT_SET,\
"mclevel",EXT_GAM,\
"mcr",EXT_EXE or EXT_EXE or EXT_GAM or EXT_GAM,\
"mcrp",EXT_ENC,\
"mcs",EXT_RAS,\
"mcsp",EXT_PAG,\
"mcsx",EXT_PAG,\
"mcw",EXT_SET,\
"mcworld",EXT_GAM,\
"mcx",EXT_CAD,\
"mcz",EXT_3DI,\
"md",EXT_COM or EXT_GAM or EXT_GAM,\
"md0",EXT_DSK,\
"md1",EXT_DSK or EXT_DSK,\
"md2",EXT_DSK or EXT_GAM,\
"md3",EXT_GAM,\
"md5anim",EXT_3DI,\
"md5camera",EXT_3DI,\
"md5mesh",EXT_3DI,\
"mda",EXT_PLU,\
"mdb",EXT_DBA,\
"mdbackup",EXT_BCK,\
"mdbhtml",EXT_DBA,\
"mdc",EXT_GIS,\
"mdd",EXT_3DI,\
"mddata",EXT_BCK,\
"mde",EXT_PLU or EXT_PLU,\
"mdf",EXT_DBA or EXT_DSK,\
"mdi",EXT_PAG,\
"mdinfo",EXT_BCK,\
"mdl",EXT_3DI or EXT_AUD or EXT_CAD or EXT_GAM,\
"mdm",EXT_GAM,\
"mdmp",EXT_SYS,\
"mdn",EXT_DBA,\
"mdp",EXT_SET,\
"mds",EXT_DSK,\
"mdt",EXT_DBA,\
"mdx",EXT_3DI or EXT_DSK,\
"me",EXT_SYS,\
"me2mod",EXT_GAM,\
"meb",EXT_3DI,\
"med",EXT_AUD,\
"mef",EXT_CAM,\
"mel",EXT_EXE,\
"mem",EXT_BCK or EXT_EXE or EXT_GAM or EXT_SYS,\
"menu",EXT_GAM,\
"meo",EXT_ENC,\
"mesh",EXT_3DI or EXT_3DI,\
"met",EXT_RAS,\
"meta",EXT_VID,\
"metadata_never_index",EXT_SYS,\
"mf",EXT_FNT,\
"mfo",EXT_PAG,\
"mfp",EXT_PAG,\
"mfs",EXT_ENC,\
"mft",EXT_PAG,\
"mfw",EXT_PLU,\
"mfx",EXT_PLU,\
"mga",EXT_PAG,\
"mgc",EXT_VEC,\
"mgcb",EXT_VEC,\
"mgf",EXT_3DI,\
"mgk",EXT_SET,\
"mgl",EXT_GAM,\
"mgm",EXT_GIS or EXT_SET,\
"mgmf",EXT_VEC,\
"mgmt",EXT_VEC,\
"mgmx",EXT_VEC,\
"mgs",EXT_VEC,\
"mgtheme",EXT_SET,\
"mgtx",EXT_VEC,\
"mgv",EXT_AUD or EXT_VID,\
"mgx",EXT_GAM or EXT_GAM,\
"mhs",EXT_CAD,\
"mi4",EXT_SYS,\
"mic",EXT_RAS,\
"mid",EXT_AUD or EXT_GIS,\
"midi",EXT_AUD,\
"mif",EXT_GIS or EXT_PAG,\
"mig",EXT_BCK,\
"mii",EXT_GAM,\
"milk",EXT_PLU,\
"mim",EXT_ENC,\
"mime",EXT_ENC,\
"mine",EXT_GAM,\
"minesweepersave-ms",EXT_GAM,\
"mini2sf",EXT_AUD,\
"miniusf",EXT_AUD,\
"mint",EXT_COM,\
"mio",EXT_EXE,\
"mip",EXT_RAS,\
"mir",EXT_DSK,\
"mis",EXT_GAM or EXT_GAM,\
"mission",EXT_GAM,\
"mix",EXT_3DI or EXT_GAM or EXT_RAS,\
"mj2",EXT_VID,\
"mjd",EXT_ENC,\
"mjp",EXT_VID,\
"mjpg",EXT_VID,\
"mk3d",EXT_VID,\
"mka",EXT_AUD,\
"mkv",EXT_VID,\
"mlc",EXT_DSK or EXT_SYS,\
"mlk",EXT_SET,\
"mlp",EXT_AUD,\
"mm6",EXT_GAM,\
"mm7",EXT_GAM,\
"mm8",EXT_GAM,\
"mmat",EXT_VEC,\
"mmdc",EXT_SET,\
"mme",EXT_ENC,\
"mmf",EXT_AUD,\
"mmip",EXT_PLU,\
"mml",EXT_PAG,\
"mmm",EXT_AUD,\
"mmp",EXT_AUD or EXT_SET,\
"mmv",EXT_VID,\
"mnc",EXT_ENC,\
"mng",EXT_RAS,\
"mnh",EXT_GIS,\
"mnm",EXT_3DI,\
"mnr",EXT_RAS,\
"mns",EXT_SET,\
"mnu",EXT_SET or EXT_SET or EXT_SET,\
"mnv",EXT_VID,\
"mo3",EXT_AUD,\
"mob",EXT_VID,\
"mobileconfig",EXT_SYS,\
"mod",EXT_AUD or EXT_GAM or EXT_PLU or EXT_SYS or EXT_VID,\
"modd",EXT_VID,\
"mode",EXT_PLU,\
"model",EXT_CAD,\
"mof",EXT_SET,\
"moff",EXT_VID,\
"moi",EXT_VID,\
"moov",EXT_VID,\
"mos",EXT_CAM,\
"mot",EXT_3DI,\
"mou",EXT_COM,\
"mov",EXT_VID,\
"movie",EXT_VID,\
"mp",EXT_3DI or EXT_VEC,\
"mp_",EXT_AUD,\
"mp1",EXT_AUD,\
"mp10",EXT_CAD,\
"mp11",EXT_CAD,\
"mp2",EXT_AUD,\
"mp21",EXT_VID or EXT_VID,\
"mp2m",EXT_GAM,\
"mp2s",EXT_GAM,\
"mp2v",EXT_VID,\
"mp3",EXT_AUD,\
"mp4",EXT_VID,\
"mp4v",EXT_VID,\
"mp7",EXT_CAD,\
"mp9",EXT_CAD,\
"mpa",EXT_AUD,\
"mpb",EXT_BCK,\
"mpc",EXT_AUD,\
"mpd",EXT_DBA,\
"mpdconf",EXT_SET,\
"mpdp",EXT_AUD,\
"mpe",EXT_VID,\
"mpeg",EXT_VID,\
"mpeg4",EXT_VID,\
"mpf",EXT_RAS or EXT_VID,\
"mpg",EXT_VID,\
"mpg2",EXT_VID,\
"mpga",EXT_AUD,\
"mpgindex",EXT_VID,\
"mpj",EXT_3DI,\
"mpk",EXT_GAM or EXT_GIS,\
"mpkg",EXT_COM,\
"mpl",EXT_VID or EXT_VID,\
"mpls",EXT_VID,\
"mpm",EXT_GAM,\
"mpo",EXT_RAS,\
"mpq",EXT_GAM,\
"mps",EXT_GAM or EXT_GIS,\
"mpsub",EXT_VID,\
"mpu",EXT_AUD,\
"mpv",EXT_VID,\
"mpv2",EXT_VID,\
"mpw",EXT_SET,\
"mpx",EXT_EXE,\
"mpz",EXT_GAM,\
"mqo",EXT_3DI,\
"mqv",EXT_VID,\
"mrb",EXT_RAS,\
"mrc",EXT_EXE,\
"mrg",EXT_DBA,\
"mrimg",EXT_DSK,\
"mrml",EXT_3DI,\
"mrs",EXT_GAM,\
"mrw",EXT_CAM,\
"mrxs",EXT_RAS,\
"ms",EXT_EXE or EXT_EXE,\
"ms1",EXT_GAM,\
"ms11",EXT_CAD,\
"ms3d",EXT_3DI,\
"ms7",EXT_CAD,\
"ms9",EXT_CAD,\
"msc",EXT_SYS,\
"mscx",EXT_AUD,\
"mscz",EXT_AUD,\
"msd",EXT_GIS,\
"msdvd",EXT_VID,\
"mse",EXT_ENC or EXT_VID,\
"msf",EXT_SET,\
"msh",EXT_3DI or EXT_VID,\
"msk",EXT_RAS,\
"mskn",EXT_SET,\
"msm",EXT_SET,\
"msn",EXT_SET,\
"msp",EXT_RAS or EXT_SYS,\
"msstyle",EXT_SYS,\
"msstyles",EXT_SYS,\
"mst",EXT_SET or EXT_SET,\
"msv",EXT_AUD,\
"msw",EXT_SET,\
"mswmm",EXT_VID,\
"mt2",EXT_AUD,\
"mt9",EXT_AUD,\
"mte",EXT_AUD,\
"mtf",EXT_AUD or EXT_SET,\
"mti",EXT_AUD,\
"mtl",EXT_3DI,\
"mtm",EXT_AUD,\
"mtp",EXT_AUD,\
"mts",EXT_AUD or EXT_VID,\
"mtv",EXT_VID,\
"mtx",EXT_3DI or EXT_PLU,\
"mtz",EXT_3DI or EXT_SYS,\
"mu",EXT_3DI,\
"mu3",EXT_AUD,\
"mud",EXT_3DI or EXT_DBA,\
"mui",EXT_AUD or EXT_SYS,\
"mul",EXT_GAM or EXT_GAM,\
"mum",EXT_SYS,\
"mus",EXT_AUD or EXT_AUD or EXT_AUD or EXT_GAM,\
"musa",EXT_AUD,\
"mux",EXT_AUD or EXT_AUD,\
"muz",EXT_AUD,\
"mv_",EXT_BCK,\
"mvb",EXT_VID,\
"mvc",EXT_VID,\
"mvd",EXT_VID,\
"mve",EXT_VID,\
"mvex",EXT_VID,\
"mvp",EXT_VID or EXT_VID,\
"mvs",EXT_CAD,\
"mvy",EXT_VID,\
"mwb",EXT_DBA,\
"mws",EXT_AUD,\
"mwx",EXT_GIS,\
"mx3",EXT_AUD,\
"mx4",EXT_AUD,\
"mx5",EXT_AUD,\
"mx5template",EXT_AUD,\
"mxaddon",EXT_PLU,\
"mxcs",EXT_SET,\
"mxd",EXT_GIS,\
"mxe",EXT_EXE,\
"mxf",EXT_FNT or EXT_VID,\
"mxfr",EXT_SET,\
"mxi",EXT_RAS,\
"mxl",EXT_AUD,\
"mxm",EXT_3DI,\
"mxmf",EXT_AUD,\
"mxp",EXT_PLU,\
"mxs",EXT_3DI or EXT_SET,\
"mxskin",EXT_SET,\
"mxt",EXT_GIS,\
"mxv",EXT_VID,\
"mycolors",EXT_SET,\
"myd",EXT_DBA,\
"mydocs",EXT_SYS,\
"myl",EXT_RAS,\
"myr",EXT_AUD,\
"mys",EXT_VID,\
"mzp",EXT_AUD or EXT_COM or EXT_COM,\
"n-gage",EXT_GAM,\
"n2",EXT_3DI,\
"n3d",EXT_3DI or EXT_GAM,\
"n3pmesh",EXT_GAM,\
"n64",EXT_GAM,\
"nam",EXT_GAM,\
"nap",EXT_AUD or EXT_VEC,\
"narc",EXT_GAM,\
"nav",EXT_GAM,\
"naz",EXT_GAM,\
"nb",EXT_SPR,\
"nb0",EXT_SYS,\
"nb7",EXT_BCK,\
"nba",EXT_BCK,\
"nbd",EXT_BCK or EXT_BCK,\
"nbf",EXT_BCK or EXT_BCK,\
"nbh",EXT_SYS,\
"nbi",EXT_BCK,\
"nbk",EXT_BCK or EXT_BCK,\
"nbm",EXT_PLU,\
"nbp",EXT_PLU,\
"nbs",EXT_AUD or EXT_BCK,\
"nbt",EXT_GAM,\
"nbu",EXT_BCK,\
"nc",EXT_CAD,\
"ncd",EXT_DSK or EXT_RAS,\
"ncf",EXT_GAM,\
"ncfg",EXT_SET,\
"ncgr",EXT_GAM,\
"nclr",EXT_GAM,\
"nco",EXT_BCK,\
"ncor",EXT_VID,\
"ncr",EXT_RAS,\
"nct",EXT_RAS,\
"ncw",EXT_AUD,\
"nd",EXT_SET,\
"ndc",EXT_SET,\
"ndf",EXT_DBA,\
"ndif",EXT_DSK,\
"nds",EXT_GAM,\
"nef",EXT_CAM,\
"neo",EXT_RAS,\
"nes",EXT_GAM,\
"net",EXT_PLU,\
"neu",EXT_CAD,\
"nexe",EXT_EXE,\
"nfb",EXT_BCK,\
"nfc",EXT_BCK,\
"nff",EXT_3DI,\
"nfi",EXT_DSK,\
"nfo",EXT_GAM or EXT_SYS,\
"nfs11save",EXT_GAM,\
"nftr",EXT_FNT,\
"ngage",EXT_GAM,\
"ngc",EXT_CAD or EXT_GAM,\
"ngd",EXT_CAD,\
"ngp",EXT_GAM,\
"ngt",EXT_GIS,\
"nif",EXT_3DI,\
"nji",EXT_SET,\
"nkb",EXT_AUD,\
"nkc",EXT_AUD,\
"nki",EXT_AUD,\
"nkm",EXT_AUD or EXT_GAM,\
"nkp",EXT_SET,\
"nks",EXT_AUD,\
"nkx",EXT_AUD,\
"nlelem",EXT_GAM,\
"nlm",EXT_RAS,\
"nls",EXT_SYS,\
"nltrack",EXT_GAM,\
"nmap",EXT_GIS,\
"nmbtemplate",EXT_SPR,\
"nmc",EXT_GIS,\
"nmf",EXT_GIS,\
"nml",EXT_GAM,\
"nn",EXT_DSK,\
"npf",EXT_BCK,\
"npl",EXT_AUD or EXT_CAD,\
"npp",EXT_PAG,\
"nps",EXT_BCK,\
"nra",EXT_AUD,\
"nrg",EXT_DSK,\
"nri",EXT_DSK,\
"nrs",EXT_BCK,\
"nrt",EXT_AUD,\
"nrw",EXT_CAM,\
"ns2",EXT_DBA,\
"ns3",EXT_DBA,\
"ns4",EXT_DBA,\
"nsa",EXT_AUD,\
"nsbca",EXT_GAM,\
"nsbmd",EXT_GAM,\
"nsbta",EXT_3DI,\
"nsbtx",EXT_GAM,\
"nscr",EXT_GAM,\
"nsf",EXT_AUD or EXT_DBA,\
"nst",EXT_AUD,\
"nsv",EXT_VID,\
"nt",EXT_SYS,\
"ntc",EXT_SET,\
"ntfs",EXT_SYS,\
"ntn",EXT_AUD,\
"ntrk",EXT_GAM,\
"nts",EXT_SET,\
"numbers-tef",EXT_SPR,\
"numbers",EXT_SPR,\
"nut",EXT_VID,\
"nuv",EXT_VID,\
"nv",EXT_DBA or EXT_GAM,\
"nv2",EXT_DBA or EXT_GIS,\
"nvc",EXT_SET or EXT_VID,\
"nvf",EXT_AUD,\
"nwc",EXT_AUD or EXT_CAD,\
"nwd",EXT_CAD,\
"nwf",EXT_CAD,\
"nwv",EXT_SET,\
"ny",EXT_PLU,\
"nyf",EXT_DBA,\
"o",EXT_DEV,\
"oar",EXT_COM,\
"obi",EXT_SET,\
"obj",EXT_3DI,\
"obp",EXT_3DI,\
"obt",EXT_SET,\
"obz",EXT_3DI,\
"oc3",EXT_RAS,\
"oc4",EXT_RAS,\
"oc5",EXT_RAS,\
"oce",EXT_SET,\
"oci",EXT_RAS,\
"oct",EXT_3DI,\
"odb",EXT_DBA or EXT_DBA,\
"odc",EXT_SET,\
"odf",EXT_GAM,\
"odg",EXT_VEC,\
"odi",EXT_RAS,\
"odm",EXT_AUD,\
"ods",EXT_SPR,\
"oeb",EXT_BCK,\
"oem",EXT_SET,\
"oex",EXT_PLU,\
"off",EXT_3DI,\
"ofr",EXT_AUD,\
"oga",EXT_AUD,\
"ogf",EXT_3DI,\
"ogg",EXT_AUD,\
"ogm",EXT_VID,\
"ogv",EXT_VID,\
"ogx",EXT_VID,\
"ogz",EXT_GAM,\
"okt",EXT_AUD,\
"ola",EXT_PAG,\
"olb",EXT_CAD,\
"old",EXT_BCK,\
"olk14pref",EXT_SET,\
"oma",EXT_AUD,\
"omf",EXT_AUD or EXT_RAS,\
"omg",EXT_AUD,\
"omod",EXT_GAM,\
"omx",EXT_AUD,\
"onepkg",EXT_BCK,\
"onetoc2",EXT_SET,\
"opd",EXT_PAG,\
"opj",EXT_CAD,\
"ops",EXT_SET,\
"opt",EXT_CAD or EXT_SET,\
"options",EXT_SET,\
"opts",EXT_SET,\
"oqy",EXT_DBA,\
"ora",EXT_DBA,\
"orc",EXT_AUD,\
"ore",EXT_EXE,\
"orf",EXT_CAM,\
"ori",EXT_BCK,\
"orig",EXT_BCK,\
"orx",EXT_DBA,\
"osax",EXT_PLU,\
"osb",EXT_GIS,\
"osc",EXT_GIS,\
"osdx",EXT_SET,\
"osm",EXT_GIS,\
"osp",EXT_VID,\
"osr",EXT_GAM,\
"oss",EXT_SET,\
"osx",EXT_EXE,\
"osz",EXT_GAM,\
"ota",EXT_RAS,\
"otb",EXT_RAS,\
"otf",EXT_FNT,\
"otg",EXT_VEC,\
"oti",EXT_RAS,\
"otm",EXT_EXE,\
"otrkey",EXT_VID,\
"ots",EXT_AUD or EXT_SPR,\
"otz",EXT_SET,\
"out",EXT_EXE,\
"ov2",EXT_GIS,\
"ove",EXT_AUD,\
"ovl",EXT_GAM,\
"ovp",EXT_VEC,\
"ovpn",EXT_SET,\
"ovr",EXT_VEC,\
"ovw",EXT_AUD or EXT_AUD,\
"owc",EXT_DBA,\
"oxps",EXT_PAG,\
"oxt",EXT_PLU,\
"oyx",EXT_BCK,\
"oz",EXT_COM,\
"p",EXT_PLU,\
"p01",EXT_DSK or EXT_DSK,\
"p21",EXT_3DI,\
"p2g",EXT_DSK,\
"p2i",EXT_DSK,\
"p2m",EXT_GAM or EXT_SET,\
"p2s",EXT_GAM,\
"p2z",EXT_3DI,\
"p3d",EXT_3DI,\
"p3e",EXT_SET,\
"p3l",EXT_3DI,\
"p3m",EXT_3DI,\
"p3r",EXT_3DI,\
"p3t",EXT_GAM,\
"p65",EXT_PAG,\
"p96",EXT_DBA,\
"p97",EXT_DBA,\
"pa",EXT_PAG,\
"pac",EXT_AUD or EXT_RAS or EXT_VID,\
"pack",EXT_ENC,\
"pack.gz",EXT_COM,\
"package",EXT_COM or EXT_GAM,\
"pae",EXT_COM,\
"paf",EXT_EXE,\
"paf.exe",EXT_EXE,\
"pak",EXT_COM or EXT_GAM or EXT_GAM,\
"pal",EXT_RAS or EXT_SET,\
"pan",EXT_DBA,\
"panic",EXT_SYS,\
"pap",EXT_RAS,\
"papers",EXT_SET,\
"paq",EXT_BCK,\
"paq6",EXT_COM,\
"paq7",EXT_COM,\
"paq8",EXT_COM,\
"paq8f",EXT_COM,\
"par",EXT_3DI or EXT_COM or EXT_GAM or EXT_VID,\
"par2",EXT_COM,\
"partimg",EXT_DSK,\
"pat",EXT_3DI or EXT_AUD or EXT_CAD or EXT_RAS or EXT_SYS or EXT_VEC,\
"pax",EXT_COM,\
"pba",EXT_BCK or EXT_PLU,\
"pbb",EXT_BCK,\
"pbd",EXT_BCK,\
"pbf",EXT_AUD or EXT_BCK or EXT_BCK,\
"pbi",EXT_COM,\
"pbj",EXT_BCK,\
"pbm",EXT_RAS,\
"pbn",EXT_GAM,\
"pbp",EXT_GAM,\
"pbx5script",EXT_BCK,\
"pbxscript",EXT_BCK,\
"pc1",EXT_RAS,\
"pc2",EXT_RAS,\
"pc3",EXT_RAS or EXT_SET,\
"pc6",EXT_CAD,\
"pc7",EXT_CAD,\
"pca",EXT_AUD,\
"pcast",EXT_AUD,\
"pcc",EXT_GAM,\
"pcd",EXT_GAM or EXT_RAS,\
"pcf",EXT_FNT or EXT_GAM,\
"pcg",EXT_AUD,\
"pck",EXT_GAM or EXT_SYS,\
"pcl",EXT_PAG,\
"pcm",EXT_AUD,\
"pcs",EXT_CAD or EXT_VEC,\
"pcsav",EXT_GAM,\
"pcsxstate",EXT_GAM,\
"pct",EXT_PAG,\
"pctl",EXT_SET,\
"pcv",EXT_COM,\
"pcx",EXT_RAS,\
"pd",EXT_AUD or EXT_VEC,\
"pdb",EXT_BCK or EXT_DBA or EXT_DBA,\
"pdc",EXT_ENC,\
"pdd",EXT_RAS,\
"pde",EXT_PAG,\
"pder",EXT_PAG,\
"pdf",EXT_PAG,\
"pdfs",EXT_SET,\
"pdfxml",EXT_PAG,\
"pdg",EXT_PAG,\
"pdh",EXT_PAG,\
"pdi",EXT_DSK,\
"pdm",EXT_DBA or EXT_PAG,\
"pdn",EXT_RAS,\
"pdp",EXT_PAG,\
"pdr",EXT_PAG or EXT_SYS,\
"pds",EXT_VID,\
"pdw",EXT_PAG,\
"pdwr",EXT_PAG,\
"pdz",EXT_PAG,\
"pe4",EXT_RAS or EXT_RAS,\
"pea",EXT_COM,\
"peak",EXT_AUD,\
"pef",EXT_CAM,\
"peg",EXT_GAM,\
"pegn",EXT_GAM,\
"pek",EXT_AUD,\
"pen",EXT_SET,\
"per",EXT_GAM,\
"perfmoncfg",EXT_SET,\
"pet",EXT_COM,\
"pex",EXT_EXE or EXT_PAG,\
"pf",EXT_COM,\
"pfa",EXT_FNT,\
"pfb",EXT_FNT,\
"pfd",EXT_VEC,\
"pff",EXT_PAG,\
"pfi",EXT_RAS,\
"pfl",EXT_PAG or EXT_PLU,\
"pfm",EXT_FNT,\
"pfr",EXT_FNT or EXT_RAS,\
"pfx",EXT_SYS,\
"pgd",EXT_DSK,\
"pgf",EXT_GAM or EXT_RAS,\
"pgi",EXT_VID,\
"pgm",EXT_RAS,\
"pgn",EXT_GAM,\
"pgp",EXT_SET,\
"pgt",EXT_GAM,\
"pgx",EXT_DSK,\
"ph",EXT_SET,\
"phar",EXT_EXE,\
"phb",EXT_SET,\
"phn",EXT_GAM,\
"pho",EXT_AUD or EXT_CAD,\
"photoshow",EXT_VID,\
"phy",EXT_3DI or EXT_AUD,\
"phya",EXT_GAM,\
"phz",EXT_GAM,\
"pi1",EXT_RAS,\
"pi2",EXT_RAS or EXT_RAS,\
"pi3",EXT_RAS,\
"pi4",EXT_RAS,\
"pi5",EXT_RAS,\
"pi6",EXT_RAS,\
"pic",EXT_RAS or EXT_RAS or EXT_RAS,\
"picnc",EXT_RAS,\
"pict",EXT_RAS,\
"pictclipping",EXT_RAS,\
"pid",EXT_SYS,\
"pie",EXT_SET,\
"pif",EXT_EXE,\
"pig",EXT_GAM or EXT_GAM,\
"pigm",EXT_3DI,\
"pigs",EXT_3DI,\
"pim",EXT_COM,\
"pin",EXT_GIS,\
"pip",EXT_SET,\
"pipd",EXT_CAD,\
"pipe",EXT_CAD,\
"pit",EXT_COM or EXT_SYS,\
"piv",EXT_VID,\
"pix",EXT_GIS or EXT_RAS or EXT_RAS,\
"pixadex",EXT_RAS,\
"piz",EXT_COM,\
"pj",EXT_GAM,\
"pjpeg",EXT_RAS,\
"pjpg",EXT_RAS,\
"pjs",EXT_VID,\
"pk",EXT_AUD or EXT_FNT,\
"pk2",EXT_SYS,\
"pk3",EXT_GAM or EXT_GAM,\
"pk4",EXT_GAM,\
"pkf",EXT_AUD,\
"pkg",EXT_3DI or EXT_3DI or EXT_COM or EXT_GAM or EXT_SET,\
"pkm",EXT_GAM,\
"pl",EXT_VEC,\
"pl0",EXT_3DI,\
"pl1",EXT_3DI or EXT_GAM,\
"pl2",EXT_3DI,\
"pla",EXT_AUD or EXT_CAD,\
"playlist",EXT_VID,\
"playmission",EXT_GAM,\
"plf",EXT_GAM,\
"plg",EXT_PLU,\
"plist",EXT_SET,\
"pln",EXT_CAD or EXT_GAM or EXT_PLU,\
"plproj",EXT_VID,\
"plr",EXT_GAM or EXT_GAM,\
"pls",EXT_AUD or EXT_SET,\
"plsc",EXT_EXE,\
"plst",EXT_AUD,\
"plt",EXT_VEC or EXT_VEC,\
"plugin",EXT_PLU or EXT_PLU,\
"plx",EXT_EXE,\
"ply",EXT_3DI or EXT_AUD,\
"pm",EXT_RAS,\
"pm3",EXT_CAD or EXT_RAS,\
"pm4",EXT_PAG,\
"pm5",EXT_PAG,\
"pm6",EXT_PAG,\
"pmc",EXT_SET,\
"pmd",EXT_3DI or EXT_3DI or EXT_PAG or EXT_SPR,\
"pmf",EXT_GIS or EXT_VID,\
"pmg",EXT_RAS or EXT_VEC,\
"pmj",EXT_SET,\
"pml",EXT_SET,\
"pmp",EXT_SET,\
"pmv",EXT_SPR or EXT_VID,\
"pna",EXT_AUD,\
"pnach",EXT_GAM,\
"pnf",EXT_SYS,\
"png",EXT_RAS,\
"pni",EXT_RAS,\
"pnm",EXT_RAS,\
"pno",EXT_AUD,\
"pns",EXT_RAS or EXT_VID,\
"pnt",EXT_RAS,\
"pntg",EXT_RAS,\
"pnz",EXT_DBA,\
"pobj",EXT_VEC,\
"pod",EXT_GAM,\
"pof",EXT_GAM,\
"pog",EXT_GAM,\
"pol",EXT_SYS,\
"pop",EXT_GAM or EXT_RAS,\
"pov",EXT_RAS or EXT_RAS,\
"pp2",EXT_3DI,\
"pp4",EXT_RAS,\
"pp5",EXT_RAS,\
"ppa",EXT_PLU,\
"ppam",EXT_PLU,\
"ppc",EXT_AUD,\
"ppcx",EXT_AUD,\
"ppd",EXT_SYS,\
"ppf",EXT_GAM or EXT_RAS,\
"ppj",EXT_VID,\
"ppm",EXT_RAS or EXT_SYS,\
"ppp",EXT_PAG,\
"ppx",EXT_PAG,\
"ppz",EXT_3DI,\
"pqhero",EXT_GAM,\
"pqi",EXT_DSK,\
"pra",EXT_SET,\
"prc",EXT_3DI or EXT_EXE,\
"pref",EXT_SET or EXT_SET,\
"prefab",EXT_3DI,\
"prefpane",EXT_SYS,\
"prefs",EXT_GAM,\
"prel",EXT_VID,\
"prf",EXT_SET or EXT_SET or EXT_SET or EXT_SET or EXT_SET or EXT_SYS,\
"prfpset",EXT_SET,\
"prg",EXT_AUD or EXT_AUD or EXT_CAD or EXT_EXE or EXT_EXE or EXT_GAM,\
"printerexport",EXT_SYS,\
"prk",EXT_GAM,\
"prm",EXT_3DI or EXT_GIS or EXT_PLU or EXT_SET,\
"prn",EXT_PAG,\
"pro",EXT_CAD or EXT_VID,\
"profile",EXT_GAM or EXT_SET or EXT_SYS,\
"profimail",EXT_SET,\
"propdesc",EXT_SET,\
"properties",EXT_GAM or EXT_SET,\
"props",EXT_SET,\
"prproj",EXT_VID,\
"prs",EXT_SET,\
"prst",EXT_SET,\
"prt",EXT_CAD or EXT_CAD or EXT_CAD or EXT_SYS,\
"prtl",EXT_VID,\
"prv",EXT_3DI or EXT_BCK,\
"prw",EXT_RAS,\
"prx",EXT_GAM or EXT_SET,\
"ps",EXT_VEC,\
"ps1",EXT_EXE or EXT_SYS,\
"ps1xml",EXT_SET,\
"ps2",EXT_GAM or EXT_GAM or EXT_SYS,\
"psa",EXT_3DI or EXT_BCK,\
"psb",EXT_RAS or EXT_VID,\
"psc1",EXT_SET,\
"psd",EXT_RAS,\
"psdl",EXT_GAM,\
"psdx",EXT_RAS,\
"pse",EXT_RAS,\
"pset",EXT_PLU,\
"psf",EXT_AUD or EXT_CAD or EXT_RAS or EXT_SET,\
"psg",EXT_PAG,\
"psh",EXT_VID,\
"psid",EXT_VEC,\
"psk",EXT_3DI,\
"psm",EXT_AUD or EXT_CAD,\
"psp",EXT_RAS or EXT_SET,\
"pspbrush",EXT_RAS,\
"pspimage",EXT_RAS,\
"psr",EXT_PAG,\
"pss",EXT_CAD or EXT_GAM,\
"pssd",EXT_VID,\
"pssg",EXT_GAM,\
"psu",EXT_CAD or EXT_GAM,\
"psv",EXT_CAD or EXT_GAM,\
"psw6",EXT_ENC,\
"psx",EXT_GAM,\
"psy",EXT_AUD or EXT_SET,\
"psys",EXT_GAM,\
"psz",EXT_COM,\
"ptf",EXT_AUD or EXT_SET,\
"ptg",EXT_RAS,\
"ptk",EXT_RAS,\
"ptm",EXT_AUD or EXT_GIS,\
"pts",EXT_AUD,\
"ptt",EXT_GIS,\
"ptx",EXT_PAG or EXT_RAS or EXT_RAS,\
"pub",EXT_PAG,\
"pup",EXT_COM or EXT_COM,\
"purblepairssave-ms",EXT_GAM,\
"purbleshopsave-ms",EXT_GAM,\
"puz",EXT_COM or EXT_GAM,\
"pva",EXT_VID,\
"pvc",EXT_AUD or EXT_BCK,\
"pvd",EXT_EXE,\
"pvm",EXT_DSK,\
"pvpf",EXT_GAM,\
"pvr",EXT_RAS or EXT_VID,\
"pvs",EXT_SET,\
"pwa",EXT_COM,\
"pwc",EXT_EXE,\
"pwd",EXT_CAD,\
"pwf",EXT_GAM,\
"pwl",EXT_SYS,\
"pwp",EXT_RAS,\
"pws",EXT_SET or EXT_VEC,\
"pwt",EXT_CAD or EXT_PAG,\
"px",EXT_RAS,\
"pxb",EXT_SET,\
"pxd",EXT_RAS,\
"pxg",EXT_SET,\
"pxi",EXT_DSK,\
"pxicon",EXT_RAS,\
"pxm",EXT_RAS,\
"pxp",EXT_GAM,\
"pxr",EXT_RAS,\
"pxv",EXT_VID,\
"pyc",EXT_EXE,\
"pyo",EXT_EXE,\
"pz2",EXT_3DI,\
"pz3",EXT_3DI,\
"pzl",EXT_GAM,\
"pzp",EXT_GAM or EXT_RAS,\
"pzz",EXT_3DI,\
"q1q",EXT_PLU,\
"q2d",EXT_SET,\
"q2q",EXT_PLU,\
"q3c",EXT_PAG,\
"q4q",EXT_PLU,\
"q5r",EXT_PLU,\
"q7q",EXT_PLU,\
"q8r",EXT_PLU,\
"q9r",EXT_PLU,\
"q9s",EXT_PLU,\
"qar",EXT_PLU,\
"qbb",EXT_BCK,\
"qbk",EXT_BCK,\
"qbm",EXT_BCK,\
"qbmb",EXT_BCK,\
"qbmd",EXT_BCK,\
"qbx",EXT_BCK,\
"qc",EXT_3DI or EXT_GAM,\
"qcp",EXT_AUD,\
"qda",EXT_COM,\
"qdf",EXT_PAG,\
"qdp",EXT_GAM,\
"qf",EXT_SET,\
"qic",EXT_BCK,\
"qif",EXT_RAS,\
"qit",EXT_EXE,\
"qlgenerator",EXT_PLU,\
"qmg",EXT_RAS,\
"qpm",EXT_CAD,\
"qpt",EXT_PAG,\
"qpw",EXT_SPR,\
"qpx",EXT_EXE or EXT_PLU or EXT_SET,\
"qrc",EXT_SET,\
"qry",EXT_DBA,\
"qsf",EXT_BCK,\
"qss",EXT_SET,\
"qt",EXT_VID,\
"qtch",EXT_VID,\
"qti",EXT_RAS,\
"qtif",EXT_RAS,\
"qtindex",EXT_VID,\
"qtl",EXT_VID,\
"qtm",EXT_VID,\
"qtp",EXT_SET,\
"qtr",EXT_PLU,\
"qtx",EXT_PLU,\
"qtz",EXT_VID,\
"qv~",EXT_BCK,\
"qvd",EXT_DBA,\
"qvm",EXT_GAM or EXT_SYS,\
"qvpp",EXT_SET,\
"qvt",EXT_SET,\
"qwd",EXT_GAM,\
"qxb",EXT_PAG,\
"qxd",EXT_PAG,\
"qxp",EXT_PAG,\
"qxt",EXT_PAG,\
"r",EXT_AUD,\
"r0",EXT_COM,\
"r00",EXT_COM,\
"r01",EXT_COM,\
"r02",EXT_COM,\
"r03",EXT_COM,\
"r1",EXT_COM,\
"r1m",EXT_AUD,\
"r2",EXT_COM,\
"r21",EXT_COM,\
"r30",EXT_COM,\
"r3d",EXT_VID,\
"ra",EXT_AUD,\
"rad",EXT_3DI or EXT_3DI or EXT_SET,\
"radq",EXT_GAM,\
"raf",EXT_CAM,\
"ram",EXT_AUD,\
"rar",EXT_COM,\
"ras",EXT_GAM or EXT_RAS,\
"raskinplace",EXT_SET,\
"ratdvd",EXT_DSK,\
"raw",EXT_AUD or EXT_CAM,\
"rax",EXT_AUD,\
"ray",EXT_3DI,\
"rb",EXT_SET,\
"rb4",EXT_PAG or EXT_SET,\
"rbc",EXT_BCK,\
"rbf",EXT_BCK or EXT_BCK or EXT_DBA,\
"rbk",EXT_BCK,\
"rbs",EXT_AUD or EXT_AUD or EXT_BCK,\
"rbx",EXT_EXE,\
"rbxl",EXT_GAM,\
"rbxm",EXT_GAM,\
"rc1",EXT_SYS,\
"rc2",EXT_SYS,\
"rcd",EXT_CAD or EXT_VID,\
"rcf",EXT_SET,\
"rcl",EXT_DSK or EXT_RAS,\
"rco",EXT_SYS,\
"rcproject",EXT_VID,\
"rcs",EXT_3DI,\
"rct",EXT_SET,\
"rcu",EXT_RAS,\
"rcy",EXT_AUD,\
"rda",EXT_GAM,\
"rdb",EXT_BCK or EXT_VID,\
"rdc",EXT_GIS,\
"rdf",EXT_CAD or EXT_DSK or EXT_GIS or EXT_SET or EXT_SPR,\
"rdi",EXT_ENC or EXT_SET,\
"rdl",EXT_VEC,\
"rdo",EXT_SET,\
"rdp",EXT_SET,\
"rds",EXT_3DI,\
"rec",EXT_VID,\
"record",EXT_AUD,\
"red",EXT_CAD,\
"ref",EXT_GIS,\
"reg",EXT_SET or EXT_SYS,\
"regtrans-ms",EXT_SYS,\
"rels",EXT_PAG,\
"rep",EXT_GAM or EXT_GAM,\
"res",EXT_GAM,\
"resmoncfg",EXT_SET,\
"rev",EXT_COM,\
"rex",EXT_AUD,\
"rez",EXT_GAM or EXT_PLU,\
"rfa",EXT_GAM,\
"rfd",EXT_GAM or EXT_PAG,\
"rfgs_pc",EXT_GAM,\
"rfl",EXT_AUD,\
"rfm",EXT_GAM,\
"rfq",EXT_SET,\
"rft",EXT_3DI,\
"rfw",EXT_SYS,\
"rgb",EXT_RAS or EXT_RAS,\
"rgmb",EXT_BCK,\
"rgn",EXT_GIS,\
"rgp",EXT_GAM,\
"rgs",EXT_EXE,\
"rgss2a",EXT_GAM,\
"rhp",EXT_PLU,\
"ric",EXT_RAS,\
"rif",EXT_RAS,\
"riff",EXT_RAS,\
"rig",EXT_3DI or EXT_CAD,\
"rim",EXT_GAM,\
"rip",EXT_AUD,\
"rix",EXT_RAS,\
"rk",EXT_COM,\
"rkp",EXT_GAM,\
"rl",EXT_GAM,\
"rle",EXT_GAM or EXT_RAS,\
"rle.gz",EXT_GAM,\
"rlf",EXT_PAG,\
"rli",EXT_RAS,\
"rll",EXT_SET,\
"rm",EXT_VID,\
"rmbak",EXT_BCK,\
"rmd",EXT_VID or EXT_VID,\
"rmf",EXT_AUD,\
"rmi",EXT_AUD,\
"rmj",EXT_AUD,\
"rml",EXT_CAD or EXT_SET,\
"rmm",EXT_AUD,\
"rmp",EXT_GIS or EXT_VID,\
"rmr",EXT_PAG,\
"rms",EXT_SET or EXT_VID,\
"rmskin",EXT_SET,\
"rmt",EXT_SYS,\
"rmv",EXT_VID,\
"rmvb",EXT_VID,\
"rmx",EXT_AUD,\
"rnc",EXT_COM,\
"rng",EXT_AUD,\
"rns",EXT_AUD,\
"rnx",EXT_SET,\
"rock",EXT_PLU,\
"rod",EXT_DBA,\
"rol",EXT_AUD,\
"rom",EXT_GAM,\
"roq",EXT_VID,\
"rot",EXT_GAM,\
"rox",EXT_EXE,\
"rp",EXT_VID,\
"rp2",EXT_GAM,\
"rp9",EXT_COM,\
"rpb",EXT_SET,\
"rpd",EXT_DBA,\
"rpf",EXT_GAM or EXT_RAS,\
"rpj",EXT_EXE,\
"rpk",EXT_SET,\
"rpl",EXT_GAM or EXT_GAM,\
"rplib",EXT_PLU,\
"rpm",EXT_COM or EXT_PLU,\
"rps",EXT_SET,\
"rptr",EXT_PAG,\
"rpy",EXT_GAM or EXT_GAM,\
"rpyc",EXT_GAM,\
"rra",EXT_CAD,\
"rrd",EXT_GIS,\
"rri",EXT_RAS,\
"rrr",EXT_BCK or EXT_SET,\
"rs",EXT_CAD or EXT_RAS or EXT_SYS,\
"rs2",EXT_GAM,\
"rsb",EXT_RAS,\
"rsd",EXT_DBA,\
"rsdf",EXT_ENC,\
"rsm",EXT_CAD or EXT_PAG,\
"rsn",EXT_AUD,\
"rso",EXT_AUD,\
"rsr",EXT_RAS,\
"rst",EXT_GIS,\
"rsx",EXT_VID,\
"rtd",EXT_CAD,\
"rte",EXT_COM,\
"rti",EXT_AUD,\
"rtm",EXT_AUD,\
"rts",EXT_AUD or EXT_SET or EXT_VID or EXT_VID,\
"ruf",EXT_SYS,\
"ruleset",EXT_SET,\
"rum",EXT_VID,\
"run",EXT_EXE or EXT_GAM,\
"rv",EXT_VID,\
"rvdata",EXT_GAM,\
"rvl",EXT_VID,\
"rvproj",EXT_GAM,\
"rvx",EXT_AUD,\
"rw2",EXT_CAM,\
"rwl",EXT_CAM,\
"rwplugin",EXT_PLU,\
"rws",EXT_GAM,\
"rwstyle",EXT_SET,\
"rx2",EXT_AUD,\
"rxdata",EXT_GAM,\
"rxe",EXT_EXE,\
"rz",EXT_COM,\
"rzk",EXT_ENC,\
"rzx",EXT_ENC,\
"s",EXT_3DI,\
"s00",EXT_COM,\
"s01",EXT_COM,\
"s02",EXT_COM,\
"s10",EXT_GAM,\
"s2a",EXT_EXE,\
"s2m",EXT_GAM,\
"s2mh",EXT_GAM,\
"s2ml",EXT_SET,\
"s2mv",EXT_RAS,\
"s2qh",EXT_SET,\
"s2ql",EXT_SET,\
"s2z",EXT_GAM,\
"s3i",EXT_AUD,\
"s3m",EXT_AUD,\
"s3z",EXT_AUD,\
"s4m",EXT_GAM,\
"s5x",EXT_GAM,\
"s7z",EXT_COM,\
"sa1",EXT_GAM,\
"sa9",EXT_PLU,\
"sab",EXT_CAD,\
"sad",EXT_GAM,\
"saf",EXT_AUD or EXT_GIS,\
"safariextz",EXT_PLU,\
"sam",EXT_AUD,\
"sap",EXT_AUD,\
"sar",EXT_COM or EXT_RAS,\
"sat",EXT_CAD,\
"sav",EXT_BCK or EXT_GAM or EXT_GAM or EXT_GAM,\
"savedsearch",EXT_SYS,\
"saver",EXT_SYS,\
"sb",EXT_AUD,\
"sbb",EXT_BCK,\
"sbf",EXT_DBA or EXT_SYS,\
"sbg",EXT_AUD,\
"sbi",EXT_AUD,\
"sbk",EXT_AUD or EXT_PAG or EXT_VID,\
"sbn",EXT_GIS or EXT_GIS or EXT_SYS,\
"sbp",EXT_CAD or EXT_RAS,\
"sbs",EXT_BCK or EXT_EXE,\
"sbt",EXT_VID,\
"sbv",EXT_PAG or EXT_SET,\
"sbx",EXT_COM,\
"sc2",EXT_AUD or EXT_GAM,\
"sc2archive",EXT_GAM,\
"sc2assets",EXT_GAM,\
"sc2bank",EXT_GAM,\
"sc2data",EXT_GAM,\
"sc2ma",EXT_GAM,\
"sc2map",EXT_GAM,\
"sc2mod",EXT_GAM,\
"sc2replay",EXT_GAM,\
"sc2save",EXT_GAM,\
"sc2scene",EXT_GAM,\
"sc3",EXT_GAM,\
"sc4",EXT_GAM or EXT_GAM,\
"sc4desc",EXT_GAM,\
"sc4lot",EXT_GAM,\
"sc4model",EXT_3DI,\
"sc5",EXT_GAM,\
"sc6",EXT_GAM,\
"sca",EXT_EXE,\
"scacfg",EXT_SET,\
"scad",EXT_CAD,\
"scap",EXT_SYS,\
"scar",EXT_EXE,\
"scb",EXT_EXE,\
"scc",EXT_VID,\
"scea",EXT_GAM,\
"scene",EXT_GAM,\
"scf",EXT_GAM or EXT_SYS,\
"scg",EXT_RAS,\
"sch",EXT_CAD or EXT_SET,\
"schemas",EXT_SYS,\
"schematic",EXT_GAM,\
"sci",EXT_RAS,\
"scm",EXT_GAM or EXT_GAM or EXT_PLU or EXT_VID or EXT_VID,\
"scn",EXT_GAM or EXT_GAM or EXT_GAM or EXT_RAS or EXT_VID,\
"sco",EXT_DSK,\
"scp",EXT_RAS,\
"scpcfg",EXT_SET,\
"scpt",EXT_EXE,\
"scr",EXT_EXE or EXT_SYS,\
"screenflow",EXT_VID,\
"script",EXT_EXE,\
"scs",EXT_GAM or EXT_GAM,\
"scs11",EXT_AUD,\
"sct",EXT_EXE or EXT_RAS,\
"scu",EXT_RAS,\
"scv",EXT_VEC,\
"scx",EXT_DBA or EXT_GAM or EXT_GAM,\
"sd",EXT_AUD or EXT_AUD,\
"sd2",EXT_AUD,\
"sd2f",EXT_AUD,\
"sda",EXT_VEC,\
"sdat",EXT_AUD,\
"sdb",EXT_3DI or EXT_DBA or EXT_DBA or EXT_DBA or EXT_SYS,\
"sdc",EXT_BCK or EXT_COM or EXT_SPR,\
"sdf",EXT_DBA or EXT_GAM or EXT_GIS,\
"sdg",EXT_CAD,\
"sdi",EXT_DSK,\
"sdii",EXT_AUD,\
"sdm",EXT_GIS,\
"sdn",EXT_COM,\
"sdoc",EXT_ENC,\
"sdr",EXT_RAS,\
"sds",EXT_AUD,\
"sdsk",EXT_DSK,\
"sdt",EXT_AUD or EXT_GAM or EXT_PAG or EXT_SYS,\
"sdw",EXT_GIS,\
"sdx",EXT_AUD,\
"sdz",EXT_GAM,\
"sea",EXT_COM,\
"searchconnector-ms",EXT_SYS,\
"sec",EXT_VID,\
"sed",EXT_SET,\
"sedprj",EXT_VID,\
"seed",EXT_EXE,\
"seestyle",EXT_SET,\
"sef",EXT_ENC,\
"seg",EXT_AUD,\
"sen",EXT_COM,\
"sep",EXT_RAS,\
"seplugin",EXT_PLU,\
"seq",EXT_AUD or EXT_VID,\
"sequ",EXT_SET,\
"ses",EXT_AUD,\
"session",EXT_3DI,\
"sesx",EXT_AUD,\
"set",EXT_SET or EXT_SET,\
"settings",EXT_GAM or EXT_SET,\
"sew",EXT_CAD,\
"sf",EXT_AUD,\
"sf2",EXT_AUD,\
"sfap0",EXT_AUD,\
"sfar",EXT_GAM,\
"sfb",EXT_GAM,\
"sfc",EXT_GAM or EXT_GAM or EXT_RAS,\
"sfcache",EXT_SYS,\
"sfd",EXT_FNT or EXT_VID,\
"sff",EXT_GAM or EXT_RAS,\
"sfk",EXT_AUD,\
"sfl",EXT_AUD,\
"sfo",EXT_GAM or EXT_SET,\
"sfs",EXT_AUD or EXT_COM,\
"sfvidcap",EXT_VID,\
"sfw",EXT_RAS,\
"sfx",EXT_COM,\
"sga",EXT_GAM,\
"sgaa",EXT_GAM,\
"sgb",EXT_GAM or EXT_GAM,\
"sgi",EXT_RAS,\
"sgm",EXT_GAM,\
"sgn",EXT_3DI,\
"sgr",EXT_GAM,\
"sgt",EXT_SET,\
"sgz",EXT_ENC,\
"sh",EXT_COM,\
"sh2",EXT_GAM,\
"sh3d",EXT_3DI,\
"sh3f",EXT_3DI,\
"shader",EXT_GAM,\
"shar",EXT_COM,\
"shb",EXT_EXE,\
"shd",EXT_SYS,\
"shg",EXT_RAS,\
"shh",EXT_SET,\
"shk",EXT_COM,\
"shn",EXT_AUD,\
"shp",EXT_3DI or EXT_GIS,\
"shpa",EXT_GAM,\
"shr",EXT_COM,\
"shsh",EXT_SYS,\
"shx",EXT_CAD,\
"shy",EXT_ENC,\
"si",EXT_3DI,\
"sib",EXT_AUD,\
"sid",EXT_AUD or EXT_GAM or EXT_RAS,\
"sif",EXT_SET,\
"sig",EXT_RAS,\
"sii",EXT_GAM,\
"sim",EXT_BCK or EXT_RAS,\
"simg",EXT_DSK,\
"sims2pack",EXT_GAM,\
"sims3pack",EXT_GAM,\
"sis",EXT_BCK or EXT_DBA,\
"sit",EXT_COM,\
"sitx",EXT_COM,\
"siv",EXT_VID,\
"sjd",EXT_PAG,\
"sk1",EXT_VEC,\
"sk2",EXT_VEC,\
"skb",EXT_BCK,\
"sketch",EXT_VEC,\
"skf",EXT_CAD,\
"ski",EXT_SET,\
"skin",EXT_SET or EXT_SET,\
"skitch",EXT_RAS,\
"skl",EXT_3DI,\
"skm",EXT_RAS,\
"skn",EXT_SET,\
"skp",EXT_3DI,\
"skypeemoticonset",EXT_RAS,\
"skz",EXT_SET,\
"sl",EXT_SET,\
"sld",EXT_GIS or EXT_RAS,\
"sldasm",EXT_CAD,\
"slddrt",EXT_VEC,\
"slddrw",EXT_CAD,\
"sldprt",EXT_CAD,\
"slp",EXT_AUD,\
"slt",EXT_SET,\
"slx",EXT_AUD,\
"sm",EXT_GAM,\
"sma",EXT_AUD,\
"smc",EXT_GAM,\
"smd",EXT_3DI or EXT_GAM,\
"smf",EXT_AUD or EXT_VEC,\
"smi",EXT_DSK or EXT_VID or EXT_VID,\
"smil",EXT_VID,\
"smk",EXT_VID,\
"sml",EXT_VID,\
"smm",EXT_EXE or EXT_GIS,\
"smp",EXT_AUD or EXT_AUD or EXT_GIS or EXT_RAS,\
"smpd",EXT_GAM,\
"sms",EXT_GAM,\
"smt",EXT_SET,\
"smv",EXT_VID,\
"smzip",EXT_GAM,\
"sn1",EXT_BCK,\
"sn2",EXT_BCK,\
"sna",EXT_BCK,\
"snd",EXT_AUD or EXT_AUD or EXT_AUD,\
"snda",EXT_GAM,\
"sng",EXT_AUD or EXT_AUD,\
"snk",EXT_ENC,\
"snp",EXT_PAG,\
"sns",EXT_AUD or EXT_BCK,\
"snx",EXT_SET,\
"so-abi",EXT_PLU,\
"so.0",EXT_SYS,\
"sob",EXT_RAS,\
"sol",EXT_SET,\
"solitairesave-ms",EXT_GAM,\
"sopt",EXT_DSK,\
"sou",EXT_AUD,\
"sounds",EXT_GAM,\
"sow",EXT_GAM,\
"sp",EXT_PAG,\
"sp2",EXT_GAM,\
"sp3",EXT_GIS,\
"spa",EXT_RAS,\
"sparc",EXT_PLU,\
"sparsebundle",EXT_DSK,\
"sparseimage",EXT_DSK,\
"spb",EXT_GAM,\
"spc",EXT_GAM or EXT_RAS,\
"spd",EXT_ENC or EXT_PLU,\
"spdf",EXT_ENC,\
"spe",EXT_PLU or EXT_RAS,\
"spf",EXT_BCK or EXT_SET,\
"spfx",EXT_SET,\
"spg",EXT_BCK,\
"sph",EXT_AUD or EXT_RAS,\
"spi",EXT_BCK,\
"spidersolitairesave-ms",EXT_GAM,\
"spiff",EXT_RAS,\
"spj",EXT_RAS or EXT_SET,\
"spk",EXT_GAM,\
"spl",EXT_SYS or EXT_VID,\
"spo",EXT_GAM,\
"spp",EXT_RAS,\
"sppack",EXT_AUD,\
"spq",EXT_DBA,\
"spr",EXT_EXE or EXT_RAS,\
"sprg",EXT_AUD,\
"sprite",EXT_GAM or EXT_RAS,\
"sps",EXT_BCK or EXT_GAM or EXT_GAM,\
"spt",EXT_CAD or EXT_COM,\
"spu",EXT_RAS,\
"spx",EXT_AUD,\
"sqb",EXT_BCK,\
"sqfs",EXT_DSK,\
"sql",EXT_DBA,\
"sqlite",EXT_DBA,\
"sqlite3",EXT_DBA,\
"sqlitedb",EXT_DBA,\
"sqm",EXT_GAM or EXT_SYS,\
"sqx",EXT_COM,\
"sqz",EXT_VID,\
"sr",EXT_RAS,\
"sr2",EXT_CAM,\
"srep",EXT_COM,\
"srf",EXT_3DI or EXT_CAM or EXT_SET,\
"srm",EXT_GAM,\
"srr",EXT_BCK,\
"srs",EXT_SET,\
"srt",EXT_VID,\
"srt0",EXT_GAM,\
"srw",EXT_CAM,\
"ssa",EXT_GAM,\
"sseq",EXT_AUD or EXT_AUD,\
"ssf",EXT_GIS or EXT_VID,\
"ssl",EXT_SET,\
"ssl2",EXT_SET,\
"ssm",EXT_VID,\
"ssnd",EXT_AUD,\
"sss",EXT_SET or EXT_SET,\
"sst",EXT_GAM,\
"st",EXT_DSK,\
"sta",EXT_GAM,\
"stap",EXT_AUD,\
"startupinfo",EXT_SET,\
"stb",EXT_SET,\
"stc",EXT_3DI or EXT_SET or EXT_SPR,\
"std",EXT_VEC,\
"ste",EXT_RAS or EXT_SET,\
"steamstart",EXT_GAM,\
"step",EXT_3DI,\
"stf",EXT_SET,\
"stg",EXT_BCK,\
"stl",EXT_CAD or EXT_GAM or EXT_VID,\
"stm",EXT_AUD,\
"sto",EXT_3DI,\
"storyisttheme",EXT_SET,\
"stp",EXT_3DI,\
"str",EXT_GAM or EXT_SYS or EXT_VID,\
"stsg",EXT_GAM,\
"stt",EXT_GIS or EXT_SET,\
"stwm",EXT_GAM,\
"stx",EXT_AUD or EXT_VID,\
"sty",EXT_AUD or EXT_AUD or EXT_SET,\
"style",EXT_GIS or EXT_SET,\
"sub",EXT_DSK or EXT_GAM,\
"sud",EXT_GAM,\
"suf",EXT_ENC,\
"suit",EXT_FNT,\
"sumo",EXT_RAS,\
"sun",EXT_RAS,\
"suniff",EXT_RAS,\
"sup",EXT_RAS,\
"sv$",EXT_BCK,\
"sv2i",EXT_BCK,\
"sv5",EXT_GAM or EXT_GAM,\
"sv6",EXT_GAM,\
"sva",EXT_RAS,\
"svd",EXT_AUD or EXT_CAD,\
"sve",EXT_GAM,\
"svf",EXT_VEC,\
"svg",EXT_VEC,\
"svgz",EXT_VEC,\
"svi",EXT_VID,\
"svs",EXT_GAM,\
"svx",EXT_AUD or EXT_GIS,\
"sw",EXT_AUD,\
"sw2",EXT_SET,\
"swa",EXT_AUD,\
"swav",EXT_AUD,\
"swc",EXT_GAM,\
"swf",EXT_VID,\
"swi",EXT_VID,\
"switch",EXT_ENC,\
"swm",EXT_DSK,\
"swp",EXT_SYS,\
"swt",EXT_VID,\
"swv",EXT_GAM,\
"sww",EXT_GAM,\
"sxc",EXT_SPR,\
"sxd",EXT_GIS or EXT_VEC,\
"sxt",EXT_AUD,\
"sy_",EXT_COM,\
"syb",EXT_GAM,\
"syh",EXT_AUD,\
"syn",EXT_AUD or EXT_AUD,\
"sys",EXT_SYS or EXT_SYS,\
"system",EXT_GAM,\
"syw",EXT_AUD,\
"syx",EXT_AUD,\
"sz",EXT_SET,\
"szs",EXT_GAM,\
"t2b",EXT_RAS,\
"t3001",EXT_CAD,\
"t3d",EXT_3DI or EXT_3DI or EXT_SET,\
"t3x",EXT_PLU,\
"t64",EXT_DSK,\
"taac",EXT_RAS,\
"tab",EXT_GIS,\
"taf",EXT_GAM,\
"tak",EXT_AUD or EXT_AUD or EXT_CAD,\
"tao",EXT_DSK,\
"tap",EXT_DSK or EXT_GAM,\
"tar.gz",EXT_COM,\
"tar.gz2",EXT_COM,\
"tar.lzma",EXT_COM,\
"tar.xz",EXT_COM,\
"taz",EXT_COM,\
"tb0",EXT_RAS,\
"tbk",EXT_BCK,\
"tbm",EXT_GAM,\
"tbn",EXT_RAS,\
"tbp",EXT_CAD or EXT_PLU,\
"tbz",EXT_COM,\
"tbz2",EXT_COM,\
"tc",EXT_DSK,\
"tc2",EXT_CAD,\
"tc3",EXT_CAD,\
"tcd",EXT_CAD,\
"tcm",EXT_CAD,\
"tcp",EXT_EXE,\
"tct",EXT_CAD,\
"tcw",EXT_CAD,\
"tcx",EXT_CAD,\
"td0",EXT_AUD or EXT_DSK,\
"td4",EXT_GAM,\
"td6",EXT_GAM,\
"tda3mt",EXT_VID,\
"tdb",EXT_BCK or EXT_GAM,\
"tddd",EXT_3DI,\
"tdf",EXT_SET,\
"tdx",EXT_VID,\
"te",EXT_DBA,\
"teacher",EXT_DBA,\
"ted",EXT_GAM or EXT_GAM,\
"terminal",EXT_SET,\
"tex",EXT_RAS,\
"tex0",EXT_GAM,\
"tfc",EXT_RAS,\
"tfm",EXT_FNT,\
"tfmx",EXT_AUD,\
"tfr",EXT_GAM,\
"tfrd",EXT_GIS,\
"tfw",EXT_GIS,\
"tg",EXT_AUD or EXT_COM,\
"tg4",EXT_RAS,\
"tga",EXT_RAS,\
"tgz",EXT_COM,\
"th",EXT_GIS,\
"tha",EXT_SYS,\
"the",EXT_SET,\
"theme",EXT_SET or EXT_SET or EXT_SYS,\
"themepack",EXT_SET,\
"thm",EXT_EXE or EXT_RAS or EXT_RAS,\
"thmx",EXT_SET,\
"thp",EXT_VID,\
"thumb",EXT_RAS,\
"thx",EXT_AUD,\
"tib",EXT_DSK,\
"tif",EXT_RAS or EXT_RAS,\
"tiff",EXT_RAS,\
"tig",EXT_BCK,\
"tim",EXT_GAM,\
"tis",EXT_BCK,\
"tivo",EXT_VID,\
"tix",EXT_VID,\
"tja",EXT_GAM,\
"tjc",EXT_GAM,\
"tjp",EXT_RAS,\
"tko",EXT_PLU,\
"tkr",EXT_GAM,\
"tlc",EXT_VEC,\
"tlg",EXT_BCK,\
"tlk",EXT_GAM,\
"tlo",EXT_SET,\
"tlz",EXT_COM,\
"tlzma",EXT_COM,\
"tm2",EXT_AUD or EXT_RAS,\
"tm8",EXT_AUD,\
"tmbundle",EXT_PLU,\
"tmc",EXT_AUD,\
"tmd",EXT_3DI or EXT_DBA,\
"tme",EXT_3DI,\
"tmo",EXT_3DI,\
"tmp",EXT_BCK,\
"tmr",EXT_BCK,\
"tms",EXT_EXE,\
"tmtheme",EXT_SET,\
"tn",EXT_RAS,\
"tn1",EXT_RAS,\
"tn2",EXT_RAS,\
"tn3",EXT_RAS,\
"tne",EXT_VEC,\
"tny",EXT_RAS,\
"toast",EXT_DSK,\
"toc",EXT_AUD or EXT_DSK or EXT_GAM,\
"tod",EXT_VID,\
"top",EXT_CAD,\
"topprj",EXT_CAD,\
"topviw",EXT_CAD,\
"tor",EXT_GAM,\
"tp",EXT_VID,\
"tp0",EXT_VID,\
"tp3",EXT_PAG,\
"tp4",EXT_GAM,\
"tpark",EXT_SET,\
"tpd",EXT_VID,\
"tpf",EXT_RAS or EXT_SET,\
"tpi",EXT_PLU or EXT_RAS,\
"tpl",EXT_SET or EXT_SET or EXT_VEC,\
"tpr",EXT_VID,\
"tps",EXT_3DI or EXT_DBA or EXT_RAS,\
"trc",EXT_DBA,\
"tri",EXT_3DI or EXT_3DI,\
"trif",EXT_RAS,\
"trk",EXT_GAM,\
"trm",EXT_DBA,\
"trn",EXT_BCK,\
"trp",EXT_VID,\
"truck",EXT_3DI,\
"trx",EXT_SET,\
"ts",EXT_VID,\
"ts1",EXT_3DI,\
"tsf",EXT_CAD,\
"tsk",EXT_SET,\
"tsm",EXT_SET,\
"tsp",EXT_AUD or EXT_VID,\
"tst",EXT_SET,\
"tsz",EXT_SET,\
"tta",EXT_AUD,\
"ttarch",EXT_GAM,\
"ttbk",EXT_BCK,\
"ttc",EXT_FNT,\
"tte",EXT_FNT,\
"ttf",EXT_FNT,\
"ttm",EXT_GAM,\
"tts",EXT_SET,\
"ttxt",EXT_VID,\
"tub",EXT_RAS,\
"tun",EXT_AUD,\
"tut",EXT_GAM,\
"tvs",EXT_VID,\
"twc",EXT_SET,\
"twt",EXT_GAM,\
"tx_",EXT_COM,\
"txf",EXT_FNT,\
"txw",EXT_AUD,\
"txz",EXT_COM,\
"typeit4me",EXT_SET,\
"tz",EXT_COM,\
"tzx",EXT_DSK,\
"u",EXT_AUD or EXT_GAM or EXT_RAS,\
"u3d",EXT_3DI,\
"u3p",EXT_EXE,\
"u8",EXT_AUD,\
"uax",EXT_AUD,\
"ub",EXT_AUD,\
"uc",EXT_GAM,\
"uc2",EXT_COM,\
"uci",EXT_BCK,\
"ucl",EXT_GAM,\
"ucm",EXT_GAM,\
"uct",EXT_SET,\
"udb",EXT_DBA,\
"udcx",EXT_SET,\
"udf",EXT_DSK or EXT_EXE,\
"udk",EXT_GAM,\
"udl",EXT_DBA,\
"uea",EXT_ENC,\
"ufo",EXT_RAS,\
"ufr",EXT_VEC,\
"ufs",EXT_DSK,\
"ufs.uzip",EXT_COM,\
"uha",EXT_COM,\
"uibak",EXT_DSK,\
"uif",EXT_DSK,\
"uis",EXT_SET,\
"ukx",EXT_GAM,\
"ulaw",EXT_AUD,\
"ult",EXT_AUD,\
"ulw",EXT_AUD,\
"umod",EXT_GAM,\
"ums",EXT_3DI,\
"umx",EXT_GAM,\
"uni",EXT_AUD,\
"unity",EXT_GAM,\
"unity3d",EXT_GAM,\
"unr",EXT_GAM,\
"unt",EXT_CAD,\
"uop",EXT_GAM,\
"uos",EXT_SPR,\
"updatr",EXT_GAM,\
"upf",EXT_CAD or EXT_SET,\
"upk",EXT_GAM,\
"upx",EXT_EXE,\
"uqm",EXT_GAM,\
"urt",EXT_RAS,\
"usa",EXT_GAM,\
"user",EXT_SET,\
"userprofile",EXT_SET,\
"usertile-ms",EXT_RAS,\
"usf",EXT_AUD or EXT_SET or EXT_VID,\
"usflib",EXT_AUD,\
"usm",EXT_VID,\
"usr",EXT_DBA,\
"usx",EXT_GAM,\
"ut2",EXT_GAM,\
"ut2mod",EXT_GAM,\
"ut3",EXT_GAM,\
"ut4mod",EXT_GAM,\
"ut8",EXT_GAM,\
"utc",EXT_GAM,\
"utw",EXT_GAM,\
"utx",EXT_GAM,\
"utz",EXT_SET,\
"uu",EXT_ENC,\
"uud",EXT_ENC,\
"uue",EXT_ENC,\
"uvx",EXT_GAM,\
"uw",EXT_AUD,\
"uwf",EXT_AUD,\
"uxx",EXT_GAM,\
"uzip",EXT_COM,\
"v",EXT_RAS,\
"v12",EXT_DBA,\
"v2i",EXT_BCK,\
"v2m",EXT_AUD,\
"v3d",EXT_3DI,\
"v3o",EXT_3DI,\
"v64",EXT_GAM,\
"vac",EXT_3DI,\
"vag",EXT_AUD,\
"val",EXT_AUD,\
"vap",EXT_AUD,\
"vaporcd",EXT_DSK,\
"vb",EXT_AUD or EXT_EXE or EXT_GAM,\
"vbe",EXT_EXE,\
"vbf",EXT_GAM,\
"vbox-extpack",EXT_PLU,\
"vbox-prev",EXT_BCK,\
"vbox",EXT_SET,\
"vbr",EXT_VEC,\
"vbx6settings",EXT_SET,\
"vc1",EXT_VID,\
"vc3",EXT_AUD,\
"vc4",EXT_DSK,\
"vc6",EXT_DSK,\
"vc8",EXT_DSK,\
"vcd",EXT_DSK or EXT_DSK,\
"vcm",EXT_GAM,\
"vco",EXT_DSK,\
"vcpf",EXT_VID,\
"vcpref",EXT_SET,\
"vcr",EXT_VID,\
"vct",EXT_GIS,\
"vcv",EXT_VID,\
"vcw",EXT_SET,\
"vcx",EXT_DSK,\
"vda",EXT_RAS,\
"vdc",EXT_GIS,\
"vdf",EXT_GAM or EXT_GAM or EXT_PLU,\
"vdi",EXT_DSK or EXT_DSK,\
"vdj",EXT_AUD,\
"vdo",EXT_EXE or EXT_VID,\
"vdr",EXT_VID,\
"vdx",EXT_VID,\
"vec",EXT_GIS or EXT_VEC,\
"veg",EXT_3DI or EXT_VID,\
"vem",EXT_COM or EXT_VID,\
"vep",EXT_VID,\
"vet",EXT_CAD,\
"vexe",EXT_EXE,\
"vf",EXT_VID,\
"vfc",EXT_PAG,\
"vfd",EXT_DSK,\
"vff",EXT_RAS,\
"vft",EXT_VID,\
"vfw",EXT_VID,\
"vfz",EXT_VID,\
"vga",EXT_SYS,\
"vgd",EXT_SYS,\
"vgi",EXT_GAM,\
"vgm",EXT_AUD,\
"vgz",EXT_AUD or EXT_VID,\
"vhd",EXT_DSK,\
"vhdx",EXT_DSK,\
"vhv",EXT_GAM,\
"vic",EXT_RAS,\
"vid",EXT_VID,\
"video",EXT_VID,\
"viewlet",EXT_VID,\
"viff",EXT_RAS,\
"vim",EXT_SET,\
"vimrc",EXT_SET,\
"vis",EXT_DBA or EXT_GAM,\
"viv",EXT_GAM or EXT_GAM or EXT_VID,\
"vivo",EXT_VID,\
"vlab",EXT_VID,\
"vlc",EXT_AUD,\
"vlt",EXT_ENC or EXT_SET,\
"vlw",EXT_FNT,\
"vlx",EXT_EXE,\
"vmac",EXT_SET,\
"vmba",EXT_SET,\
"vmc",EXT_SET,\
"vmcx",EXT_SET,\
"vmd",EXT_3DI or EXT_AUD,\
"vmdk",EXT_DSK,\
"vmf",EXT_AUD or EXT_AUD or EXT_GAM,\
"vml",EXT_VEC,\
"vmo",EXT_3DI or EXT_AUD,\
"vmpl",EXT_SET,\
"vmt",EXT_SET,\
"vmtm",EXT_SET,\
"vmv",EXT_GAM or EXT_GAM,\
"vmwarevm",EXT_DSK,\
"vmx",EXT_GAM or EXT_SET or EXT_SET,\
"vmxf",EXT_SET,\
"vna",EXT_RAS,\
"vnc",EXT_SET,\
"vnd",EXT_CAD,\
"vnf",EXT_FNT,\
"vni",EXT_SET,\
"vob",EXT_3DI or EXT_GAM or EXT_VID,\
"voc",EXT_AUD,\
"voi",EXT_AUD,\
"vol",EXT_GAM,\
"volarchive",EXT_DSK,\
"vox",EXT_3DI or EXT_AUD,\
"voxal",EXT_AUD,\
"vp",EXT_3DI or EXT_ENC or EXT_GAM or EXT_PAG,\
"vp3",EXT_VID,\
"vp6",EXT_VID,\
"vp7",EXT_VID,\
"vpcbackup",EXT_BCK,\
"vpd",EXT_3DI,\
"vph",EXT_SET,\
"vpj",EXT_VID,\
"vpk",EXT_GAM,\
"vpl",EXT_AUD,\
"vpm",EXT_AUD or EXT_EXE,\
"vps",EXT_SET,\
"vqc",EXT_SET,\
"vqf",EXT_AUD,\
"vrf",EXT_AUD,\
"vrl",EXT_3DI,\
"vro",EXT_VID,\
"vs",EXT_3DI,\
"vs4",EXT_VID,\
"vsd",EXT_VEC,\
"vse",EXT_VID,\
"vsh",EXT_3DI,\
"vsi",EXT_COM,\
"vsix",EXT_PLU,\
"vsp",EXT_VID,\
"vsprops",EXT_SET,\
"vsq",EXT_AUD,\
"vss",EXT_RAS,\
"vssettings",EXT_SET,\
"vst",EXT_PLU or EXT_RAS or EXT_VEC,\
"vsw",EXT_SET,\
"vtf",EXT_CAD or EXT_GAM,\
"vtx",EXT_3DI or EXT_AUD,\
"vue",EXT_3DI or EXT_SET,\
"vvd",EXT_3DI,\
"vwx",EXT_CAD,\
"vx_",EXT_SYS,\
"vxd",EXT_SYS,\
"vyf",EXT_AUD,\
"w01",EXT_AUD,\
"w32",EXT_VID,\
"w3d",EXT_3DI,\
"w3g",EXT_GAM,\
"w3m",EXT_GAM,\
"w3n",EXT_GAM,\
"w3x",EXT_GAM,\
"w3z",EXT_GAM,\
"w64",EXT_AUD,\
"wad",EXT_GAM or EXT_GAM,\
"wagame",EXT_GAM,\
"wal",EXT_GAM,\
"war",EXT_COM,\
"wav",EXT_AUD or EXT_AUD,\
"wave",EXT_AUD,\
"wax",EXT_AUD,\
"wb1",EXT_RAS,\
"wbb",EXT_BCK,\
"wbc",EXT_RAS,\
"wbcat",EXT_BCK,\
"wbd",EXT_RAS,\
"wbfs",EXT_GAM,\
"wbk",EXT_BCK,\
"wbm",EXT_RAS,\
"wbmp",EXT_RAS,\
"wbt",EXT_GAM,\
"wbz",EXT_RAS,\
"wcm",EXT_EXE,\
"wcp",EXT_VID,\
"wcx",EXT_SET,\
"wcz",EXT_SET,\
"wdb",EXT_DBA or EXT_GAM,\
"wdf",EXT_GAM or EXT_SYS,\
"wdgt",EXT_SYS,\
"wdp",EXT_CAD or EXT_RAS,\
"weap",EXT_GAM,\
"webm",EXT_VID,\
"webp",EXT_RAS,\
"webpnp",EXT_SYS,\
"wem",EXT_AUD,\
"wer",EXT_SYS,\
"wfb",EXT_AUD,\
"wfc",EXT_SET,\
"wfd",EXT_AUD or EXT_GIS,\
"wfp",EXT_AUD,\
"wft",EXT_3DI,\
"wgf",EXT_GAM,\
"wgz",EXT_SYS,\
"wi",EXT_RAS,\
"wic",EXT_RAS,\
"widget",EXT_EXE or EXT_EXE,\
"wii",EXT_DSK,\
"wil",EXT_DSK,\
"wim",EXT_DSK,\
"win",EXT_BCK or EXT_BCK,\
"winclone",EXT_DSK,\
"wiz",EXT_EXE,\
"wjf",EXT_BCK,\
"wki",EXT_SPR,\
"wks",EXT_SPR or EXT_SPR,\
"wku",EXT_SPR,\
"wl6",EXT_GAM,\
"wld",EXT_GAM or EXT_GAM or EXT_GIS,\
"wlmp",EXT_VID,\
"wlp",EXT_PAG,\
"wlx",EXT_GIS,\
"wlz",EXT_DSK or EXT_PLU,\
"wm",EXT_VID,\
"wma",EXT_AUD,\
"wmd",EXT_VID,\
"wmdb",EXT_DBA,\
"wmf",EXT_GAM or EXT_VEC,\
"wmga",EXT_PAG,\
"wmmp",EXT_VID,\
"wmo",EXT_GAM,\
"wmp",EXT_RAS,\
"wms",EXT_SET,\
"wmt",EXT_DSK,\
"wmv",EXT_VID,\
"wmx",EXT_VID,\
"wmz",EXT_SET or EXT_VEC,\
"woff",EXT_FNT,\
"wolfquest",EXT_GAM,\
"wor",EXT_GIS,\
"work",EXT_SET,\
"workflow",EXT_EXE,\
"workspace",EXT_SET,\
"world",EXT_GAM or EXT_GAM,\
"wot",EXT_COM or EXT_VID,\
"wotreplay",EXT_GAM,\
"wow",EXT_AUD,\
"wp3",EXT_VID,\
"wpb",EXT_BCK or EXT_RAS,\
"wpe",EXT_ENC or EXT_RAS,\
"wpg",EXT_VEC,\
"wph",EXT_SYS,\
"wpk",EXT_AUD or EXT_EXE,\
"wpl",EXT_GAM or EXT_VID,\
"wpm",EXT_EXE or EXT_GAM,\
"wpp",EXT_AUD or EXT_SET,\
"wproj",EXT_AUD,\
"wps",EXT_SET,\
"wpt",EXT_GAM or EXT_PAG,\
"wpx",EXT_SYS,\
"wq1",EXT_SPR,\
"wq2",EXT_SPR,\
"wrk",EXT_AUD or EXT_DBA,\
"wrl",EXT_3DI,\
"wrp",EXT_3DI,\
"wrpl",EXT_GAM,\
"wrpl.wgf",EXT_GAM,\
"wrz",EXT_3DI,\
"ws",EXT_EXE,\
"wsf",EXT_EXE,\
"wsh",EXT_EXE,\
"wspak",EXT_BCK,\
"wtd",EXT_GAM,\
"wtf",EXT_GAM,\
"wtpl",EXT_AUD,\
"wtpt",EXT_AUD,\
"wtv",EXT_VID,\
"wus",EXT_AUD,\
"wut",EXT_AUD,\
"wv",EXT_AUD,\
"wvc",EXT_AUD,\
"wve",EXT_AUD,\
"wvl",EXT_RAS,\
"wvx",EXT_VID,\
"wwf",EXT_PAG,\
"wwu",EXT_AUD,\
"wx",EXT_GAM,\
"wyz",EXT_AUD,\
"wz",EXT_GAM or EXT_GAM,\
"wzconfig",EXT_SET,\
"x",EXT_3DI,\
"x_b",EXT_CAD,\
"x_t",EXT_CAD,\
"x32",EXT_PLU,\
"x3d",EXT_3DI,\
"x3f",EXT_CAM,\
"x4k",EXT_SET,\
"x64",EXT_DSK,\
"xa",EXT_AUD or EXT_AUD or EXT_DSK,\
"xadd",EXT_PLU,\
"xaf",EXT_3DI or EXT_3DI,\
"xan",EXT_GAM,\
"xap",EXT_EXE,\
"xar",EXT_VEC,\
"xba",EXT_PLU,\
"xbap",EXT_EXE,\
"xbe",EXT_GAM,\
"xbk",EXT_BCK,\
"xbm",EXT_RAS,\
"xbsav",EXT_GAM,\
"xcf",EXT_RAS,\
"xcu",EXT_SET,\
"xdb",EXT_DBA,\
"xdi",EXT_DSK,\
"xdr",EXT_SET,\
"xds",EXT_GAM,\
"xdw",EXT_PAG,\
"xef",EXT_COM,\
"xej",EXT_VID,\
"xel",EXT_VID,\
"xem",EXT_SET,\
"xen",EXT_GAM,\
"xep",EXT_SET,\
"xes",EXT_SET,\
"xesc",EXT_VID,\
"xet",EXT_SET,\
"xev",EXT_SET,\
"xex",EXT_GAM,\
"xez",EXT_COM,\
"xfl",EXT_VID,\
"xfn",EXT_FNT,\
"xfs",EXT_AUD,\
"xft",EXT_FNT,\
"xgs",EXT_SET,\
"xi",EXT_AUD,\
"xif",EXT_PAG,\
"xise",EXT_CAD,\
"xl",EXT_SPR,\
"xla",EXT_PLU,\
"xlam",EXT_PLU,\
"xlb",EXT_SET or EXT_SET,\
"xld",EXT_DBA,\
"xlk",EXT_BCK,\
"xll",EXT_PLU,\
"xlm",EXT_EXE,\
"xlmv",EXT_VID,\
"xlr",EXT_SPR,\
"xls",EXT_SPR,\
"xlsb",EXT_SPR,\
"xlshtml",EXT_SPR,\
"xlsm",EXT_SPR,\
"xlsx",EXT_SPR,\
"xltm",EXT_SPR,\
"xltx",EXT_SPR,\
"xlv",EXT_PLU,\
"xm",EXT_AUD,\
"xmb",EXT_GAM or EXT_GAM,\
"xmcdz",EXT_COM,\
"xmd",EXT_DSK or EXT_PLU,\
"xmf",EXT_3DI or EXT_AUD or EXT_DSK,\
"xmi",EXT_AUD,\
"xmind",EXT_VEC,\
"xmm",EXT_3DI,\
"xmmap",EXT_VEC,\
"xmz",EXT_AUD,\
"xnb",EXT_GAM,\
"xnt",EXT_PLU,\
"xof",EXT_3DI,\
"xol",EXT_GIS,\
"xom",EXT_GAM,\
"xp",EXT_AUD or EXT_GAM,\
"xp2",EXT_GAM,\
"xp3",EXT_GAM,\
"xp4",EXT_GAM,\
"xpaddercontroller",EXT_SET,\
"xpd",EXT_GAM,\
"xpi",EXT_PLU,\
"xpk",EXT_GAM,\
"xpl",EXT_SET,\
"xpm",EXT_RAS,\
"xpr",EXT_3DI or EXT_VEC,\
"xps",EXT_PAG,\
"xpt",EXT_PLU,\
"xqt",EXT_EXE,\
"xrf",EXT_3DI,\
"xrm-ms",EXT_SYS,\
"xrns",EXT_AUD,\
"xs",EXT_GAM,\
"xsb",EXT_AUD,\
"xsf",EXT_3DI,\
"xsi",EXT_3DI,\
"xsiaddon",EXT_PLU,\
"xsn",EXT_PAG,\
"xsp",EXT_AUD,\
"xspf",EXT_AUD,\
"xst",EXT_SET,\
"xt",EXT_AUD,\
"xtl",EXT_GAM,\
"xtp",EXT_PAG or EXT_SET,\
"xtreme",EXT_SET,\
"xui",EXT_SET,\
"xur",EXT_SET,\
"xv0",EXT_3DI,\
"xv3",EXT_CAD,\
"xva",EXT_DSK,\
"xvid",EXT_VID,\
"xvm",EXT_SET,\
"xvmconf",EXT_GAM,\
"xwb",EXT_AUD,\
"xwd",EXT_RAS,\
"xwk",EXT_SET,\
"xx",EXT_COM,\
"xxe",EXT_ENC,\
"xys",EXT_EXE,\
"xz",EXT_COM,\
"xzfx",EXT_PAG,\
"y",EXT_COM or EXT_RAS,\
"y3a",EXT_GAM,\
"y3d",EXT_GAM,\
"y4m",EXT_VID,\
"yal",EXT_VEC,\
"yaodl",EXT_3DI,\
"ycm",EXT_GAM,\
"ydc",EXT_GAM,\
"ydl",EXT_3DI,\
"ydr",EXT_GAM,\
"ydt",EXT_GAM,\
"yenc",EXT_ENC,\
"yfs",EXT_GAM,\
"ym",EXT_AUD,\
"ync",EXT_ENC,\
"ysp",EXT_RAS,\
"yuv",EXT_RAS or EXT_VID,\
"yz",EXT_COM,\
"yz1",EXT_COM,\
"z",EXT_COM,\
"z01",EXT_COM,\
"z02",EXT_COM,\
"z03",EXT_COM,\
"z04",EXT_COM,\
"z2f",EXT_GAM,\
"z3d",EXT_3DI,\
"z64",EXT_GAM,\
"zap",EXT_COM or EXT_SET,\
"zdl",EXT_PAG,\
"zdp",EXT_PAG,\
"zds",EXT_GAM or EXT_PAG,\
"zeg",EXT_VID,\
"zfsendtotarget",EXT_COM,\
"zfx",EXT_PAG,\
"zgm",EXT_VEC,\
"zi",EXT_COM,\
"zif",EXT_RAS,\
"zip",EXT_COM or EXT_GAM,\
"zipx",EXT_COM,\
"zix",EXT_COM,\
"zl",EXT_COM,\
"zl9",EXT_EXE,\
"zlb",EXT_PLU,\
"zm1",EXT_VID,\
"zm2",EXT_VID,\
"zm3",EXT_VID,\
"zmap",EXT_GAM,\
"zmv",EXT_VID,\
"zno",EXT_PAG,\
"zon",EXT_SET,\
"identifier",EXT_SYS,\
"zoo",EXT_COM or EXT_GAM,\
"zpa",EXT_AUD,\
"zpf",EXT_SET,\
"zpi",EXT_COM or EXT_SET,\
"zpl",EXT_AUD,\
"zps",EXT_ENC,\
"zs0",EXT_GAM,\
"zs1",EXT_GAM,\
"zs2",EXT_GAM,\
"zs3",EXT_GAM,\
"zs4",EXT_GAM,\
"zs5",EXT_GAM,\
"zs6",EXT_GAM,\
"zs7",EXT_GAM,\
"zs8",EXT_GAM,\
"zs9",EXT_GAM,\
"zsd",EXT_GAM,\
"zst",EXT_GAM,\
"zt",EXT_3DI,\
"ztd",EXT_GAM,\
"ztmp",EXT_GAM,\
"zvd",EXT_AUD,\
"zvr",EXT_AUD,\
"zvt",EXT_SET,\
"zxp",EXT_PLU,\
"zz",EXT_COM,\
"zzz",EXT_GAM
