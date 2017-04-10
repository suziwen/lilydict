/****************************************************************************
**
** Copyright (C) 2016 lieefu Way.
** All rights reserved.
** Contact: lieefu@gmail.com
**
** This file is part of the ShanbayDict.
**
** $BEGIN_LICENSE:LGPL$
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 3 as published by the Free Software Foundation and
** appearing in the file LICENSE included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 3 requirements will be met:
** http://www.gnu.org/licenses/lgpl.html.
**
** $END_LICENSE$
**                                                    2016/5/5
****************************************************************************/
#ifndef YOUDAONET_H
#define YOUDAONET_H

#include <QObject>
class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;
class YoudaoDict : public QObject
{
    Q_OBJECT
public:
    explicit YoudaoDict(QObject *parent = 0);
    
signals:
    void signalRetWordinfo(const QString &wordinfo);
public slots:
    void httpfinished(QNetworkReply*);
public:
    void connect();
    void queryWord(const QString &word);
    QNetworkAccessManager * http;
};

#endif // YOUDAONET_H
