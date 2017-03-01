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
#include <QMenu>
#include <QAction>
#include <QDesktopWidget>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QThread>
#include "app/application.h"
#include <dict/dict.h>
Application::Application(){
}

void Application::close(){
    closeSystrayIcon();
}
void Application::showSystrayIcon(){
    if(trayIcon!=nullptr) return;
    trayIcon = new QSystemTrayIcon(QIcon(":/img/app.ico"),qApp);

    dictMenu = new QMenu("菜单");
    //dictMenu->setLayoutDirection(Qt::LeftToRight);
    showMainWinAction = new QAction(QIcon(":/img/main.ico"),QObject::tr("显示主窗口"),qApp);
    //helpAction =new QAction(QIcon(":/img/help.png"),QObject::tr("帮助"),qApp);
    quitAction = new QAction(QIcon(":/img/quit.png"),QObject::tr("退出程序"), qApp);
#ifdef Q_OS_WIN
    getscreenwordAction=new QAction(QObject::tr("屏幕取词"),qApp);
    autospeakAction=new QAction(QObject::tr("自动发音"),qApp);
#else
    getscreenwordAction=new QAction(QIcon(":/img/word.ico"),QObject::tr("屏幕取词"),qApp);
    autospeakAction=new QAction(QIcon(":/img/speaker.png"),QObject::tr("自动发音"),qApp);
#endif
    cfgAction=new QAction(QIcon(":/img/setup.ico"),QObject::tr("软件设置"),qApp);
    loginshanbayAction=new QAction(QIcon(":/img/shanbay.ico"),QObject::tr("登录扇贝网"),qApp);
    aboutAction=new QAction(QIcon(":/img/about.png"),QObject::tr("关于"),qApp);

    loginshanbayAction->setCheckable(true);
    autospeakAction->setCheckable(true);
    autospeakAction->setChecked(DICT::cfg->isAutospeak());
    getscreenwordAction->setCheckable(true);
    getscreenwordAction->setChecked(DICT::cfg->isGetscreentext());

    dictMenu->addAction(showMainWinAction);
    //dictMenu->addAction(helpAction);
    dictMenu->addAction(getscreenwordAction);
    dictMenu->addAction(autospeakAction);
    dictMenu->addAction(loginshanbayAction);
    dictMenu->addSeparator();
    dictMenu->addAction(cfgAction);
    dictMenu->addAction(aboutAction);
    dictMenu->addSeparator();
    dictMenu->addAction(quitAction);

    trayIcon->setContextMenu(dictMenu);
    QObject::connect(showMainWinAction,&QAction::triggered,[&](){DICT::gui->showMainWin();});
    QObject::connect(autospeakAction,&QAction::toggled,
                     [&](bool checked){
        DICT::cfg->setAutospeak(checked);
        qDebug()<<"autospeak:"<<DICT::cfg->isAutospeak();
    });
    QObject::connect(getscreenwordAction,&QAction::toggled,
                     [&](bool checked){
        DICT::cfg->setScreentext(checked);
        qDebug()<<"getscreenwordAction:"<<checked;
        setScreenText();
    });
    QObject::connect(DICT::cfg.get(),&Config::signalChange,
                     [&](const QString& key, const QVariant& value){
        if(key=="screentext"){
            getscreenwordAction->setChecked(value.toBool());
        }else if(key=="autospeak"){
            autospeakAction->setChecked(value.toBool());
            setScreenText();
        }else if(key=="selectedtext"){
            setScreenText();
        }else if(key=="clipboardtext"){
            setScreenText();
        }
    });

    QObject::connect(aboutAction,&QAction::triggered,[&](){DICT::gui->showAboutWin();DICT::gui->hideMainWin();});
    QObject::connect(quitAction,&QAction::triggered,[&](){close();qApp->quit();});
    QObject::connect(cfgAction,&QAction::triggered,
                     [&](){
       DICT::gui->showSetupWin();
    });

    QObject::connect(loginshanbayAction,&QAction::triggered,[&](){
        //DICT::gui->setLoginWinState("正在连接扇贝网...");
        DICT::gui->mainWin->hide();
        DICT::gui->loginWin->show();
    });
    //Qt bug:Ubuntu 14.04 Qt 5.6 QSystemTrayIcon doesn't emit activated signal
    QObject::connect(trayIcon,&QSystemTrayIcon::activated,
                     [&](QSystemTrayIcon::ActivationReason reason) {
        switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            qDebug()<<"DoubleClick";
            if(DICT::gui->mainWinIsVisible()){
                DICT::gui->hideMainWin();
            }else{
                DICT::gui->showMainWin();
            }
            break;
        case QSystemTrayIcon::MiddleClick:
            qDebug()<<"MiddleClick";
            break;
        default:;
        }
    });
    trayIcon->setToolTip(QObject::tr("百合词典 %1").arg(DICT::cfg->getVersion().toString()));
    trayIcon->show();
}
void Application::closeSystrayIcon(){
    trayIcon->deleteLater();
    dictMenu->deleteLater();
}

void Application::run(){

    DICT::init();
    setScreenText();
    showSystrayIcon();
    if(DICT::cfg->isStartloginshanbay()){
        DICT::gui->loginWin->show();
    }else{
       if(!DICT::cfg->isAutohide()) DICT::gui->mainWin->show();
    }


}
void Application::captureText(QString text){
    capture_text = text.trimmed();
    if(capture_text.isEmpty()||capture_text.length()>20) return;
    DICT::showType = ShowType::balloon;
    if(DICT::cfg->isShowquerylogo()){
        DICT::logo->popup();
        return;
    }
    DICT::queryWord(capture_text);
}

void Application::setScreenText(){
    if(!DICT::cfg->isGetscreentext()){//关闭屏幕取词
        QObject::disconnect(qApp->clipboard(),0,0,0);
        return;
    }
    if(qApp->clipboard()->supportsSelection()){//windows and os_x not supportSection
        if(DICT::cfg->isGetselectedtext()){
            QObject::connect(qApp->clipboard(),&QClipboard::selectionChanged,
                             [&](){
                qDebug()<<"selectionChanged"<< qApp->clipboard()->mimeData(QClipboard::Selection)->hasText()<<qApp->clipboard()->text(QClipboard::Selection);
                qDebug()<< (qApp->mouseButtons() & Qt::LeftButton);
                captureText(qApp->clipboard()->text(QClipboard::Selection));

            });

        }else{
            QObject::disconnect(qApp->clipboard(),&QClipboard::selectionChanged,0,0);
        }
    }
    if(DICT::cfg->isGetclipboardtext())   {
        QObject::connect(qApp->clipboard(),&QClipboard::dataChanged,
                         [&](){
            qDebug()<<"dataChanged"<<qApp->clipboard()->mimeData(QClipboard::Clipboard)->hasText()<<qApp->clipboard()->text();

            captureText(qApp->clipboard()->text());
        });
    }else{
        QObject::disconnect(qApp->clipboard(),&QClipboard::dataChanged,0,0);
    }

}
