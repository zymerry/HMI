#ifndef __HARD_SDK_H__ 
#define __HARD_SDK_H__

#include <qobject.h>
#include <QUdpSocket>

class QWebView; 
class QWebFrame;

class Hard : public QObject 
{ 
    Q_OBJECT
public: 
	Hard( QObject *parent );

	void setWebView( QWebView *view );


    // flush flag
    bool needFlush;

public slots: 
    void print( const QString &param );
    QString getMsg();
    int indexOf(const QString &string, const QString &find);
    int lastIndexOf(const QString &string, const QString &find);
    void load(const QString &url);
    int getCurrentPageNum();
    void setCurrentPageNum(int number);

/******************************  gpio  ****************************/
	int gpio_open(int arg);
	int gpio_setio(int arg, int direction);
	QString gpio_read(int arg, int size);
	int gpio_write(int arg, const QString &data);
	void gpio_close(int arg);
/****************************  end gpio  **************************/

/*******************************  key  ****************************/
int key_open();
int key_select();
void key_close();
/*****************************  end key  **************************/

/******************************  serial  **************************/
int serial_open(int arg);
int serial_setopt(int arg, int nSpeed, int nBits, int Evnt, int nStop);
//int serial_read(int arg, char *buf, size_t len);
QString serial_read(int arg, int size);
int serial_write(int arg, int size, const QString &str);
void serial_close(int arg);
/*****************************  end serial  ***********************/

/********************************  mic  ***************************/
int mic_open();
int mic_setopt(int samplerate, int rec_volume);
QString mic_read(int size);
void mic_close();
/******************************  end mic  *************************/

/*******************************  audio  **************************/
int audio_open();
int audio_init_frag();
int audio_setdef();
int audio_setrate(int samplerate);
int audio_setsound(int sound);
int audio_write(int size, const QString &buf);
void audio_close();
/******************************  end audio  ***********************/

/********************************  can  ***************************/
int can_open();
int can_setopt(int rate, int id, int mask);
QString can_read(int size);
int can_write(int size,QString str);
void can_close();
/*******************************  end can *************************/

/****************************  audio-encode  **********************/
int encode_init();
QString encode(QString src);
void close_encode();
/***************************  audio-encode end  *******************/

/****************************  audio-decode  **********************/
void DestroyAACDecoder();
int InitAACDecoder(int nSamplesPerSec, int nChannels);
QString Decoder(int nlen, QString pszAAC);
int get_pnOutLen();
/***************************  audio-decode end  *******************/

/*******************************  file  ***************************/
int file_open(QString file_name);
int file_write(int size, QString src);
QString file_read(int size);
int file_close(int fd);
QString getlocaltime();
/*****************************  file end  *************************/

private slots: 
	void attachObject();
    void onRecvSocket();

private: 
    QWebView *webview;
    QWebFrame *frame;
    QString msg;
    QUdpSocket *recvSocket;

    QHostAddress ip;
    unsigned short port;
    int pageNum;
};

#endif // __FANCY_H__
