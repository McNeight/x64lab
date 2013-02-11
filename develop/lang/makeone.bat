@IF "%LANG%"=="" set LANG=en-US
IF not "%1"=="" set LANG=%1

 @echo -----------------------------------
 @echo Assembling %LANG% language
 @echo -----------------------------------
 @del %x64devdir%\lang\%LANG%.bin
 @fasm %x64devdir%\lang\%LANG%.inc %x64devdir%\lang\%LANG%.bin
@set LANG=