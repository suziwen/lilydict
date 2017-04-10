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
#include "config.h"
#include <QApplication>
Config::Config(QObject *parent) :QObject(parent)
{
    settings_=new QSettings("shanbay.ini",QSettings::IniFormat);
    load();
}
Config::~Config(){
    save();
    settings_->deleteLater();
}
void Config::setValue(const QString &key, const QVariant &value) {
    emit signalChange(key,value);
    settings_->setValue(key, value);
}

QVariant Config::value(const QString &key, const QVariant &defaultValue) const {
    return settings_->value(key, defaultValue);
}
void Config::load(){
    username=settings_->value("username","").toString();
    userpass=settings_->value("userpass","").toString();
    savepass=settings_->value("savepass",false).toBool();
    autologin=settings_->value("autologin",false).toBool();
    autospeak=settings_->value("autospeak",true).toBool();
    getscreentext=settings_->value("getscreentext",true).toBool();
#ifdef Q_OS_WIN
    getclipboardtext=settings_->value("getclipboardtext",true).toBool();
    getselectedtext=settings_->value("getselectedtext",false).toBool();
#else
    getclipboardtext=settings_->value("getclipboardtext",false).toBool();
    getselectedtext=settings_->value("getselectedtext",true).toBool();
#endif
    showquerylogo=settings_->value("showquerylogo",true).toBool();
    autorun=settings_->value("autorun",false).toBool();

    autohide=settings_->value("autohide",false).toBool();
    startloginshanbay=settings_->value("startloginshanbay",false).toBool();
    autoaddword=settings_->value("autoaddword",false).toBool();

    x = settings_->value("x",0).toInt();
    y = settings_->value("y",0).toInt();
    width = settings_->value("width",800).toInt();
    height = settings_->value("height",390).toInt();
}
void Config::save(){
    settings_->setValue("username",username);
    settings_->setValue("userpass",userpass);
    settings_->setValue("savepass",savepass);
    settings_->setValue("autologin",autologin);
    settings_->setValue("autospeak",autospeak);
    settings_->setValue("getscreentext",getscreentext);
    settings_->setValue("getclipboardtext",getclipboardtext);
    settings_->setValue("getselectedtext",getselectedtext);
    settings_->setValue("showquerylogo",showquerylogo);
    settings_->setValue("autorun",autorun);
    settings_->setValue("autohide",autohide);
    settings_->setValue("startloginshanbay",startloginshanbay);
    settings_->setValue("autoaddword",autoaddword);
    settings_->setValue("x",x);
    settings_->setValue("y",y);
    settings_->setValue("width",width);
    settings_->setValue("height",height);
    settings_->sync();
}
QString Config::getUsername(){
    return username;
}
void Config::setUsername(QString name){    
    username=name;
}

QString Config::getUserpass(){
    return userpass;
}
void Config::setUserpass(QString text){
    userpass=text;
}

bool Config::isSavepass(){
    return savepass;
}
void Config::setSavepass(bool value){
    savepass=value;
    emit signalChange("savepass",value);
    if(!savepass) userpass="";
}

bool Config::isAutologin(){
    return autologin;
}
void Config::setAutologin(bool value){
    autologin=value;
    emit signalChange("autologin",value);
}

bool Config::isAutohide(){
    return autohide;
}
void Config::setAutohide(bool value){
    autohide=value;
    emit signalChange("autohide",value);
}

bool Config::isStartloginshanbay(){
    return startloginshanbay;
}
void Config::setStartloginshanbay(bool value){
    startloginshanbay=value;
    emit signalChange("startloginshanbay",value);
}
bool Config::isAutospeak(){
    return autospeak;
}
void Config::setAutospeak(bool value){
    autospeak=value;
    emit signalChange("autospeak",value);
}

bool Config::isAutorun(){
    return autorun;
}
void Config::setAutorun(bool value){
    autorun=value;
    emit signalChange("autorun",value);
}

bool Config::isGetclipboardtext(){
    return getclipboardtext;
}
void Config::setClipboardtext(bool value){
    getclipboardtext=value;
    emit signalChange("clipboardtext",value);
}
bool Config::isGetselectedtext(){
    return getselectedtext;
}
void Config::setSelectedtext(bool value){
    getselectedtext=value;
    emit signalChange("selectedtext",value);
}

bool Config::isGetscreentext(){
    return getscreentext;
}
void Config::setScreentext(bool value){
    getscreentext=value;
    emit signalChange("screentext",value);
}

bool Config::isShowquerylogo(){
    return showquerylogo;
}
void Config::setShowquerylogo(bool value){
    showquerylogo=value;
    emit signalChange("showquerylogo",value);
}
bool Config::isAutoaddword(){
    return autoaddword;
}
void Config::setAutoaddword(bool value){
    autoaddword=value;
    emit signalChange("autoaddword",value);
}
bool Config::isLoginshanbay(){
    return loginshanbay;
}
void Config::setLoginshanbay(bool value){
    loginshanbay=value;
    emit signalChange("loginshanbay",value);
}

int Config::getX(){
    return x;
}
void Config::setX(int value){
    x=value;
    emit signalChange("x",value);
}

int Config::getY(){
    return y;
}
void Config::setY(int value){
    y=value;
    emit signalChange("y",value);
}

int Config::getWidth(){
    return width;
}
void Config::setWidth(int value){
    width=value;
    emit signalChange("width",value);
}

int Config::getHeight(){
    return height;
}
void Config::setHeight(int value){
    height=value;
    emit signalChange("height",value);
}
