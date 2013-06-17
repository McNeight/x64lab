REM *** Batch file to use MSSDK 7.1
REM *** Setup
REM *** Copy "SetEnv.cmd" from your <SDKDIR>\Windows\v7.1\Bin to the [tool] folder of x64lab
REM *** this batch file executes the SetEnv and launch the nmake using parameters
REM *** this file may be inserted in the [config\command.utf8] file 
REM *** to be launched from x64lab

call %x64lab%\tool\SetEnv.cmd %1 %2
nmake -f %3 %4


