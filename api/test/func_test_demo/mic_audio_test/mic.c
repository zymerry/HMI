/**
* @file      mic.c
* @brief     This module realize the opreation of the microphone.
* @details   This module contains open and close and setopt and read of the button.
* @author    zy
* @date      2017/06/15
* @version   HMI-T001
* @par Copyright (c)
*      keluofeite
* @par History:
*
*   version: author, date, desc\n
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/soundcard.h>

/**This is the brief of the mic_open
* 	int mic_open(int *dsp_fd, int *mixer_fd)
*   this function can open the mic file descriptor.
*	@param dsp_fd. It is the dsp file descriptor.
*   @param mixer. It is the mixer file descriptor.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     open()
*   @note    
*/
int mic_open(int *dsp_fd, int *mixer_fd)
{
	//check the param
	if (dsp_fd < 0 || mixer_fd < 0)
	{
		printf("the param error! dsp_fd:[%d] mixer_fd:[%d]\n", dsp_fd, mixer_fd);
		return -1;
	}

	//open the device and return the file descriptor
	*dsp_fd = open("/dev/dsp1",O_RDONLY,0);
	if (*dsp_fd < 0)
	{
		perror("open dsp_fd : ");
		return -1;
	}

	*mixer_fd = open("/dev/mixer1", O_WRONLY);
	if (*mixer_fd < 0)
	{
		perror("open mixer :");
		return -1;
	}

	return 0;
}

/**This is the brief of the mic_setopt
* 	int mic_setopt(int samplerate, int rec_volume£¬int dsp_fd, int mixer_fd)
*   this function can set the microphone working condition.
*	@param dsp_fd. It is the dsp file descriptor.
*   @param mixer. It is the mixer file descriptor.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     ioctl()
*   @note    
*/
int mic_setopt(int samplerate, int rec_volume, int dsp_fd, int mixer_fd)
{
	int format;
	int tmp;
	int channels = 1;

	//param check
	if (0==samplerate)
	{
		samplerate = 16000;
	}
	else if (!(samplerate==8000 || samplerate==11025 ||
		samplerate==16000 || samplerate==22050 ||
		samplerate==24000 || samplerate==32000 ||
		samplerate==44100 || samplerate==48000))
	{
		printf("the param samplerate :[%d] is error!\n", samplerate);
		return -1;
	}
	if (0==rec_volume)
	{
		rec_volume = 50;
	}
	else if (rec_volume < 0)
	{
		printf("the param rec_volume :[%d] is error!\n", rec_volume);
		return -1;
	}
	if (dsp_fd < 0 || mixer_fd < 0)
	{
		printf("dsp_fd:[%d] mixer_fd:[%d] !\n", dsp_fd, mixer_fd);
		return -1;
	}

	printf("samplerate:[%d]  rec_volume:[%d]\n", samplerate, rec_volume);

	//set byte-order
	format = AFMT_S16_LE;
	if (ioctl(dsp_fd,SNDCTL_DSP_SETFMT, &format) == -1)
	{
		perror("dsp_fd set SNDCTL_DSP_SETFMT");
		return -1;
	}
	//set speed
	format = samplerate;
	if (ioctl(dsp_fd, SNDCTL_DSP_SPEED, &samplerate) == -1)
	{
		perror("dsp_fd set SNDCTL_DSP_SPEED");
		printf("samplerate:[%d]\n", samplerate);
		return -1;
	}
	else
	{
		printf("Actual Speed : %d \n", samplerate);
	}
	//set rec_volume
	if (rec_volume > 100)
	{
		rec_volume = 100;
	}
	tmp = rec_volume;
	rec_volume <<= 8;
	rec_volume |= tmp;
	ioctl(mixer_fd , MIXER_WRITE(SOUND_MIXER_PCM), &rec_volume);

	return 0;
}

/**This is the brief of the mic_read
* 	int mic_read(int dsp_fd, char *buf, int size)
*   this function can set the microphone working condition.
*	@param dsp_fd. It is the dsp file descriptor.
*   @retval  int
*   @return  on success the realistic size that read returned.On error, -1 is returned.
*	@see     read()
*   @note    
*/
int mic_read(int dsp_fd, char *buf, int size)
{
	int num;
	//check the param
	if (dsp_fd < 0)
	{
		printf("the param dsp_fd:[%d] error!\n", dsp_fd);
		return -1;
	}
	if (buf == NULL)
	{
		printf("the param buf is NULL!\n");
		return -1;
	}

	//read from dsp_fd
	num = read(dsp_fd, buf, size);
	if (num < 0)
	{
		printf("dsp_fd read error!\n");
		return -1;
	}
	return num;
}

/**This is the brief of the mic_close
* 	void mic_close(int dsp_fd, int mixer_fd)
*   this function will close the mic file descriptor.
*	@param dsp_fd. It is the dsp file descriptor.
*   @param mixer. It is the mixer file descriptor.
*   @retval  void
*   @return  
*	@see     close()
*   @note    
*/
void mic_close(int dsp_fd, int mixer_fd)
{
	//check the param
	if (dsp_fd < 0 || mixer_fd < 0)
	{
		printf("the param error! dsp_fd:[%d] mixer_fd:[%d]\n", dsp_fd, mixer_fd);
	}
	close(dsp_fd);
	close(mixer_fd);
}


