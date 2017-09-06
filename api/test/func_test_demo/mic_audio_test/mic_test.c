#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "hardware_sdk.h"


int main(int argc, char *argv[], char *env)
{
	int fd_dsp, fd_mixer;
	int ret;
	char buf[1024];
	int fd, len;

	ret = mic_open(&fd_dsp, &fd_mixer);
	if (ret < 0)
	{
		printf("mic_open error!\n");
		return -1;
	}
	
	ret = mic_setopt(0, 0, fd_dsp, fd_mixer);
	if (ret < 0)
	{
		printf("mic_setopt error!\n");
		return -1;
	}
	
	fd = open("/mnt/nand1-2/mic.mp3", O_CREAT|O_TRUNC|O_RDWR, 0644);
	if (fd < 0)
	{
		printf("open :error!\n");
		return -1;
	}

	len = 0;
	while (1)
	{
		ret = mic_read(fd_dsp, buf, 1024);
		if (ret > 0)
		{
			write(fd, buf, 1024);
		}
		len += ret;
		
		if (len >= 512*1000)
			break;
	}
	return 0;
}
