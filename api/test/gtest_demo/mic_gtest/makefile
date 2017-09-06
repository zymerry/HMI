CC = arm-linux-g++
CFLAGS = -O2

OBJS = mic_gtest.o mic.o
TARGET = gtest_mic
$(TARGET) : $(OBJS)
	arm-linux-g++ $(OBJS) -o $@ -lpthread -lgtest -L.
mic_gtest.o : mic_gtest.c
	$(CC) -c $(CFLAGS) $^ -o $@ -lgtest -lpthread -I/usr/include -I/usr/include/i386-linux-gnu -L/usr/lib/gtest_arm/ 
mic.o : mic.c
	arm-linux-gcc -c $^ -o $@
.PHYONE : clean
clean :
	rm -f *.o $(TARGET)
