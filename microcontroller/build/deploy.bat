@echo off

pushd ..\bin

..\build\avrdude -c pickit4_isp -p m32u4 -U flash:w:main.hex:i

popd
