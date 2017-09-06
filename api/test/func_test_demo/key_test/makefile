CC = arm-linux-gcc
CFLAGS = -c -O2

key_test : key_test.c debug.c debug.h key.c hardware_sdk.h
	$(CC) $^ -o $@
.PHYONE : clean
clean :
	rm -f *.o key_test
