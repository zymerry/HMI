CC = arm-linux-g++
CFLAGS = -O2

OBJS = key_gtest.o key.o
TARGET = key_gtest
$(TARGET) : $(OBJS)
	arm-linux-g++ $(OBJS) -o $@ -lpthread -lgtest  -L.
key_gtest.o : key_gtest.c
	$(CC) -c $(CFLAGS) $^ -o $@ -lgtest -lpthread -I/usr/include -I/usr/include/i386-linux-gnu -L/usr/lib/gtest_arm/ 
key.o : key.c
	arm-linux-gcc -c $^ -o $@
.PHYONE : clean
clean :
	rm -f *.o $(TARGET)
