call assemble.bat

pushd ..\bin

"C:\Program Files\Microchip\MPLABX\v6.00\mplab_platform\mplab_ipe\ipecmd.exe" -Fmain.hex -M -TSBUR222474663 -PATMEGA32U4 -ORIISP

popd
