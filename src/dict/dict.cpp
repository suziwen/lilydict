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
#include <QVersionNumber>
#include <QTimer>
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "dict.h"
std::unique_ptr<Application> DICT::app = std::make_unique<Application>();
std::unique_ptr<Gui> DICT::gui = std::make_unique<Gui>();
std::unique_ptr<ShanbayDict> DICT::shanbayDict;// = std::make_unique<ShanbayDict>();
std::unique_ptr<YoudaoDict> DICT::youdaoDict;
std::unique_ptr<Config> DICT::cfg = std::make_unique<Config>();
Dictlogo* DICT::logo ;
ShowType DICT::showType;

void DICT::queryWord(const QString& word){
    DICT::shanbayDict->queryWord(word);
    DICT::youdaoDict->queryWord(word);
}

void DICT::showWord(DictType dictType,const QString &wordinfo){
    if(DICT::showType == ShowType::main){
        DICT::gui->showWord(dictType,wordinfo);
    }else{
        DICT::gui->showWordInBalloon(dictType,wordinfo);
    }
}

////////////////////////
void DICT::init(){    
    DICT::gui->init();
    QTimer::singleShot(1000, [](){
        qDebug()<<"延迟初始化，提高启动速度";
        DICT::logo = new Dictlogo();
        DICT::shanbayDict = std::make_unique<ShanbayDict>();
        DICT::shanbayDict->connect();

        DICT::youdaoDict = std::make_unique<YoudaoDict>();
        DICT::youdaoDict->connect();

        QObject::connect(DICT::shanbayDict.get(),&ShanbayDict::signalRetWordinfo,
                         [&](const QString& wordinfo){
            DICT::showWord(DictType::ShanbayDict,wordinfo);
        });

        QObject::connect(DICT::youdaoDict.get(),&YoudaoDict::signalRetWordinfo,
                         [&](const QString& wordinfo){
            DICT::showWord(DictType::YoudaoDict,wordinfo);
        });

        QObject::connect(DICT::logo,&Dictlogo::Clicked,
                         [&](){
            //qDebug()<<"logo clicked:"<<capture_text;
            DICT::queryWord(DICT::app->capture_text);
        });
        QObject::connect(DICT::shanbayDict.get(),&ShanbayDict::signalConnectFinished,[&](){
            if(DICT::shanbayDict->state!=ShanbayDict::NetState::login){
                DICT::gui->setLoginWinState("无法连接扇贝网，请稍后重试");
                return;
            }
            DICT::gui->setLoginWinState("已连接扇贝网，请输入用户名和密码登录!");
        });
        QObject::connect(DICT::shanbayDict.get(),&ShanbayDict::signalShowCaptcha,
                         [&](){
            //qDebug()<<DICT::ShanbayDict->captcha.id<<DICT::ShanbayDict->captcha.url;
            DICT::gui->showCaptchaImg(DICT::shanbayDict->captcha.url);

        });
        QObject::connect(DICT::gui.get(), &Gui::signalLoginClick,
                         [&](const QString username,QString password,QString captchacode){
            //qDebug()<<"loginClick:"<<username <<password<<captchacode;
            DICT::shanbayDict->login(username,password,captchacode);

        });
        QObject::connect(DICT::gui.get(),&Gui::signalFreshCaptchaImg,
                         [&](){
            //qDebug()<<"require fresh captcha img";
            DICT::shanbayDict->refreshCaptchaImg();
        });
        QObject::connect(DICT::shanbayDict.get(),&ShanbayDict::signalLoginFinished,
                         [&](bool ok,const QString& msg){
            if(ok){
                DICT::gui->loginWin->hide();
                if(!DICT::cfg->isAutohide()) DICT::gui->mainWin->show();
                DICT::cfg->setUsername(DICT::shanbayDict->username);
                if(DICT::cfg->isSavepass()) DICT::cfg->setUserpass(DICT::shanbayDict->password);
                DICT::app->loginshanbayAction->setChecked(true);
                DICT::cfg->setLoginshanbay(true);
                //setScreenText();
                //showSystrayIcon();
            }else{
                DICT::gui->setLoginWinState(msg);
            }
        });

        QObject::connect(DICT::gui.get(),&Gui::signalBtnqueryClick,
                         [&](const QString word){
            DICT::showType = ShowType::main;
            DICT::queryWord(word);
        });


        QObject::connect(DICT::gui.get(),&Gui::signalBtnaddwordClick,
                         [&](const QString type,const QString id){
            DICT::shanbayDict->addWord(type,id);
        });
        QObject::connect(DICT::shanbayDict.get(),&ShanbayDict::signalAddwordFinished,
                         [&](const QString&data){
            DICT::gui->addWordRet(data);
        });
        DICT::app->setScreenText();
        DICT::app->showSystrayIcon();
    });
    //获取版本信息，提示升级
    QTimer::singleShot(10000, [](){
        QNetworkAccessManager *manager = new QNetworkAccessManager(qApp);
        QObject::connect(manager, &QNetworkAccessManager::finished,
                         [](QNetworkReply* reply){
            auto replData=reply->readAll();
            auto jsonDoc=QJsonDocument::fromJson(replData);
            if(!jsonDoc.isNull()){
                auto jsonObj=jsonDoc.object();
                auto ok=jsonObj.value("ok").toBool();
                if(ok){
                    auto version=jsonObj.value("version").toString();
                    auto v1 = QVersionNumber::fromString(version);
                    auto v2 = QVersionNumber::fromString(DICT::cfg->version);
                    if(v1>v2){
                        auto url = jsonObj.value("url").toString();
                        auto message = jsonObj.value("message").toString();
                        qDebug()<<version<<url<<message<<v2<< (v1>v2);
                        DICT::gui->showUpgradeWin(message,url);
                    }

                }
            }
        });
        manager->get(QNetworkRequest(QUrl("http://www.lieefu.com/api/lilydict/version")));
    });
}
