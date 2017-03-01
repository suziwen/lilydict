/****************************************************************************
**
** Copyright (C) 2013 Jeffrey Lee.
** All rights reserved.
** Contact: vipjeffreylee@gmail.com
**
** This file is part of the ShanbayDict.
**
** $BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
**
**
** $END_LICENSE$
**
****************************************************************************/
#ifndef CONFIG_H
#define CONFIG_H
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
#include <QSettings>
#include <QObject>
class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = 0);
    ~Config();

signals:
    void signalChange(const QString& key,const QVariant & value);

public slots:

private:
    QString username,userpass;
    bool loginshanbay=false,savepass, autologin, autospeak, autoaddword,autorun,autohide,
    startloginshanbay,
    getscreentext,
    getclipboardtext,
    getselectedtext,
    showquerylogo;
    QSettings *settings_;
    void load();
    void save();
public:
    //百合词典版本信息
    QString versioninformation=QObject::tr("百合词典1.0.0");
    //所有使用本软件全部或者部分代码的程序设计人员请保留lience信息，并在所发布的软件关于窗口中进行显示。
    QString licenceinformation=QObject::tr("<h2>%1</h2>"
                                         "百合词典依据<a href='http://www.shanbay.com'><b>扇贝网</b></a><a href='http://dict.youdao.com/'><b>有道词典</b></a>公开的API设计。<br>"
                                         "Copyright(C) 2016 Lieefu Way  All rights reserved.<br>"
                                         "<p>完全遵循LGPL v3协议,未经作者允许不得作为商业用途。<a href='http://git.oschina.net/lieefu/lilydict'><b>百合词典开源(码云)</b></a></p>"
                                         "<p><h3>软件作者:Lieefu Way<br>email:lieefu@gmail.com<br>新浪微博：<a href='http://weibo.com/207899158'>http://weibo.com/207899158</a><br>"
                                         "QQ:53336158 百合词典QQ群：130406877</h3</p>"
                                         "<p>本软件有多个平台的版本包含linux、mac和windows。</p>").arg(versioninformation);
    Q_INVOKABLE QVariant getVersion(){
        return versioninformation;
    }
    Q_INVOKABLE QVariant getLicenceInfo(){
        return licenceinformation;
    }

public:
    Q_INVOKABLE void setValue(const QString & key, const QVariant & value);
    Q_INVOKABLE QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;


    Q_INVOKABLE QString getUsername();
    Q_INVOKABLE void setUsername(QString name);

    Q_INVOKABLE QString getUserpass();
    Q_INVOKABLE void setUserpass(QString text);

    Q_INVOKABLE bool isSavepass();
    Q_INVOKABLE void setSavepass(bool value);

    Q_INVOKABLE bool isAutologin();
    Q_INVOKABLE void setAutologin(bool value);

    Q_INVOKABLE bool isAutospeak();
    Q_INVOKABLE void setAutospeak(bool value);

    Q_INVOKABLE bool isGetscreentext();
    Q_INVOKABLE void setScreentext(bool value);

    Q_INVOKABLE bool isGetclipboardtext();
    Q_INVOKABLE void setClipboardtext(bool value);

    Q_INVOKABLE bool isGetselectedtext();
    Q_INVOKABLE void setSelectedtext(bool value);

    Q_INVOKABLE bool isShowquerylogo();
    Q_INVOKABLE void setShowquerylogo(bool value);

    Q_INVOKABLE bool isAutorun();
    Q_INVOKABLE void setAutorun(bool value);

    Q_INVOKABLE bool isAutohide();
    Q_INVOKABLE void setAutohide(bool value);

    Q_INVOKABLE bool isStartloginshanbay();
    Q_INVOKABLE void setStartloginshanbay(bool value);

    Q_INVOKABLE bool isAutoaddword();
    Q_INVOKABLE void setAutoaddword(bool value);

    Q_INVOKABLE bool isLoginshanbay();
    Q_INVOKABLE void setLoginshanbay(bool value);
};

#endif // CONFIG_H
