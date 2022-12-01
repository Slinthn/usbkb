@echo off

cls

pushd ..

xc8-cc -mcpu=ATmega32U4 -Wall -o bin/main.o main.c

popd

avr-objcopy -O ihex ../bin/main.o ../bin/main.hex
