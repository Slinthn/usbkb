@echo off

call assemble.bat

pushd ..\bin

java -jar "C:\Program Files\Microchip\MPLABX\v6.05\mplab_platform\mplab_ipe\ipecmd.jar" -Fmain.hex -M -TSBUR222474663 -PATMEGA32U4 -ORIISP
rem call "C:\Program Files\Microchip\MPLABX\v6.05\mplab_platform\mplab_ipe\ipecmd.exe" -Fmain.hex -M -TSBUR222474663 -PATMEGA32U4 -ORIISP

popd
