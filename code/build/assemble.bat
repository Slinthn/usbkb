@echo off

if not exist ../bin mkdir ../bin

cls

pushd ..\src

xc8-cc -mcpu=ATmega32U4 -Wall -o ../bin/main.o main.c

popd

avr-objcopy -O ihex ../bin/main.o ../bin/main.hex
