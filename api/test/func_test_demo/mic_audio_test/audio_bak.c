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

static int rate;
static int frag;
/**This is the brief of the audio_open
* 	int audio_open(int *fd_dsp, int *fd_mixer)
*   this function can open the loudspeaker file descriptor.
*	@param fd_dsp. It is the dsp file descriptor.
*   @param fd_mixer. It is the mixer file descriptor.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     open()
*   @note    
*/
int audio_open(int *fd_dsp, int *fd_mixer)
{
	//open the file descriptor
	*fd_dsp = open("/dev/dsp", O_RDWR);
	if (fd_dsp < 0)
	{
		perror("open fd_dsp:");
		return -1;
	}
	*fd_mixer = open("/dev/mixer", O_RDWR);
	if (fd_mixer < 0)
	{
		perror("open fd_mixer :");
		return -1;
	}

	return 0;
}

/**This is the brief of the init_frag
* 	int void init_frag()
*   this 
*	@param fd_dsp. It is the dsp file descriptor.
*   @retval  
*   @return  
*	@see     
*   @note    
*/
int init_frag(int fd_dsp)
{
	//get dsp buf and initialize the databuf
	ioctl(fd_dsp, SNDCTL_DSP_GETBLKSIZE, &frag);
	printf("frag:[%d]\n", frag);
	return frag;
}

/**This is the brief of the audio_setdef
* 	int audio_setdef(int fd_dsp, int fd_mixer)
*   this function will set default nature of the loudspeaker.
*	@param fd_dsp. It is the dsp file descriptor.
*   @param fd_mixer. It is the mixer file descriptor.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     ioctl()
*   @note    
*/
int audio_setdef(int fd_dsp, int fd_mixer)
{
	int oss_format;
	int channels;

	//check the param fd_dsp and param fd_mixer
	if (fd_dsp < 0 || fd_mixer < 0)
	{
		printf("the param error! fd_dsp:[%d] fd_mixer:[%d]\n", fd_dsp, fd_mixer);
		return -1;
	}
	//set byte-order
	//standard 16bit little endian format, support this format only
	oss_format=AFMT_S16_LE;
	ioctl(fd_dsp, SNDCTL_DSP_SETFMT, &oss_format);

	//set channels
	channels = 1;
	ioctl(fd_dsp, SNDCTL_DSP_CHANNELS, &channels);

	return 0;
}

/**This is the brief of the audio_setrate
* 	int audio_setrate(int fd_dsp, int samplerate)
*   this function will set samplerate of the loudspeaker.
*	@param fd_dsp. It is the dsp file descriptor.
*   @param samplerate. It is the of the loudspeaker.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     ioctl()
*   @note    
*/
int audio_setrate(int fd_dsp, int samplerate)
{
	int sample_rate;
	int ret;

	//check the param
	if (!(samplerate==800 || samplerate==11025 || samplerate==16000 ||
		samplerate==22050 || samplerate==24000 || samplerate==32000 ||
		samplerate==44100 || samplerate==48000))
	{
		printf("the param samplerate :[%d] is error!\n", samplerate);
		return -1;
	}

	//set samplerate
	rate = samplerate;
	sample_rate = samplerate;
	ret = ioctl(fd_dsp, SNDCTL_DSP_SPEED, &sample_rate);
	if (ret < 0)
	{
		printf("set samplerate error!\n");
		return -1;
	}
	return 0;
}

/**This is the brief of the audio_setrate
* 	int audio_setsound(int fd_mixer, int sound)
*   this function will set volume.
*	@param fd_dsp. It is the dsp file descriptor.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     ioctl()
*   @note    
*/
int audio_setsound(int fd_mixer, int sound)
{
	int volume;
	int ret;

	//check the param
	if (sound < 0)
	{
		sound = 0;
	}
	if (fd_mixer < 0)
	{
		printf("the param fd_mixer:[%d] error!\n", fd_mixer);
	}
	//set sound
	volume = sound;
	ret = ioctl(fd_mixer, MIXER_WRITE(SOUND_MIXER_PCM), &volume);
	if (ret < 0)
	{
		printf("set volume error!\n");
		return -1;
	}
	return 0;
}

/**This is the brief of the audio_setrate
* 	int audio_write(int fd_dsp, char *buf, int write_size)
*   this function will set volume.
*	@param fd_dsp. It is the dsp file descriptor.
*   @param buf. It is buf that will to play.
*   @param write_size. It is the size of the realistic content in buf.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     write()
*   @note    
*/
int audio_write(int fd_dsp, char *buf, int write_size)
{
	//check the param
	if (fd_dsp < 0)
	{
		printf("fd_dsp :[%d] is error!\n", fd_dsp);
		return -1;
	}
	if (buf==NULL)
	{
		printf("buf is NULL!\n");
		return -1;
	}
	if (write_size < 0)
	{
		printf("the param write_size :[%d] error!\n", write_size);
		return -1;
	}

	//get an databuf from buf
	//if (databuf_len+write_size < frag)
	//if (0)
	//{
	//	memcpy(databuf+databuf_len, buf, write_size);
	//	databuf_len += write_size;
	//}
	//else
	//{
		//get info.bytes
		audio_buf_info info;
		do
		{
			ioctl(fd_dsp, SNDCTL_DSP_GETOSPACE, &info);
			usleep(100);
		}
		while(info.bytes < frag);
		fd_set writefds;
		struct timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		FD_ZERO(&writefds);
		FD_SET(fd_dsp, &writefds);
		tv.tv_sec = 0;
		tv.tv_usec = 0;

		//write the data to device
		select(fd_dsp+1, NULL, &writefds, NULL, &tv);
		if(FD_ISSET(fd_dsp, &writefds))
		{
			write(fd_dsp, buf, write_size);
			return 1;
		}
		usleep(100);
		return 0;

	//	memset(databuf, 0, frag);
	//	databuf_len = 0;
	//	memcpy(databuf, buf, write_size);
	//	databuf_len += write_size;
	//}
	
}

/**This is the brief of the audio_close
* 	void audio_close(int fd_dsp, int fd_mixer)
*   this function can open the loudspeaker file descriptor.
*	@param fd_dsp. It is the dsp file descriptor.
*   @param fd_mixer. It is the mixer file descriptor.
*   @retval  void
*   @return  
*	@see     close()
*   @note    
*/
void audio_close(int fd_dsp, int fd_mixer)
{
	int bytes;
	//check the param
	if ((fd_dsp < 0) || (fd_mixer < 0))
	{
		printf("the param error!\n fd_dsp:[%d] fd_mixer:[%d]", fd_dsp, fd_mixer);
	}

	ioctl(fd_dsp,SNDCTL_DSP_GETODELAY,&bytes);
	printf("bytes:[%d]\n", bytes);
	int delay = bytes / (rate * 2 * 1);
	sleep(delay);
	printf("delay:[%d]\n", delay);
	
	close(fd_dsp);
	close(fd_mixer);
}

