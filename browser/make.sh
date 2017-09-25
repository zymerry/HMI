#!/bin/sh
arm-linux-gcc gpio.c -c -o gpio.o
arm-linux-gcc serial.c -c -o serial.o
arm-linux-gcc mic.c -c -o mic.o
arm-linux-gcc audio.c -c -o audio.o
arm-linux-gcc key.c -c -o key.o
arm-linux-gcc can.c -c -o can.o
arm-linux-gcc file.c -c -o file.o
/usr/local/Trolltech/QtEmbedded-4.8.7/bin/qmake -r
#make
