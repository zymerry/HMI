CC = arm-linux-gcc
DFLAGS = -c -O2
OBJS = serial.c serial_test.c hardware_sdk.h

serial_test : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ 

.PHYONE : clean
clean :
	rm -f *.o serial_test
