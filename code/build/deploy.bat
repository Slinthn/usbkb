@echo off

call assemble.bat

if %errorlevel% neq 0 exit /b %errorlevel%

pushd ..\bin

rem java -jar "C:\Program Files\Microchip\MPLABX\v6.05\mplab_platform\mplab_ipe\ipecmd.jar" -Fmain.hex -M -TSBUR222474663 -PATMEGA32U4 -ORIISP
call "C:\Program Files\Microchip\MPLABX\v6.00\mplab_platform\mplab_ipe\ipecmd.exe" -Fmain.hex -M -TSBUR222474663 -PATMEGA32U4 -ORIISP

popd
