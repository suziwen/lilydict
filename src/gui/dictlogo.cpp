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
#include "dictlogo.h"


Dictlogo::Dictlogo(QWidget *parent) :
    QLabel(parent)
{
#ifdef Q_OS_WIN
    setWindowFlags(Qt::Popup);
#else
    setWindowFlags(Qt::FramelessWindowHint|Qt::ToolTip);
#endif
    setGeometry(0,0,32,32);
    setPixmap(QPixmap(":/img/app1.ico").scaled(QSize(32,32), Qt::IgnoreAspectRatio));
    timer=new QTimer();
    connect(timer,SIGNAL(timeout()), this, SLOT(autohide()));
}
void Dictlogo::popup(){
    timer->stop();
    if(this->isHidden()){
        //setWindowOpacity(qreal(0.9));
        move(QCursor::pos()-QPoint(36,46));
        show();
    }
    timercount=0.9;
    timer->start(200);
}
void Dictlogo::autohide(){
    if(!this->rect().contains(this->mapFromGlobal(QCursor::pos()))){
        mousein=false;
        if(timercount<0){
            timer->stop();
            this->hide();
            return;
        }
        this->setWindowOpacity(timercount);
        timercount-=0.1;

    }else{
        if(!mousein){
            mousein=true;
            timercount=0.9;
            this->setWindowOpacity(qreal(0.9));
        }
    }
}
