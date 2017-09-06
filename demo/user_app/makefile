CC = arm-linux-gcc
CFLAGS = -I../../api/include
TARGET = AppMain
OBJS = main.c

$(TARGET) : $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@ -L../../api/hard_src -L../../api/ui_src -lHardWare -lAppUi -pthread -I. -L.

.PHYON : clean
clean :
	rm -f *.o $(TARGET)
