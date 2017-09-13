#ifndef __FANCY_H__ 
#define __FANCY_H__

#include <qobject.h>
#include <QUdpSocket>

class QWebView; 
class QWebFrame;

class Fancy : public QObject 
{ 
    Q_OBJECT
public: 
	Fancy( QObject *parent );

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

//gpio-------------------------------------
	int gpio_open(int arg);
	int gpio_setio(int arg, int direction);
	QString gpio_read(int arg, int size);
    int gpio_set_write(int arg);
	int gpio_write(const QString &data);
	void gpio_close(int arg);
//key--------------------------------------
int key_open();
int key_select();
void key_close();
//serial-----------------------------------
int serial_open(int arg);
int serial_setopt(int arg, int nSpeed, int nBits, int Evnt, int nStop);
//int serial_read(int arg, char *buf, size_t len);
QString serial_read();
//int serial_write(int arg, const QString &str, size_t len);
int serial_write(const QString &str);
void serial_close(int arg);
void serial_set_write(int arg, int size);
void serial_set_read(int arg, int size);
//mic---------------------------------------
int mic_open();
int mic_setopt(int samplerate, int rec_volume);
//int mic_read(int dsp_fd, char *buf, int size);
//void mic_read_init();
int mic_set_read(int size);
QString mic_read();
void mic_close();
//audio--------------------------------------
int audio_open();
int audio_init_frag();
int audio_setdef();
int audio_setrate(int samplerate);
int audio_setsound(int sound);
int audio_set_write(int write_size);
int audio_write(const QString &buf);
void audio_close();

//for opreate file
int open_file();
//int write_file(const QString &str);
//QString read_file();
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
