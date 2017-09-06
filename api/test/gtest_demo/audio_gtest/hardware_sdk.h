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

//the audio
int audio_open(int *fd_dsp, int *fd_mixer);
int audio_setdef(int fd_dsp, int fd_mixer);
int audio_setrate(int fd_dsp, int samplerate);
int audio_setsound(int fd_mixer, int sound);
int audio_write(int fd_dsp, char *buf, int write_size);
void audio_close(int fd_dsp, int fd_mixer);
int init_frag(int fd_dsp);


//the GPIO
void select_num(int tmp, char *buf);
int gpio_open(int arg);
int gpio_setio(int arg, int direction);
int gpio_read(int fd, char *data, int size);
int gpio_write(int fd, char *data);
void gpio_close(int gpio_fd);

//the key
int key_open();
int key_select();
void key_close();

//the mic
int mic_open(int *dsp_fd, int *mixer_fd);
int mic_setopt(int samplerate, int rec_volume, int dsp_fd, int mixer_fd);
int mic_read(int dsp_fd, char *buf, int size);
void mic_close(int dsp_fd, int mixer_fd);

//the serial
int serial_open(int arg);
int serial_setopt(int fd, int nSpeed, int nBits, char nEvent, int nStop);
int serial_read(int fd, unsigned char *buf, size_t len);
int serial_write(int fd, unsigned char *buf, size_t len);
void serial_close(int fd);
#endif
