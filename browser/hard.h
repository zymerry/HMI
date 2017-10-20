#ifndef HHH_HARD_HHH
#define HHH_HARD_HHH
/*******************************  gpio  ***************************/
int _gpio_open(int arg);
int _gpio_setio(int arg, int direction);
int _gpio_read(int fd, char *data, int size);
int _gpio_write(int fd, char *data);
void _gpio_close(int gpio_fd);
/*****************************  gpio end  *************************/

/********************************  key  ***************************/
int _key_open();
int _key_select();
void _key_close();
/*******************************  key end  ************************/

/********************************  serial  ************************/
int _serial_open(int arg);
int _serial_setopt(int arg, int nSpeed, int nBits, int Evnt, int nStop);
int _serial_read(int arg, char *buf, size_t len);
int _serial_write(int arg, const char *buf, size_t len);
void _serial_close(int arg);
/******************************  serial end  **********************/

/***********************************  mic  ************************/
int _mic_open(int *dsp_fd, int *mixer_fd);
int _mic_setopt(int samplerate, int rec_volume, int dsp_fd, int mixer_fd);
int _mic_read(int dsp_fd, char *buf, int size);
void _mic_close(int dsp_fd, int mixer_fd);
/**********************************  mic end  *********************/

/*********************************  audio  ************************/
int _audio_open(int *dsp_fd, int *mixer_fd);
int _audio_init_frag(int dsp_fd);
int _audio_setdef(int dsp_fd, int mixer_fd);
int _audio_setrate(int dsp_fd, int samplerate);
int _audio_setsound(int mixer_fd, int sound);
int _audio_write(int dsp_fd, char *buf, int write_size);
void _audio_close(int dsp_fd, int mixer_fd);
/********************************  audio end  *********************/

/**********************************  can  *************************/
int _can_open();
int _can_setopt(int fd, int rate, int id, int mask);
int _can_read(int fd, char *buf, int size);
int _can_write(int fd, char *buf, int size);
void _can_close(int fd);
/********************************  can end  ***********************/

/******************************  audio-encode  ********************/
int _encode(const char *src, char *dst);
/****************************  audio-encode end  ******************/

/******************************  audio-decode  ********************/
void _DestroyAACDecoder();
int _InitAACDecoder(int nSamplesPerSec, int nChannels);
int _Decoder(char *pszAAC, unsigned int nLen, char *pszOut, int *pnOutLen);
/***************************  audio-decode  end  ******************/
//file---
int _open(char *file_name);
int _write(int fd, char *buf, int file_size);
int _read(int fd, char *buf, int size);
int _close(int fd);
#endif //HHH_HARD_HHH
