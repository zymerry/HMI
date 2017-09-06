#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "hardware_sdk.h"


static int dsp_fd1, mix_fd1;
static int dsp_fd2, mix_fd2;

void func1(void)
{
	
}

void func2(void)
{

}

int main(int argc, char *argv[], char env[])
{
	int ret;
	char buf[1024];
	pthread_t tid1, tid2;
	
	memset(buf, 0, sizeof(1024));
	ret = mic_open(&dsp_fd1, &mix_fd1);
	if (ret < 0)
	{
		printf("mic_open error!\n");
		return -1;
	}

	ret = audio_open(&dsp_fd2, &mix_fd2);
	if (ret < 0)
	{
		printf("audio_open error!\n");
		return -1;
	}

	ret = mic_setopt(0, 0, dsp_fd1, mix_fd1);
	if (ret < 0)
	{
		printf("mic_setopt error!\n");
		return -1;
	}

	ret = audio_setdef(dsp_fd2, mix_fd2);
	if (ret < 0)
	{
		printf("audio_setdef error!\n");
		return -1;
	}

	ret = audio_setrate(dsp_fd2, 16000);
	if (ret < 0)
	{
		printf("audio_setrate error!\n");
		return -1;
	}
	
	ret = audio_setsound(mix_fd2, 0x5050);
	if (ret < 0)
	{
		printf("audio_setsound error!\n");
		return -1;
	}

	init_frag(dsp_fd2);
	while (1)
	{
		printf("0000000000000000000000\n");
		memset(buf, 0, 1024);
		ret = mic_read(dsp_fd1, buf, 1024);
		if (ret < 0)
		{
			printf("mic_read error!\n");
			return -1;
		}
		printf("111111111111111111111111111\n");
		ret = audio_write(dsp_fd2, buf, 1024);
		if (ret < 0)
		{
			printf("audio_write error!\n");
			return -1;
		}
	}
#if 0	
	ret = pthread_create(&tid1, NULL, func1, NULL);
	if (ret < 0)
	{
		printf("pthread_create func1 error!");
		return -1;
	}

	ret = pthread_create(&tid2, NULL, func2, NULL);
	if (ret < 0)
	{
		printf("pthread_create func2 error!");
		return -1;
	}

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
#endif
	return 0;
}
