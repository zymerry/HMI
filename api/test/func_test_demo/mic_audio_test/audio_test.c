#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/soundcard.h>
#include <sys/poll.h>

int main(int argc, char *argv[], char *env[])
{
	char *buf = NULL;
	int fd_dsp, fd_mixer;
	int len, ret, fd, frag;
	
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("open :");
		return -1;
	}
	
	ret = audio_open(&fd_dsp, &fd_mixer);
	if (ret < 0)
	{
		printf("audio_open error!\n");
		return -1;
	}
	
	ret = audio_setdef(fd_dsp, fd_mixer);
	if (ret < 0)
	{
		printf("audio_sedef error!\n");
		return -1;
	}

	ret = audio_setrate(fd_dsp, 48000);
	if (ret < 0)
	{
		printf("audio_setrate error!\n");
		return -1;
	}

	ret = audio_setsound(fd_mixer, 0x8080);
	if (ret < 0)
	{
		printf("audio_setsound error!\n");
		return -1;
	}

	//frag = init_frag(fd_dsp);
	//buf = (char *)malloc(frag);
	 ioctl(fd_dsp, SNDCTL_DSP_GETBLKSIZE, &frag);
     buf = (char *)malloc(frag);
	 printf("frag=%d\n", frag);
     printf("frag=%d\n", buf);

	int flag = 1;
	printf("start audio!\n");
	while (1)
	{
		if (flag == 1)
		{
			memset(buf, 0, frag);
			ret=read(fd, buf, frag);
		}
		if (ret > 0)
		{
			flag = audio_write(fd_dsp, buf, frag);
		}
		else if (ret < 0)
		{
			printf("read file error!\n");
			return -1;
		}
		else
		{
			printf("audio end ret :[%d]\n", ret);
			break;
		}
	}
	audio_close(fd_dsp, fd_mixer);
	return 0;
}
