@echo off

set LANG=en-US
  call %x64devdir%\lang\makeone.bat
  IF ERRORLEVEL 1 GOTO :err_exit
  copy %x64devdir%\lang\en-US.bin %x64devdir%\..\lang\en-US.bin /Y

set LANG=pl-PL
	call %x64devdir%\lang\makeone.bat
  IF ERRORLEVEL 1 GOTO :err_exit
  copy %x64devdir%\lang\pl-PL.bin %x64devdir%\..\lang\pl-PL.bin /Y

:err_exit
set LANG=
