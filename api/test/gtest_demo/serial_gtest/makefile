CC = arm-linux-g++
CFLAGS = -O2

OBJS = serial_gtest.o serial.o
TARGET = gtest_serial
$(TARGET) : $(OBJS)
	arm-linux-g++ $(OBJS) -o $@ -lpthread -lgtest -L.
serial_gtest.o : serial_gtest.c
	$(CC) -c $(CFLAGS) $^ -o $@ -lgtest -lpthread -I/usr/include -I/usr/include/i386-linux-gnu -L/usr/lib/gtest_arm/ 
serial.o : serial.c
	arm-linux-gcc -c $^ -o $@
.PHYONE : clean
clean :
	rm -f *.o $(TARGET)
