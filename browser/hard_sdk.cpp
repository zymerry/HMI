#include <QByteArray>
#include <qwebview.h> 
#include <qdebug.h>
#include <qwebframe.h>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <string>
#include "hard_sdk.h"

static int mic_dsp_fd, mic_mixer_fd;
static int audio_dsp_fd, audio_mixer_fd;
static int gpio_fd1, gpio_fd2, gpio_fd3, gpio_fd4, gpio_fd5, gpio_fd6, gpio_arg;
extern "C"
{
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "hard.h"
}
/******************************  gpio  ****************************/
int Hard::gpio_open(int arg)
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
int Hard::gpio_setio(int arg, int direction)
{
	return _gpio_setio(arg, direction);
}
QString Hard::gpio_read(int arg, int size)
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
    //从gpio口读取数据到data
	_gpio_read(fd, data, size);
    //将char *转化为Qstring
    QString qstr = QString(QLatin1String(data));
    return qstr;
}
int Hard::gpio_write(int arg, const QString &str)
{
    int fd=0;
    gpio_arg = arg;

    //判断使用的是哪个gpio口
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
    //将Qstring转化为char *
    char *data=NULL;
    QByteArray ba = str.toLatin1();
    data = ba.data();
	return _gpio_write(fd, data);
}

void Hard::gpio_close(int arg)
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
int Hard::key_open()
{
    //打开按键设备-采用的是无阻塞的方式打开
    return _key_open();
}
int Hard::key_select()
{
    //轮循按键设备
    return _key_select();
}
void Hard::key_close()
{
    //关闭按键设备
    _key_close();
}
/***************************  gpio end  ***************************/

/****************************  serial  ****************************/
int Hard::serial_open(int arg)
{
    //打开一个串口
    return _serial_open(arg);
}
int Hard::serial_setopt(int arg, int nSpeed, int nBits, int Evnt, int nStop)
{
    //设置串口的工作模式
    return _serial_setopt(arg, nSpeed, nBits, Evnt, nStop);
}
QString Hard::serial_read(int arg, int size)
{
    int ret = 0;      //每次读到的数据大小
    int rd_count = 0;  //读到的数据的总的大小
    int arg_rtmp = 0; //表示从哪个串口读书据
    int size_rtmp = 0;//要读多大的数据
    char buf[1024];       //总的数据缓冲区
    char data_tmp[256];   //每次接收数据的数据缓冲区
    memset(buf, 0, 1024);
    memset(data_tmp, 0, 256);

    arg_rtmp = arg;
    size_rtmp = size;

    //保证接收一次完整的数据包
    do
    {
        ret = _serial_read(arg_rtmp, data_tmp, size_rtmp);
        if (ret > 0)
        {
            memcpy(buf+rd_count, data_tmp, ret);
            rd_count += ret;
            memset(data_tmp, 0, 256);
        }
    }
    while (ret > 0);

    //将char *转换为Qstring
    QString qstr = QString(QLatin1String(buf));
    return qstr;
}
int Hard::serial_write(int arg, int size, const QString &str)
{ 
    int arg_wtmp = 0;  //串口标志位，表示从哪个串口发送数据
    int size_wtmp = 0; //发送数据的大小

    arg_wtmp = arg;
    size_wtmp = size;

    //将Qstring数据转换为char *
    char *buf=NULL;
    QByteArray ba = str.toLatin1();
    buf = ba.data();
    return _serial_write(arg_wtmp, buf, size_wtmp);
}
void Hard::serial_close(int arg)
{
    _serial_close(arg);
}
/*************************  serial end  ***************************/

/*****************************  mic  ******************************/
static int file_fd;
static QFile file("/etc/file");
static QTextStream in(&file);
int Hard::mic_open()
{
    //以C和QFile两种方式打开"/etc/file"文件
    //打开文件的目的是通过文件来完成存储着二进制字符串的转换
    //char * 到 Qstring 和 Qstring 到 char *
	file_fd = _open("/etc/file");
	if (!file.open(QIODevice::ReadOnly|QIODevice::Text))       
	{
		printf("Can't open the file!\n");
	}
    //打开扬声器设备
    return _mic_open(&mic_dsp_fd, &mic_mixer_fd);
}

int Hard::mic_setopt(int samplerate, int rec_volume)
{
    return _mic_setopt(samplerate, rec_volume, mic_dsp_fd, mic_mixer_fd);
}

QString Hard::mic_read(int size)
{
    int ret;      //实际写的数据大小
    int read_size;//实际读到的数据大小
    int mic_size; //想要读取的数据大小
    char buf[1024*1024];      //数据缓冲区
    
    memset(buf, 0, 1024*1024);

    //从麦克风读取size大小的数据
    mic_size = size;
    read_size = _mic_read(mic_dsp_fd, buf, mic_size);

    //将char *转换为Qstring
    lseek(file_fd, SEEK_SET, 0);
    ret = _write(file_fd, buf, read_size);
    in.seek(0);
	QString str = in.read(read_size);
    return str;
}
#if 0
QTextStream in;
void Hard::mic_read_init()
{
	QFile file("/dev/dsp1");
	if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		printf("Can't open the file!\n");
	}
	QTextStream in (&file);
}
QString Hard::mic_read()
{
	QString str = in.read(mic_size);
	return str;
}
#endif
void Hard::mic_close()
{
    _mic_close(mic_dsp_fd, mic_mixer_fd);
}
/**************************  mic end  *****************************/

/***************************  audio  ******************************/
int Hard::audio_open()
{
    //打开扬声器设备
    return _audio_open(&audio_dsp_fd, &audio_mixer_fd);
}
int Hard::audio_init_frag(int frag)
{
    //获得frag
    return _audio_init_frag(audio_dsp_fd, frag);
}
int Hard::audio_setdef()
{
    //设置扬声器的默认工作方式
    return _audio_setdef(audio_dsp_fd, audio_mixer_fd);
}
int Hard::audio_setrate(int samplerate)
{
    //设置扬声器的波特率
    return _audio_setrate(audio_dsp_fd, samplerate);
}
int Hard::audio_setsound(int sound)
{
    //设置扬声器的声音大小
    return _audio_setsound(audio_mixer_fd, sound);
}
int Hard::audio_write(int size, const QString &str)
{
    char *buf=NULL;
    int audio_size;
    
    audio_size = size; //str的数据大小
    
    //将Qstring转化为char *
    QByteArray ba = str.toLatin1();
    buf = ba.data();
    //将数据写入扬声器设备
   return  _audio_write(audio_dsp_fd, buf, audio_size);
}
void Hard::audio_close()
{
    //关闭扬扬声器设备
    _audio_close(audio_dsp_fd, audio_mixer_fd);
}
/**************************  audio end  ***************************/

/*****************************  can  ******************************/
int static can_fd;
static int can_file;
static QFile cfile("/etc/can_file");
static QTextStream cf(&cfile);
int Hard::can_open()
{
    //以C和QFile两种方式打开"/etc/can_file"文件
    //打开文件的目的是通过文件来完成存储着二进制字符串的转换
    //char * 到 Qstring 和 Qstring 到 char *
	can_file = _open("/etc/can_file");
	if (!cfile.open(QIODevice::ReadOnly))       
	{
		printf("Can't open the file!\n");
	}
    can_fd = _can_open();
}
int Hard::can_setopt(int rate, int id, int mask)
{
    return _can_setopt(can_fd, rate, id, mask);
}
QString Hard::can_read(int size)
{
    int ret;
    char buf[16];
    memset(buf, 0, 16);
    ret = _can_read(can_fd, buf, size);
    if (ret == 0)
    {
        return NULL;
    }
    //将char *转换为Qstring
    lseek(can_file, SEEK_SET, 0);
    ret = _write(can_file, buf, size);
    cf.seek(0);
	QString qstr = cf.read(size);

    //QString qstr = QString(QLatin1String(buf));
    return qstr;
}
int Hard::can_write(int size, QString str)
{
    //将Qstring数据转换为char *
    char *buf=NULL;
    QByteArray ba = str.toLatin1();
    buf = ba.data();
    return _can_write(can_fd, buf, size);
}
void Hard::can_close()
{
    _can_close(can_fd);
}
/***************************  can end  ****************************/

/************************  audio-encode  **************************/
static int en_fd;
static QFile en_file("/etc/en_file");
static QTextStream en(&en_file);
int Hard::encode_init()
{
    //以C和QFile两种方式打开"/etc/en_file"文件
    //打开文件的目的是通过文件来完成存储着二进制字符串的转换
    //char * 到 Qstring 和 Qstring 到 char *
	en_fd = _open("/etc/en_file");
	if (!en_file.open(QIODevice::ReadOnly|QIODevice::Text))       
	{
		printf("Can't open the file!\n");
        return -1;
	}
    return 0;
}
QString Hard::encode(QString src)
{
    int wr_size;        //实际写入的数据大小
    int en_size;        //编码后音频数据的大小
    char dest[2048];    //编码后的音频数据
    
    //将Qstring数据转换为char *
    char *buf=NULL;
    QByteArray ba = src.toLatin1();
    buf = ba.data();
    //buf存放编码前的音频数据

    //将pcm转化为aac
    //输入buf-pcm
    //输出dest-aac
    en_size = 0;
    memset(dest, 0, 2048);
    en_size = _encode(buf, dest);
    //将char *转换为Qstring
    lseek(en_fd, SEEK_SET, 0);
    wr_size = _write(en_fd, dest, en_size);
    en.seek(0);
	QString dst = en.read(en_size);
    return dst;
}
void Hard::close_encode()
{
    _close(en_fd);
    en_file.close();
}
/*********************  audio-encode end  *************************/

/*************************  audio-decode  *************************/
static int de_fd;
static QFile de_file("/etc/de_file");
static QTextStream de(&de_file);
void Hard::DestroyAACDecoder()
{
    _close(de_fd);
    de_file.close();
    _DestroyAACDecoder();
}

int Hard::InitAACDecoder(int nSamplesPerSec, int nChannels)
{
    //以C和QFile两种方式打开"/etc/en_file"文件
    //打开文件的目的是通过文件来完成存储着二进制字符串的转换
    //char * 到 Qstring 和 Qstring 到 char *
	de_fd = _open("/etc/de_file");
	if (!de_file.open(QIODevice::ReadOnly))       
	{
		printf("Can't open the file!\n");
        return -1;
	}
    _InitAACDecoder(nSamplesPerSec, nChannels);
}

//int Hard::Decoder(unsigned char *pszAAC, unsigned int nLen, char *pszOut, int *pnOutLen)
int pnOutLen;
QString Hard::Decoder(int nlen, QString pszAAC)
{
    int wr_size = 0;
    int pcm_len = 102400;
    char pszOut[1024*1024];
    memset(pszOut, 0, 1024*1024);

    //将Qstring数据转换为char *
    char *buf=NULL;
    QByteArray ba = pszAAC.toLatin1();
    buf = ba.data();
    pnOutLen = _Decoder(buf, nlen, pszOut, &pcm_len);
    printf("pcm_len: %d\n", pcm_len);
    
    //将char *转换为Qstring
    lseek(de_fd, SEEK_SET, 0);
    wr_size = _write(de_fd, pszOut, pcm_len);
    de.seek(0);
	QString dst = de.read(pcm_len);
    return dst;

}
int Hard::get_pnOutLen()
{
    return pnOutLen;
}
/*********************  audio-decode end  *************************/

/*************************  file  *********************************/
static int ffd;
static QFile file_tmp("/mnt/nand1-2/123");
static QTextStream file_test(&file_tmp);
int Hard::file_open_p(QString file_name)
{
	//if (!file_tmp.open(QIODevice::ReadOnly|QIODevice::Text))       
	if (!file_tmp.open(QIODevice::ReadOnly))       
	{

		printf("Can't open the file!\n");
        return -1;
	}
    
}
QString Hard::file_read_p(int size)
{
    QString rd_str = file_test.read(size);
    return rd_str;
}
int Hard::file_open(QString file_name)
{
    char *buf=NULL;
    QByteArray ba = file_name.toLatin1();
    buf = ba.data();
    ffd = _open(buf);
    return ffd;
}
int Hard::file_write(int size, QString src)
{
    //将Qstring数据转换为char *
    char *buf=NULL;
    QByteArray ba = src.toLatin1();
    buf = ba.data();
    
    _write(ffd, buf, size);
}

QString Hard::file_read(int size)
{
    char data[1024*1024];
    memset(data, 0, 1024*1024);

}
int Hard::file_close(int fd)
{
    _close(fd);
}
QString Hard::getlocaltime()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    return current_date;
}
/**********************  file  end  *******************************/
Hard::Hard( QObject *parent ) 
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
void Hard::setWebView( QWebView *view ) 
{
    webview = view;
    frame = view->page()->mainFrame();
	connect( frame, SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(attachObject()) );
}

void Hard::attachObject() 
{ 
    frame->addToJavaScriptWindowObject( QString("hard"), this );
}

void Hard::onRecvSocket()
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

void Hard::print( const QString &param ) 
{
    qDebug() << "Print paramter from js script:" << param;
}

QString Hard::getMsg()
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

int Hard::indexOf(const QString &string, const QString &find)
{
    return string.indexOf(find);
}

int Hard::lastIndexOf(const QString &string, const QString &find)
{
    return string.lastIndexOf(find);
}

void Hard::load(const QString &url)
{
    QUrl loadUrl = QUrl(url);

    webview->load(loadUrl);

    qDebug() << "load";
}

int Hard::getCurrentPageNum()
{
    return pageNum;
}

void Hard::setCurrentPageNum(int number)
{
    pageNum = number;
}


