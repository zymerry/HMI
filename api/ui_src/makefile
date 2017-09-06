CC = arm-linux-gcc
CFLAGS = -shared
CFLAGS += -I../include
#CFLAGS = 
TARGET = libAppUi.so
OBJS = show_ui.c cJSON.c

$(TARGET) : $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@ -lm

.PHYON : clean
clean :
	rm -f *.o $(TARGET)
