@echo off

pushd ..\bin

ipecmd.exe -Fmain.hex -M -TSBUR222474663 -PATMEGA32U4 -ORIISP

popd
