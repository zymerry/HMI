CC = gcc
CFLAGS = -shared
#CFLAGS = 
TARGET = updatescreen.so
OBJS = client.c cJSON.c

$(TARGET) : $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@ -lm

.PHYON : clean
clean :
	rm -f *.o $(TARGET)
