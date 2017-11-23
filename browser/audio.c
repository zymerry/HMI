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
* 	int audio_open(int *dsp_fd, int *mixer_fd)
*   this function can open the loudspeaker file descriptor.
*	@param dsp_fd. It is the dsp file descriptor.
*   @param mixer_fd. It is the mixer file descriptor.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     open()
*   @note    
*/
int _audio_open(int *dsp_fd, int *mixer_fd)
{
	//open the file descriptor
	*dsp_fd = open("/dev/dsp", O_RDWR|O_NONBLOCK);
	if (*dsp_fd < 0)
	{
		return -1;
	}
	*mixer_fd = open("/dev/mixer", O_RDWR|O_NONBLOCK);
	if (*mixer_fd < 0)
	{
		return -1;
	}
	
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
int _audio_init_frag(int dsp_fd, int frag_t)
{
	//check the param
    if (!(frag_t==1||frag_t==2||frag_t==3||frag_t==4))
    {
        return -1;
    }
	if (dsp_fd < 0)
	{
		return -1;
	}
	//get the frag
    frag = frag_t;
    int bquart = 0;
    switch (frag_t)
    {
        case 1:
            bquart = 0x000a;
        case 2:
            bquart = 0x000b;
        case 3:
            bquart = 0x000c;
        case 4:
            bquart = 0x000d;
        default:
            bquart = 0x000a;
    }

    frag = (0x0002 << 16) + bquart;
    ioctl(dsp_fd, SNDCTL_DSP_SETFRAGMENT, &frag);
	ioctl(dsp_fd, SNDCTL_DSP_GETBLKSIZE, &frag);

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
int _audio_setdef(int dsp_fd, int mixer_fd)
{
	int oss_format, channels, ret;
	//set samplerate and sound with default of nature
	int samplerate = 8000;
	int volume = 0x50;
	
	//check the param dsp_fd and param mixer_fd
	if (dsp_fd < 0 || mixer_fd < 0)
	{
		return -1;
	}
	//set byte-order
	//standard 16bit little endian format, support this format only
	oss_format=AFMT_S16_LE;
	ioctl(dsp_fd, SNDCTL_DSP_SETFMT, &oss_format);

	//set channels
	channels = 2;
	ioctl(dsp_fd, SNDCTL_DSP_CHANNELS, &channels);

	//set the samplerate-16000 and the sound-0x50
	ret = ioctl(dsp_fd, SNDCTL_DSP_SPEED, &samplerate);
	if (ret < 0)
	{
		return -1;
	}
	ret = ioctl(mixer_fd, MIXER_WRITE(SOUND_MIXER_PCM), &volume);
	if (ret < 0)
	{
		return -1;
	}
	
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
int _audio_setrate(int dsp_fd, int samplerate)
{
	int sample_rate;
	int ret;

	//check the param
	if (!(samplerate==8000 || samplerate==11025 || samplerate==16000 ||
		samplerate==22050 || samplerate==24000 || samplerate==32000 ||
		samplerate==44100 || samplerate==48000))
	{
		return -1;
	}
	if (dsp_fd < 0)
	{
		return -1;
	}
	
	//set samplerate
	rate = samplerate;
	sample_rate = samplerate;
	ret = ioctl(dsp_fd, SNDCTL_DSP_SPEED, &sample_rate);
	if (ret < 0)
	{
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
int _audio_setsound(int mixer_fd, int sound)
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
		return -1;
	}
	//set sound
	volume = sound;
	ret = ioctl(mixer_fd, MIXER_WRITE(SOUND_MIXER_PCM), &volume);
	if (ret < 0)
	{
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
int _audio_write(int dsp_fd, char *buf, int write_size)
{
    int ret;
	//check the param
	if (dsp_fd < 0)
    {
		return -1;
	}
	if (buf==NULL)
	{
		return -1;
	}
	if (write_size < 0)
	{
		return -1;
	}

	//get info.bytes
	audio_buf_info info;
	do
	{
        printf("in while..info.bytes:[%d].....frag:[%d]....\n", \ 
                info.bytes, frag);
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
		ret = write(dsp_fd, buf, write_size);
		return ret;
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
void _audio_close(int dsp_fd, int mixer_fd)
{
	//check the param
	if ((dsp_fd < 0) || (mixer_fd < 0))
	{
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

