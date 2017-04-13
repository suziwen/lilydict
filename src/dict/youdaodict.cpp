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
#include "youdaodict.h"
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

YoudaoDict::YoudaoDict(QObject *parent) :
    QObject(parent)
{}
void YoudaoDict::connect(){
    http=new QNetworkAccessManager(this);
    QObject::connect(http,SIGNAL(finished(QNetworkReply*)),this,SLOT(httpfinished(QNetworkReply*)));
}
void YoudaoDict::queryWord(const QString &word){
    QNetworkRequest request;
    //QString urlstr=QString("http://fanyi.youdao.com/openapi.do?keyfrom=qtcnorg&key=624498262&type=data&doctype=json&version=1.1&q=%1").arg(word);
    QString urlstr=QString("http://dict.youdao.com/w/%1").arg(word);
    request.setUrl(QUrl(urlstr));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7");
    http->get(request);
}
QString wordinfo;
void YoudaoDict::httpfinished(QNetworkReply* reply){
    qDebug()<<"end youdao!!!!!";
    QByteArray replData=reply->readAll();

    int pos1=replData.indexOf("<div class=\"trans-container\">");
    if(pos1>0){
        int pos2=replData.indexOf("</div>",pos1)+6;
        wordinfo=replData.mid(pos1,pos2-pos1).replace("class=\"additional\"","style=\"color:gray\"");
    }else{
        wordinfo.clear();
    }

    //qDebug()<<reply->errorString()<<" wordinfo:"<<wordinfo;
    emit signalRetWordinfo(wordinfo);
//    QJsonDocument jsonDoc;
//    QJsonObject jsonObj,basicObj;
//    QJsonValue jsonValue;
//    jsonDoc=QJsonDocument::fromJson(reply->readAll());
//    if(!jsonDoc.isNull()){
//        jsonObj=jsonDoc.object();
//        //qDebug()<<jsonObj;
//        if(jsonObj.value("errorCode").toDouble()==0){
//            DICT::word->youdaoWord+=QString("<font color='blue'><b>%1. </b></font>  ").arg(jsonObj.value("query").toString());
//            DICT::word->youdaoWord+="<font color='black'><b>";
//            foreach(auto value,jsonObj.value("translation").toArray()){
//                DICT::word->youdaoWord+=value.toString();
//            }
//            jsonValue=jsonObj.value("basic");
//            if(!jsonValue.isUndefined()){
//                basicObj=jsonValue.toObject();
//                foreach(auto value,basicObj.value("explains").toArray()){
//                    DICT::word->youdaoWord+=value.toString();
//                }
//            }
//            DICT::word->youdaoWord+="</b></font><br>";
//            DICT::word->youdaoWord+="<font color='gray'>---------------------------------------------网络释义---------------------------------------------</font><br>";
//            foreach(auto value,jsonObj.value("web").toArray()){
//                QJsonObject o=value.toObject();
//                DICT::word->youdaoWord+=QString("<font color='blue'><b>%1. </b></font>  ").arg(o.value("key").toString());
//                foreach(auto v,o.value("value").toArray()){
//                    DICT::word->youdaoWord+=QString("<font color='black'><b>%1. </b></font> ").arg(v.toString());
//                }
//                DICT::word->youdaoWord+="<br>";
//            }

//        }else{
//            DICT::word->youdaoWord=tr("错误代码：%1").arg(jsonObj.value("errorCode").toDouble());
//        }
        //qDebug()<<DICT::word->youdaoWord;
//    }
//    emit signalQueryFinished();
}
