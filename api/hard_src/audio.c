/**
* @file      audio.c
* @brief     This module realize the opreation of the loudspeaker.
* @details   This module contains open and close and set nature of the loudspeaker.
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
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/soundcard.h> 

/*if you want to use debug function, you should define the HMI_DEBUG_LEVEL*/
//#define HMI_DEBUG_LEVEL
#include "debug.h"

static int rate;
static int frag;

/**This is the brief of the audio_open
* 	int audio_open(int *dsp_fd, int *mixer_fd)
*   this function can open the loudspeaker file descriptor.
*	@param dsp_fd. It is the dsp file descriptor.
*   @param mixer_fd. It is the mixer file descriptor.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     open()
*   @note    
*/
int audio_open(int *dsp_fd, int *mixer_fd)
{
	//open the file descriptor
	HMI_DEBUG("open the audio device!\n");
	*dsp_fd = open("/dev/dsp", O_RDWR);
	if (*dsp_fd < 0)
	{
		HMI_ERROR("open dsp_fd:[%d]\n", dsp_fd);
		return -1;
	}
	*mixer_fd = open("/dev/mixer", O_RDWR);
	if (*mixer_fd < 0)
	{
		HMI_ERROR("open mixer_fd :[%d]\n", mixer_fd);
		return -1;
	}
	
	HMI_DEBUG("open device audio successful! dsp_fd:[%d] mixer_fd:[%d]\n");
	return 0;
}

/**This is the brief of the audio_init_frag
* 	int audio_init_frag()
*   this 
*	@param dsp_fd. It is the dsp file descriptor.
*   @retval  
*   @return  
*	@see     
*   @note    
*/
int audio_init_frag(int dsp_fd)
{
	//check the param
	if (dsp_fd < 0)
	{
		HMI_ERROR("the param dsp_fd:[%d] error!\n", dsp_fd);
		return -1;
	}
	//get the frag
	ioctl(dsp_fd, SNDCTL_DSP_GETBLKSIZE, &frag);
	HMI_DEBUG("frag:[%d]\n", frag);
	 
	return frag;
}

/**This is the brief of the audio_setdef
* 	int audio_setdef(int dsp_fd, int mixer_fd)
*   this function will set default nature of the loudspeaker.
*	@param dsp_fd. It is the dsp file descriptor.
*   @param mixer_fd. It is the mixer file descriptor.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     ioctl()
*   @note    
*/
int audio_setdef(int dsp_fd, int mixer_fd)
{
	int oss_format, channels, ret;
	//set samplerate and sound with default of nature
	int samplerate = 16000;
	int volume = 0x50;
	
	//check the param dsp_fd and param mixer_fd
	if (dsp_fd < 0 || mixer_fd < 0)
	{
		HMI_ERROR("the param error! dsp_fd:[%d] mixer_fd:[%d]\n", dsp_fd, mixer_fd);
		return -1;
	}
	//set byte-order
	//standard 16bit little endian format, support this format only
	oss_format=AFMT_S16_LE;
	ioctl(dsp_fd, SNDCTL_DSP_SETFMT, &oss_format);

	//set channels
	channels = 1;
	ioctl(dsp_fd, SNDCTL_DSP_CHANNELS, &channels);

	//set the samplerate-16000 and the sound-0x50
	ret = ioctl(dsp_fd, SNDCTL_DSP_SPEED, &samplerate);
	if (ret < 0)
	{
		HMI_ERROR("set samplerate error!\n");
		return -1;
	}
	ret = ioctl(mixer_fd, MIXER_WRITE(SOUND_MIXER_PCM), &volume);
	if (ret < 0)
	{
		HMI_ERROR("set volume error!\n");
		return -1;
	}
	
	HMI_DEBUG("set device opt successful!\n");
	return 0;
}

/**This is the brief of the audio_setrate
* 	int audio_setrate(int dsp_fd, int samplerate)
*   this function will set samplerate of the loudspeaker.
*	@param dsp_fd. It is the dsp file descriptor.
*   @param samplerate. It is the of the loudspeaker.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     ioctl()
*   @note    
*/
int audio_setrate(int dsp_fd, int samplerate)
{
	int sample_rate;
	int ret;

	//check the param
	if (!(samplerate==800 || samplerate==11025 || samplerate==16000 ||
		samplerate==22050 || samplerate==24000 || samplerate==32000 ||
		samplerate==44100 || samplerate==48000))
	{
		HMI_ERROR("the param samplerate :[%d] is error!\n", samplerate);
		return -1;
	}
	if (dsp_fd < 0)
	{
		HMI_ERROR("the param dsp_fd:[%d]\n", dsp_fd);
		return -1;
	}
	
	//set samplerate
	rate = samplerate;
	sample_rate = samplerate;
	ret = ioctl(dsp_fd, SNDCTL_DSP_SPEED, &sample_rate);
	if (ret < 0)
	{
		HMI_ERROR("set samplerate error!\n");
		return -1;
	}
	return 0;
}

/**This is the brief of the audio_setrate
* 	int audio_setsound(int mixer_fd, int sound)
*   this function will set volume.
*	@param dsp_fd. It is the dsp file descriptor.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     ioctl()
*   @note    
*/
int audio_setsound(int mixer_fd, int sound)
{
	int volume;
	int ret;

	//check the param
	if (sound < 0)
	{
		sound = 0;
	}
	if (mixer_fd < 0)
	{
		HMI_ERROR("the param mixer_fd:[%d] error!\n", mixer_fd);
		return -1;
	}
	//set sound
	volume = sound;
	ret = ioctl(mixer_fd, MIXER_WRITE(SOUND_MIXER_PCM), &volume);
	if (ret < 0)
	{
		HMI_ERROR("set volume error!\n");
		return -1;
	}
	return 0;
}

/**This is the brief of the audio_setrate
* 	int audio_write(int dsp_fd, char *buf, int write_size)
*   this function will set volume.
*	@param dsp_fd. It is the dsp file descriptor.
*   @param buf. It is buf that will to play.
*   @param write_size. It is the size of the realistic content in buf.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     write()
*   @note    
*/
int audio_write(int dsp_fd, char *buf, int write_size)
{
	//check the param
	if (dsp_fd < 0)
	{
		HMI_ERROR("dsp_fd :[%d] is error!\n", dsp_fd);
		return -1;
	}
	if (buf==NULL)
	{
		HMI_ERROR("buf is NULL!\n");
		return -1;
	}
	if (write_size < 0)
	{
		HMI_ERROR("the param write_size :[%d] error!\n", write_size);
		return -1;
	}

	//get info.bytes
	audio_buf_info info;
	do
	{
		ioctl(dsp_fd, SNDCTL_DSP_GETOSPACE, &info);
		usleep(100);
	}
	while(info.bytes < frag);
	fd_set writefds;
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&writefds);
	FD_SET(dsp_fd, &writefds);
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	//write the data to device
	select(dsp_fd+1, NULL, &writefds, NULL, &tv);
	if(FD_ISSET(dsp_fd, &writefds))
	{
		write(dsp_fd, buf, write_size);
		return 1;
	}
	usleep(100);
	return 0;

}

/**This is the brief of the audio_close
 * 	void audio_close(int dsp_fd, int mixer_fd)
 *   this function can open the loudspeaker file descriptor.
 *	@param dsp_fd. It is the dsp file descriptor.
*   @param mixer_fd. It is the mixer file descriptor.
*   @retval  void
*   @return  
*	@see     close()
*   @note    
*/
void audio_close(int dsp_fd, int mixer_fd)
{
	//check the param
	if ((dsp_fd < 0) || (mixer_fd < 0))
	{
		HMI_DEBUG("the param error!\n dsp_fd:[%d] mixer_fd:[%d]", dsp_fd, mixer_fd);
	}
	int bytes;
	int delay;
	int channels = 1;

	//if the block have data, then sleep to wait the data to play
	ioctl(dsp_fd,SNDCTL_DSP_GETODELAY,&bytes);
	delay = bytes / (rate * 2 * channels);
	sleep(delay);

	//close the file decriptor
	close(dsp_fd);
	close(mixer_fd);
}

