@echo off

if not exist ..\bin mkdir ..\bin

cls

pushd ..\src

rem xc8-cc -S -mcpu=ATmega32U4 -Wall -o ../bin/main.s main.c
xc8-cc -mcpu=ATmega32U4 -Wall -o ../bin/main.o main.c

popd

avr-objcopy -O ihex ../bin/main.o ../bin/main.hex
