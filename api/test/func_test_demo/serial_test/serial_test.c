#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "hardware_sdk.h"

int main(int argc, char *argv[], char *env[])
{
	int serial_fd, fd, ret;
	unsigned char data[256];
	serial_fd = serial_open(2);
	if (serial_fd < 0)
	{
		printf("serial_fd error!\n");
		return -1;
	}
	ret = serial_setopt(serial_fd, 115200, 8, 'N', 1);
	if (ret < 0)
	{
		printf("serial_setopt error!\n");
		return -1;
	}
#if 1
	fd = open("/mnt/nand1-2/123", O_CREAT|O_TRUNC|O_RDWR, 0644);
//	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("open file:");
		return -1;
	}
	while (1)
	{
		memset(data, 0, 256);
		ret = serial_read(serial_fd, data, 256);
		if (ret < 0)
			break;
		printf("[%s]", data);
		if (ret > 0)
		{
			write(fd, data, ret);
		}
	}
#endif
	return 0;
}
