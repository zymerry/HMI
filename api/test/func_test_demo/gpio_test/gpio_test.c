#include <stdio.h>
#include <unistd.h>
#include "hardware_sdk.h"

int main(int argc, char *argv[], char *env[])
{
	int ret;
	int fd;
	fd = gpio_open(2);
	if (fd < 0)
	{
		printf("gpio_open error!\n");
		return -1;
	}
	
	ret = gpio_setio(2, 0);
	if (ret < 0)
	{
		printf("gpio_setio error!\n");
		return -1;
	}
	while(1)
	{
		ret = gpio_write(fd, "0");
		if (ret < 0)
		{
			printf("gpio_write error!\n");
			return -1;
		}
//		gpio_close(fd);
		sleep(2);
		ret = gpio_write(fd, "1");
		if (ret < 0)
		{
			printf("gpio_write error!\n");
			return -1;
		}
		sleep(2);
	}
	return 0;
}
