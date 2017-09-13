#include <QByteArray>
#include <qwebview.h> 
#include <qdebug.h>
#include <qwebframe.h>
#include <QFile>
#include <QFileInfo>
#include <string>

#include "fancy.h"

static int arg_wtmp, arg_rtmp;
static int size_wtmp, size_rtmp;
static int mic_dsp_fd, mic_mixer_fd, mic_size;
static int audio_dsp_fd, audio_mixer_fd, audio_size;
static int gpio_fd1, gpio_fd2, gpio_fd3, gpio_fd4, gpio_fd5, gpio_fd6, gpio_arg;
static int read_size;
extern "C"
{
#include <stdio.h>
#include <unistd.h>
#include "hard.h"
}
//gpio------------------------------
int Fancy::gpio_open(int arg)
{
    int fd;
	fd = _gpio_open(arg);
    switch (arg)
    {
        case 1:
            gpio_fd1 = fd;
            break;
        case 2:
            gpio_fd2 = fd;
            break;
        case 3:
            gpio_fd3 = fd;
            break;
        case 4:
            gpio_fd4 = fd;
            break;
        case 5:
            gpio_fd5 = fd;
            break;
        case 6:
            gpio_fd6 = fd;
            break;
    }
    return fd;
}
int Fancy::gpio_setio(int arg, int direction)
{
	return _gpio_setio(arg, direction);
}
QString Fancy::gpio_read(int arg, int size)
{
    int fd=0;
    char data[1024];

    memset(data, 0, 1024);
    switch (arg)
    {
        case 1:
            fd = gpio_fd1;
            break;
        case 2:
            fd = gpio_fd2;
            break;
        case 3:
            fd = gpio_fd3;
            break;
        case 4:
            fd = gpio_fd4;
            break;
        case 5:
            fd = gpio_fd5;
            break;
        case 6:
            fd = gpio_fd6;
            break;
    }
	_gpio_read(fd, data, size);
    QString qstr = QString(QLatin1String(data));
    return qstr;
}
int Fancy::gpio_set_write(int arg)
{
    gpio_arg = arg;
    return 0;
}
int Fancy::gpio_write(const QString &str)
{
    int fd=0;
    switch (gpio_arg)
    {
        case 1:
            fd = gpio_fd1;
            break;
        case 2:
            fd = gpio_fd2;
            break;
        case 3:
            fd = gpio_fd3;
            break;
        case 4:
            fd = gpio_fd4;
            break;
        case 5:
            fd = gpio_fd5;
            break;
        case 6:
            fd = gpio_fd6;
            break;
    }
    char *data=NULL;
    QByteArray ba = str.toLatin1();
    data = ba.data();
	return _gpio_write(fd, data);
}

void Fancy::gpio_close(int arg)
{
    int close_fd=0;
    switch (arg)
    {
        case 1:
            close_fd = gpio_fd1;
            break;
        case 2:
            close_fd = gpio_fd2;
            break;
        case 3:
            close_fd = gpio_fd3;
            break;
        case 4:
            close_fd = gpio_fd4;
            break;
        case 5:
            close_fd = gpio_fd5;
            break;
        case 6:
            close_fd = gpio_fd6;
            break;
    }
	_gpio_close(close_fd);
}

//key--------------------------------------
int Fancy::key_open()
{
    return _key_open();
}
int Fancy::key_select()
{
    return _key_select();
}
void Fancy::key_close()
{
    _key_close();
}

//serial------------------------------------
int Fancy::serial_open(int arg)
{
    return _serial_open(arg);
    

}
int Fancy::serial_setopt(int arg, int nSpeed, int nBits, int Evnt, int nStop)
{
    qDebug() << "arg :" << arg;
    qDebug() << "\nnSpeed: " << nSpeed;
    qDebug() << "\nnBits: " << nBits;
    qDebug() << "\nnEvent: " << nStop;
    return _serial_setopt(arg, nSpeed, nBits, Evnt, nStop);
}
QString Fancy::serial_read()
{
    char buf[1024];
    memset(buf, 0, 1024);
    _serial_read(arg_rtmp, buf, size_rtmp);
    QString qstr = QString(QLatin1String(buf));
    return qstr;
}
//int Fancy::serial_write(int arg, char *buf, size_t len)
//int Fancy::serial_write(int arg, const QString &str, size_t len)
int Fancy::serial_write(const QString &str)
{ 
    qDebug() << "str :" << str;
    char *buf=NULL;
    QByteArray ba = str.toLatin1();
    buf = ba.data();
    //return _serial_write(arg, buf, len);
    return _serial_write(arg_wtmp, buf, size_wtmp);
}
void Fancy::serial_close(int arg)
{
    _serial_close(arg);
}
void Fancy::serial_set_write(int arg, int size)
{
    arg_wtmp = arg;
    size_wtmp = size;
}
void Fancy::serial_set_read(int arg, int size)
{
    arg_rtmp = arg;
    size_rtmp = size;
}

//mic------------------------------------------
int Fancy::mic_open()
{
    return _mic_open(&mic_dsp_fd, &mic_mixer_fd);
}
int Fancy::mic_setopt(int samplerate, int rec_volume)
{
    return _mic_setopt(samplerate, rec_volume, mic_dsp_fd, mic_mixer_fd);
}
static int file_fd;

static QFile file("/etc/fifo");
static QTextStream in(&file);
int Fancy::mic_set_read(int size)
{
    printf("before QT open file\n");
	if (!file.open(QIODevice::ReadWrite|QIODevice::Text))       
	{
		printf("Can't open the file!\n");
	}
    printf("before C open file\n");
	file_fd = _open();
    printf("open file successful!file_fd:%d\n", file_fd);
    mic_size = size;
    return 0;
}
static int count = 1;
QString Fancy::mic_read()
{
    int ret;
    char buf[8192];
    memset(buf, 0, 8192);
    read_size = _mic_read(mic_dsp_fd, buf, 8192);
    printf("read from mic successful!read_file:%d\n", read_size);
    ret = _write(file_fd, buf, read_size);
    printf("111write to fifo successful!%d\n", ret);
    printf("in.read---%d\n", read_size);
	QString str = in.read(read_size);
    printf("read from fifo successful !\n");
	//std::string str = buf;
	//QString qstr = QString::fromStdString(str);
    //QString qstr = QString(QLatin1String(buf));
    return str;
}
#if 0
QTextStream in;
void Fancy::mic_read_init()
{
	QFile file("/dev/dsp1");
	if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		printf("Can't open the file!\n");
	}
	QTextStream in (&file);
}
QString Fancy::mic_read()
{
	QString str = in.read(mic_size);
	return str;
}
#endif
void Fancy::mic_close()
{
    _mic_close(mic_dsp_fd, mic_mixer_fd);
}

//audio-----------------------------------------
int Fancy::audio_open()
{
    return _audio_open(&audio_dsp_fd, &audio_mixer_fd);
}
int Fancy::audio_init_frag()
{
    return _audio_init_frag(audio_dsp_fd);
}
int Fancy::audio_setdef()
{
    return _audio_setdef(audio_dsp_fd, audio_mixer_fd);
}
int Fancy::audio_setrate(int samplerate)
{
    return _audio_setrate(audio_dsp_fd, samplerate);
}
int Fancy::audio_setsound(int sound)
{
    return _audio_setsound(audio_mixer_fd, sound);
}
int Fancy::audio_set_write(int write_size)
{
    audio_size = write_size;
    return 0;
}
int Fancy::audio_write(const QString &str)
{
    char *buf=NULL;
    int size;
    QByteArray ba = str.toLatin1();
    buf = ba.data();
    if (read_size != audio_size)
        audio_size = read_size;
    qDebug() << "audio_size :" << audio_size;
    size = _audio_write(audio_dsp_fd, buf, audio_size);
    qDebug() << "audio_write size :%d" << size;
}
void Fancy::audio_close()
{
    _audio_close(audio_dsp_fd, audio_mixer_fd);
}

//for file-----
int Fancy::open_file()
{
    return _open();
}
#if 0
int Fancy::write_file(const QString &str)
{
    char *buf=NULL;
    QByteArray ba = str.toLatin1();
    buf = ba.data();
    return _write(buf);
}

QString Fancy::read_file()
{
    char data[1024*1024];
    memset(data, 0, 1024*1024);
    _read(audio_size, data);
    QString qstr = QString(QLatin1String(data));
    return qstr;
}
#endif
Fancy::Fancy( QObject *parent ) 
	: QObject( parent ) 
{
//    msg = "{\"hardver\" : \"v1.0.3\", \"softver\" : \"v1.0.3\"}";
    ip = "127.0.0.1";
    port = 29374;

    recvSocket = new QUdpSocket();
    recvSocket->bind(ip, port, QUdpSocket::DontShareAddress);

    connect(recvSocket, SIGNAL(readyRead()), this, SLOT(onRecvSocket()));

    needFlush = false;
    pageNum = 1;
}
void Fancy::setWebView( QWebView *view ) 
{
    webview = view;
    frame = view->page()->mainFrame();
	connect( frame, SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(attachObject()) );
}

void Fancy::attachObject() 
{ 
    frame->addToJavaScriptWindowObject( QString("fancy"), this );
}

void Fancy::onRecvSocket()
{
    while(recvSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(recvSocket->pendingDatagramSize());
        recvSocket->readDatagram(datagram.data(), datagram.size());
        msg = QString(datagram);
        needFlush = true;
        qDebug() << "recv msg: " << msg;
    }
}

void Fancy::print( const QString &param ) 
{
    qDebug() << "Print paramter from js script:" << param;
}

QString Fancy::getMsg()
{
    if ( true == needFlush )
    {
        needFlush = false;
        qDebug() << "getMsg: " << msg;
        return msg;
    }
    else
    {
        return QString("");
    }
}

int Fancy::indexOf(const QString &string, const QString &find)
{
    return string.indexOf(find);
}

int Fancy::lastIndexOf(const QString &string, const QString &find)
{
    return string.lastIndexOf(find);
}

void Fancy::load(const QString &url)
{
    QUrl loadUrl = QUrl(url);

    webview->load(loadUrl);

    qDebug() << "load";
}

int Fancy::getCurrentPageNum()
{
    return pageNum;
}

void Fancy::setCurrentPageNum(int number)
{
    pageNum = number;
}


