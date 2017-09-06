CC = arm-linux-gcc
DFLAGS = -c -O2
OBJS = gpio.c gpio_test.c hardware_sdk.h

gpio_test : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ 

.PHYONE : clean
clean :
	rm -f *.o gpio_test
