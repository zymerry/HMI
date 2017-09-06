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
