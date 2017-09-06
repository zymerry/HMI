/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include <QtNetwork>
#include <QtWebKit>
#include "mainwindow.h"

MainWindow::MainWindow(const QUrl& url)
{
//	QFile file;
//    file.setFileName(":/jquery.min.js");
//	file.open(QIODevice::ReadOnly);
//	jQuery = file.readAll();
//	file.close();

	QNetworkProxyFactory::setUseSystemConfiguration(true);

	view = new QWebView(this);
    view->load(url);
    connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));
    view->installEventFilter(this);
    view->page()->installEventFilter(this);
    view->page()->mainFrame()->installEventFilter(this);

	Fancy* fancy = new Fancy( view );
    fancy->setWebView( view );

	QWebSettings *settings = view->page()->settings();
	settings->setAttribute(QWebSettings::JavascriptEnabled, true);
	settings->setAttribute(QWebSettings::JavascriptCanAccessClipboard, true);
	settings->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
	settings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
	settings->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
	settings->setAttribute(QWebSettings::JavascriptCanCloseWindows, true);
	settings->setAttribute(QWebSettings::AutoLoadImages, true);

	setCentralWidget(view);
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::finishLoading(bool)
{
//    view->page()->mainFrame()->evaluateJavaScript(jQuery);

    qDebug() << "finishLoading";
}

bool MainWindow::eventFilter(QObject *obj, QEvent *ev)
{
    if(ev->type() == QEvent::KeyPress)  
    {  
        return true;
    }
    return false;
}
