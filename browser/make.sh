#!/bin/sh
arm-linux-gcc gpio.c -c -o gpio.o
arm-linux-gcc serial.c -c -o serial.o
arm-linux-gcc mic.c -c -o mic.o
arm-linux-gcc audio.c -c -o audio.o
arm-linux-gcc key.c -c -o key.o
arm-linux-gcc can.c -c -o can.o
arm-linux-gcc file.c -c -o file.o
arm-linux-gcc -c  pcm2aac.c -o pcm2aac.o 
arm-linux-gcc -c  aac2pcm.c -o aac2pcm.o
/usr/local/Trolltech/QtEmbedded-4.8.7/bin/qmake -r
make;
arm-linux-g++ -Wl,-O1 -Wl,-rpath,/usr/local/Trolltech/QtEmbedded-4.8.7/lib -o fancybrowser main.o mainwindow.o hard_sdk.o gpio.o serial.o mic.o audio.o key.o can.o file.o pcm2aac.o aac2pcm.o moc_mainwindow.o moc_hard_sdk.o    -L/usr/local/Trolltech/QtEmbedded-4.8.7/lib -lQtWebKit -lQtGui -L/usr/local/Trolltech/QtEmbedded-4.8.7/lib -lQtNetwork -lQtCore -lpthread -L. -lnaacenc -lfaad
#make
