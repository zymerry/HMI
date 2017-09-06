CC = arm-linux-g++
CFLAGS = -O2

OBJS = gpio_gtest.o gpio.o
TARGET = gpio_gtest
$(TARGET) : $(OBJS)
	arm-linux-g++ $(OBJS) -o $@ -lpthread -lgtest -L.
gpio_gtest.o : gpio_gtest.c
	$(CC) -c $(CFLAGS) $^ -o $@ -lgtest -lpthread -I/usr/include -I/usr/include/i386-linux-gnu -L/usr/lib/gtest_arm/ 
gpio.o : gpio.c
	arm-linux-gcc -c $^ -o $@
.PHYONE : clean
clean :
	rm -f *.o $(TARGET)
