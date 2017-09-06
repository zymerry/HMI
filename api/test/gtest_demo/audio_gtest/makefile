CC = arm-linux-g++
CFLAGS = -O2

OBJS = audio_gtest.o audio.o
TARGET = gtest_audio
$(TARGET) : $(OBJS)
	arm-linux-g++ $(OBJS) -o $@ -lpthread -lgtest -L.
audio_gtest.o : audio_gtest.c
	$(CC) -c $(CFLAGS) $^ -o $@ -lgtest -lpthread -I/usr/include -I/usr/include/i386-linux-gnu -L/usr/lib/gtest_arm/ 
audio.o : audio.c
	arm-linux-gcc -c $^ -o $@
.PHYONE : clean
clean :
	rm -f *.o $(TARGET)
