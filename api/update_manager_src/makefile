CC = arm-linux-gcc
CFLAGS = -O2
CFLAGS += -I../include
OBJS = serial.c UpMager.c
TARGET = libUpMager.so

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -shared $^ -o $@

.PHONY : clean
clean:
	rm -rf *.o $(TARGET)
