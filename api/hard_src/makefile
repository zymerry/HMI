OBJS = audio.o gpio.o key.o mic.o serial.o debug.o
CFLAGS = -O2 -c
CC = arm-linux-gcc
LD = arm-linux-ld
TARGET = libHardWare.so
$(TARGET) : $(OBJS)
	$(CC) $^ -shared -o $@

audio.o : audio.c
	$(CC) $(CFLAGS) $< -o $@
gpio.o : gpio.c
	$(CC) $(CFLAGS) $< -o $@
key.o : key.c
	$(CC) $(CFLAGS) $< -o $@
mic.o : mic.c
	$(CC) $(CFLAGS) $< -o $@
serial.o : serial.c
	$(CC) $(CFLAGS)  $< -o $@
debug.o : debug.c
	$(CC) $(CFLAGS) $< -o $@

.PHYONE : clean
clean :
	rm -f *.o $(TARGET)
