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
#ifndef DICTLOGO_H
#define DICTLOGO_H
#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
class Dictlogo : public QLabel
{
    Q_OBJECT
public:
    explicit Dictlogo(QWidget *parent = 0);

signals:
    void Clicked();
public slots:
    void autohide();
public:
    void popup();
private:
    QTimer *timer;
    qreal timercount;
    bool mousein;
protected:
#ifdef Q_OS_WIN
    void mousePressEvent( QMouseEvent*){
        timer->stop();
        hide();
        emit Clicked();

    }
#else
    void mouseReleaseEvent( QMouseEvent*){
        hide();
        emit Clicked();
    }
#endif
};
#endif // DICTLOGO_H
