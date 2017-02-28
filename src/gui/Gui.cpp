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
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDesktopServices>
#include <dict/dict.h>
#include "Gui.h"
Gui::Gui(QObject *parent) : QObject(parent)
{

}
void Gui::init(){

    engine = new QQmlApplicationEngine();
    QQmlContext *context = engine->rootContext();
    context->setContextProperty("cfg", DICT::cfg.get());

    engine->load(QUrl(QStringLiteral("qrc:/src/gui/Login.qml")));
    loginWin = qobject_cast<QWindow*>(engine->rootObjects().at(0));
    loginWin->setIcon(QIcon(":/img/logo.png"));

    //loginWin->setFlags(Qt::FramelessWindowHint);
    //qDebug()<<engine.rootObjects().size()<<loginWin->objectName();
    QObject::connect(loginWin,SIGNAL(signalRegisterClick()),
                     this,SLOT(registerClick()));

    QObject::connect(loginWin, SIGNAL(signalLoginClick(QString,QString,QString)),
                     this, SIGNAL(signalLoginClick(QString,QString,QString)));
    QObject::connect(loginWin,SIGNAL(signalFreshCaptchaImg()),
                     this,SIGNAL(signalFreshCaptchaImg()));

    QObject::connect(this,SIGNAL(signalShowCaptchaImg(QVariant)),
                     loginWin,SLOT(showCaptchaImg(QVariant)));
    QObject::connect(this,SIGNAL(signalSetLoginWinState(QVariant)),
                     loginWin,SLOT(setState(QVariant)));

    engine->load(QUrl(QStringLiteral("qrc:/src/gui/main.qml")));
    mainWin = qobject_cast<QWindow*>(engine->rootObjects().at(1));
    mainWin->setIcon(QIcon(":/img/logo.png"));
#ifdef Q_OS_WIN
    mainWin->setFlags(Qt::Dialog);
#else
    mainWin->setFlags(Qt::WindowStaysOnTopHint);
#endif
    QObject::connect(mainWin,SIGNAL(signalBtnqueryClick(QString)),
                     this,SIGNAL(signalBtnqueryClick(QString)));
    QObject::connect(this,SIGNAL(signalShowWord(QVariant)),
                     mainWin,SLOT(showWord(QVariant)));

    QObject::connect(mainWin,SIGNAL(signalBtnaddwordClick(QString,QString)),
                     this,SIGNAL(signalBtnaddwordClick(QString,QString)));
    QObject::connect(this,SIGNAL(signalAddwordRetMain(QVariant)),
                     mainWin,SLOT(addWordRet(QVariant)));



    engine->load(QUrl(QStringLiteral("qrc:/src/gui/Balloon.qml")));
    balloonWin = qobject_cast<QWindow*>(engine->rootObjects().at(2));
    QObject::connect(this,SIGNAL(signalShowWordInBalloon(QVariant)),
                     balloonWin,SLOT(showWord(QVariant)));
    QObject::connect(balloonWin,SIGNAL(signalBtnaddwordClick(QString,QString)),
                     this,SIGNAL(signalBtnaddwordClick(QString,QString)));
    QObject::connect(this,SIGNAL(signalAddwordRetBalloon(QVariant)),
                     balloonWin,SLOT(addWordRet(QVariant)));

    engine->load(QUrl(QStringLiteral("qrc:/src/gui/Setup.qml")));
    setupWin = qobject_cast<QWindow*>(engine->rootObjects().at(3));
    setupWin->setIcon(QIcon(":/img/logo.png"));
#ifdef Q_OS_WIN
    setupWin->setFlags(Qt::Dialog);
#else
    setupWin->setFlags(Qt::WindowStaysOnTopHint);
#endif

    engine->load(QUrl(QStringLiteral("qrc:/src/gui/About.qml")));
    aboutWin = qobject_cast<QWindow*>(engine->rootObjects().at(4));
    aboutWin->setIcon(QIcon(":/img/logo.png"));
}
//loginWin
void Gui::showCaptchaImg(const QString &url){
    emit signalShowCaptchaImg(url);
}
void Gui::setLoginWinState(const QString &str){
    emit signalSetLoginWinState(str);
}
//mainWin
void Gui::showMainWin(){
    //mainWin->hide();
    mainWin->showNormal();
}
void Gui::hideMainWin(){
    mainWin->hide();
}
bool Gui::mainWinIsVisible(){
    return mainWin->isVisible();
}

void Gui::showWord(const QString &wordinfo){
    emit signalShowWord(wordinfo);
}
void Gui::addWordRet(const QString &data){
    if(DICT::showType == ShowType::main){
        emit signalAddwordRetMain(data);
    }else if(DICT::showType ==ShowType::balloon){
        qDebug()<<"balloon add word ret";
        emit signalAddwordRetBalloon(data);
    }

}

void Gui::showWordInBalloon(const QString &wordinfo){
    balloonWin->setPosition(QCursor::pos()+QPoint(10,15));
    balloonWin->show();
    emit signalShowWordInBalloon(wordinfo);
}
void Gui::registerClick(){
    QDesktopServices::openUrl(QUrl("http://www.shanbay.com/referral/ref/9e54b69ab8/"));
}

void Gui::showSetupWin(){
    setupWin->show();
}

void Gui::showAboutWin(){
    aboutWin->show();
}
