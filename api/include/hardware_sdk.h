/**
* @file      hardware_sdk.h
* @brief     in this file function math defined.
* @details   
* @author    zy
* @date      2017/06/15
* @version   HMI-T001
* @par Copyright (c)
*      keluofeite
* @par History:
*
*   version: author, date, desc\n
*/
#ifndef H_HARDWARE_SDK
#define H_HARDWARE_SDK
#include <sys/types.h>

/************************ the audio *************************/
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
int audio_open(int *fd_dsp, int *fd_mixer);

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
int audio_setdef(int fd_dsp, int fd_mixer);

/**This is the brief of the audio_setrate
* 	int audio_setrate(int dsp_fd, int samplerate)
*   this function will set samplerate of the loudspeaker.
*	@param dsp_fd. It is the dsp file descriptor.
*   @param samplerate. It is the of the loudspeaker.
*          value range:800, 11025, 16000, 22050, 24000, 32000, 44100, 48000.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     ioctl()
*   @note    
*/
int audio_setrate(int fd_dsp, int samplerate);

/**This is the brief of the audio_setrate
* 	int audio_setsound(int mixer_fd, int sound)
*   this function will set volume.
*	@param dsp_fd. It is the dsp file descriptor.
*   @param sound. It is the sound.
*          value range: (0, +~).
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     ioctl()
*   @note    
*/
int audio_setsound(int fd_mixer, int sound);

/**This is the brief of the audio_write
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
int audio_write(int fd_dsp, char *buf, int write_size);

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
void audio_close(int fd_dsp, int fd_mixer);

/**This is the brief of the audio_init_frag
* 	int audio_init_frag()
*   this function can get the buf of the dsp,which you should save sound data in.
*	@param dsp_fd. It is the dsp file descriptor.
*   @retval  
*   @return  
*	@see     
*   @note    
*/
int audio_init_frag(int fd_dsp);
/************************* audio end ************************************/

/******************************** the GPIO ******************************/
/**This is the brief of the gpio_open
* 	int gpio_open(int arg)
*   this function can define a gpio.
*	@param arg. (1~11)It is the gpio num that you want to use.
*          value range: 1~11.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     open()
*   @note    
*/
int gpio_open(int arg);

/**This is the brief of the gpio_setio
* 	int gpio_setio(int arg, int direction)
*   this function can define a gpio's direction.
*	@param arg. (1~11)It is the gpio num that you want to use.
*   @param direction. It is the direction (in or out).in-1 out-0
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     open()
*   @note    
*/
int gpio_setio(int arg, int direction);

/**This is the brief of the gpio_read
* 	int gpio_read(int fd, char *data)
*   this function will read data from gpio.
*	@param arg. the gpio file descriptor that is opened 
*   @param data. It saves the data that read from gpio.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     read()
*   @note    
*/
int gpio_read(int fd, char *data, int size);

/**This is the brief of the gpio_write
* 	int gpio_write(int fd, char *data)
*   this function will write data to gpio.
*	@param arg. the gpio file descriptor that is opened 
*   @param data. It saves the data that write to gpio.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     write()
*   @note    
*/
int gpio_write(int fd, char *data);

/**This is the brief of the gpio_close
* 	void gpio_close(int gpio_fd)
*   this function will write data to gpio.
*	@param gpio_fd. the gpio file descriptor. 
*   @retval  void
*   @return
*	@see     close()
*   @note    
*/
void gpio_close(int gpio_fd);
/************************* GPIO end *************************************/

/************************************ the key ***************************/
/**This is the brief of the key_open
*	int key_open()
*	this function can open the button file descriptor.
*	@param have no parama.
*	@retval  int
*	@return on success zero is returned.On error, -1 is returned.
*	@see	 
*	@note	 
*/
int key_open();

/**This is the brief of the key_select
*	int key_select()
*	this function can select the button, when anyone of the buttons is pressed.
*	@param have no parama.
*	@retval  int
*	@return  on success the number which signed a button is returned.On error, -1 is returned.
*	@see	 
*	@note	 
*/
int key_select();

/**This is the brief of the key_close
*	int key_close()
*	this function can close the button for the next use.
*	@param have no parama.
*	@retval  void
*	@return  
*	@see	 close()
*	@note	 
*/
void key_close();
/*************************************** key_close end ******************************/

/************************************* the mic **********************************/
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
int mic_open(int *dsp_fd, int *mixer_fd);

/**This is the brief of the mic_setopt
* 	int mic_setopt(int samplerate, int rec_volume£¬int dsp_fd, int mixer_fd)
*   this function can set the microphone working condition.
*   @param samplerate. It is the sampling frequency.
*          value range:8000, 11025, 16000, 22050, 24000, 32000, 44100, 48000.
*   @param rec_volume. It is the sound.
*          value range: (0, +~)
*	@param dsp_fd. It is the dsp file descriptor.
*   @param mixer. It is the mixer file descriptor.
*   @retval  int
*   @return  on success zero is returned.On error, -1 is returned.
*	@see     ioctl()
*   @note    
*/
int mic_setopt(int samplerate, int rec_volume, int dsp_fd, int mixer_fd);

/**This is the brief of the mic_read
* 	int mic_read(int dsp_fd, char *buf, int size)
*   this function can set the microphone working condition.
*	@param dsp_fd. It is the dsp file descriptor.
*   @retval  int
*   @return  on success the realistic size that read returned.On error, -1 is returned.
*	@see     read()
*   @note    
*/
int mic_read(int dsp_fd, char *buf, int size);

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
void mic_close(int dsp_fd, int mixer_fd);
/*************************** mic end *****************************/

/************************* the serial ****************************/
/**This is the brief of the serial_open
* 	int serial_open(int arg);
*   this function can open the 485 serial file descriptor.
*	@param	 arg. It is the 485 serial number.It is the serial that you want to open.
*            value range : 1, 2. 
*   @retval  int
*   @return  on success the serial file descriptor is returned.On error, -1 is returned.
*	@see     open()
*   @note    
*/
int serial_open(int arg);

/**This is the brief of the serial_setopt
* 	int serial_setopt(int fd, int nSpeed, int nBits, char nEvent, int nStop);
*   this function can set the 485 serial.The baud rate and the data bits and the odd-even check 
*   and the stop bit that you can set. 
*	@param	 fd. It is the 485 serial file descriptor.
*   @param   nSpeed. It is the baud rate.
*            value range: 2400, 4800, 9600, 19200, 57600, 115200, 23400, 460800, 921600.
*   @param   bBits. It is the data bits.
*            value range: 7, 8.
*   @param   nEvent. It is the odd-even check.
*            value range: 'O'-odd, 'E'-even parity check, 'N'-no odd-even.
*   @param   nStop. It is the stop bit.
*            value range: 1-one stop bit, 2-two stop bits.
*   @retval  int
*   @return  on success zerro is returned.On error, -1 is returned.
*	@see     
*   @note    
*/
int serial_setopt(int fd, int nSpeed, int nBits, char nEvent, int nStop);

/**This is the brief of the serial_read
* 	int serial_read(int fd, unsigned char *buf, size_t len)
*   this function can read the 485 serial file descriptor, It can save the data on buf.
*	@param	 fd. It is the 485 serial file descriptor.
*   @param   buf. Data buf.
*   @param   len. It is the size that read.
*   @retval  int (int fd, unsigned char *buf, size_t len)
*   @return  on success realistic size that read.On error, -1 is returned.
*	@see     read()
*   @note    
*/
int serial_read(int fd, unsigned char *buf, size_t len);

/**This is the brief of the serial_write
* 	int serial_write(int fd, unsigned char *buf, size_t len)
*   this function can write the 485 serial file descriptor.
*	@param	 fd. It is the 485 serial file descriptor.
*   @param   buf. Data buf.
*   @param   len. It is the size that read.
*   @retval  int 
*   @return  on success realistic size that write.On error, -1 is returned.
*	@see     write()
*   @note
*/
int serial_write(int fd, unsigned char *buf, size_t len);

/**This is the brief of the serial_write
* 	void serial_close(int fd)
*   this function can close the 485 serial file descriptor.
*	@param	 fd. It is the 485 serial file descriptor.
*   @retval  
*   @return  
*	@see     close()
*   @note
*/
void serial_close(int fd);
/***************** serial end ************************************/
#endif
