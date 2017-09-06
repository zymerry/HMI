#include <qdebug.h> 
#include <qwebview.h> 
#include <qwebframe.h>

#include "fancy.h"

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
