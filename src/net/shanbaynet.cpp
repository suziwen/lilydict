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
#include "shanbaynet.h"
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <src/app/application.h>
const QByteArray user_agent="Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36";
ShanbayNet::ShanbayNet(QObject *parent) :
    QObject(parent)
{
    http=new QNetworkAccessManager(this);
    http->setCookieJar(new QNetworkCookieJar(this));
    QObject::connect(http,SIGNAL(finished(QNetworkReply*)),this,SLOT(httpfinished(QNetworkReply*)));
}
ShanbayNet::~ShanbayNet(){
    // delete http;
}
//初始化就是获取session，以及是否需要验证码等信息，为下一步的登录初始化网络连接
void ShanbayNet::connect(){
    this->state = NetState::connect;
    getSessionid();
}

void ShanbayNet::getSessionid(){
    QNetworkRequest request;
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setUrl(QUrl("http://www.shanbay.com/web/account/login"));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("User-Agent",user_agent);
    httpAction=HttpAction::GetSessionidAction;
    http->get(request);
}
void ShanbayNet::refreshCaptchaImg(){
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.shanbay.com/api/v1/account/captcha/"));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("Referer","http://www.shanbay.com/accounts/login/");
    request.setRawHeader("User-Agent",user_agent);
    httpAction=HttpAction::RefreshCaptchaImg;
    http->get(request);
}

void ShanbayNet::queryWord(const QString &word){
    QNetworkRequest request;
    queryword=word;
    //request.setUrl(QUrl("http://www.shanbay.com/api/word/"+word));
    request.setUrl(QUrl("http://www.shanbay.com/api/v1/bdc/search/?word="+word));
    request.setRawHeader("Accept","application/json, text/javascript, */*; q=0.01");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("User-Agent",user_agent);
    httpAction=HttpAction::QueryWordAction;
    //qDebug()<<"Query "+word;
    http->get(request);
}
void ShanbayNet::queryExamples(QString learningid){
    if(learningid=="0"){
        return;
    }
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.shanbay.com/api/learning/examples/"+learningid));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7");
    httpAction=HttpAction::QueryWordExamplesAction;
    http->get(request);
}

void ShanbayNet::addWord(const QString &type,const QString& id){
    //type==add id is object_id 否则 id is learning_id标示我忘了
    QNetworkRequest request;
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    //request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7");
    QByteArray postData;
    httpAction=HttpAction::AddWordAction;
    if(type=="add"){
        postData.append(QString("{\"id\":%1,\"content_type\":\"vocabulary\"}").arg(id));
        request.setHeader(QNetworkRequest::ContentLengthHeader,postData.size());
        request.setUrl(QUrl("http://www.shanbay.com/api/v1/bdc/learning/"));
        http->post(request,postData);
    }else{
        postData.append("{\"retention\":1}");
        request.setHeader(QNetworkRequest::ContentLengthHeader,postData.size());
        request.setUrl(QUrl("http://www.shanbay.com/api/v1/bdc/learning/"+id));
        http->put(request,postData);
    }

    //    request.setUrl(QUrl("http://www.shanbay.com/api/learning/add/"+word));
    //    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    //    //request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //    request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    //    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    //    request.setRawHeader("Cache-Control","max-age=0");
    //    request.setRawHeader("Connection","keep-alive");
    //    request.setRawHeader("Host","www.shanbay.com");
    //    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7");
    //    httpAction=HttpAction::AddWordAction;
    //    http->get(request);

}
void ShanbayNet::addExample(QString learning_id,QString sentence, QString translation){
    if(learning_id.isNull()||learning_id=="0"){
        emit signalAddExampleFinished("单词没有在你的单词库中，现在不能为该单词添加例句");
        return;
    }
    if(sentence.trimmed().isEmpty()||translation.trimmed().isEmpty()){
        emit signalAddExampleFinished("例句或翻译不能为空");
        return;
    }
    QNetworkRequest request;
    request.setUrl(QUrl(QString("http://www.shanbay.com/api/example/add/%1?sentence=%2&translation=%3")
                        .arg(learning_id)
                        .arg(sentence)
                        .arg(translation)));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7");
    httpAction=HttpAction::AddExampleAction;
    http->get(request);
}

void ShanbayNet::login(const QString &u,const QString &p,const QString &c){
    username=u;
    password=p;
    captcha.code=c;
    loginShanbay();
    //getSessionid();
}
void ShanbayNet::loginShanbay(){
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.shanbay.com/api/v1/account/login/web/"));
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Charset","GBK,utf-8;q=0.7,*;q=0.3");
    //request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    request.setRawHeader("Cache-Control","max-age=0");
    request.setRawHeader("Connection","keep-alive");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7");
    request.setRawHeader("Origin","http//www.shanbay.com");
    request.setRawHeader("Referer","http://www.shanbay.com/web/account/login");
    request.setRawHeader("Host","www.shanbay.com");
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    request.setRawHeader("X-CSRFToken","null");

    QByteArray postData;
    //postData.append(QString("csrfmiddlewaretoken=%1&").arg(sessionid));
    postData.append(QString("username=%1&password=%2&").arg(QUrl::toPercentEncoding(username).constData()).arg(password));
    if(captcha.isneed()){
        postData.append(QString("key=%1&code=%2").arg(captcha.id).arg(captcha.code));
    }
    //qDebug()<<QString("username=%1&password=%2&").arg(QUrl::toPercentEncoding(username).constData()).arg(password);
    //postData.append("login=登录&continue=home&u=1&next=");
    qDebug()<<"post data:"<<postData;
    request.setHeader(QNetworkRequest::ContentLengthHeader,postData.size());
    httpAction=HttpAction::LoginAction;
    http->put(request,postData);
}
void ShanbayNet::Captcha::parseHtml(const QString& html){
    clear();
    int pos=html.indexOf("captcha_0");
    if(pos>0){
        int pos1=html.indexOf("value=",pos)+7;
        int pos2=html.indexOf("\"",pos1);
        id=html.mid(pos1,pos2-pos1);
        url=QString("http://www.shanbay.com/captcha/image/%1/").arg(id);
    }
}

void ShanbayNet::httpfinished(QNetworkReply* reply){
    if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString().isEmpty()){
        qDebug()<<QString::fromUtf8(reply->readAll());
    }
    //qDebug()<<QString::fromUtf8(reply->readAll());
    qDebug()<<"Http request finished!"<<reply->error()<<reply->errorString()<<reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString()<<reply->url();
    QJsonDocument jsonDoc;
    QJsonObject jsonObj,vocObj,en_definitionsObj;
    QString html;
    QByteArray replData=reply->readAll();
    sessionid=getCookie("csrftoken");
    switch(httpAction){
    case HttpAction::NoAction:
        break;
    case HttpAction::GetSessionidAction:
        sessionid=getCookie("csrftoken");
        //qDebug()<<"sessionid="<<sessionid<<replData;
        if(sessionidOk()){
            this->state = NetState::login;
            html=QString::fromUtf8(replData);
            //qDebug()<<html;
            captcha.parseHtml(html);
            if(captcha.isneed()){
                emit signalShowCaptcha();
            }
        }
        emit signalConnectFinished();
        break;
    case HttpAction::RefreshCaptchaImg:
        html=QString::fromUtf8(replData);
        //qDebug()<<html;
        //captcha.parseHtml(html);
        jsonDoc=QJsonDocument::fromJson(replData);
        if(!jsonDoc.isNull()){
            jsonObj=jsonDoc.object();
            jsonObj=jsonObj.value("data").toObject();
            captcha.id = jsonObj.value("key").toString();
            captcha.url = jsonObj.value("image_url").toString();
            emit signalShowCaptcha();
        }
        break;
    case HttpAction::LoginAction:
        httpAction=HttpAction::NoAction;
        html=QString::fromUtf8(replData);
        qDebug()<<html;
        jsonDoc=QJsonDocument::fromJson(replData);
        if(jsonDoc.isNull()){
            nickname=QUrl::fromPercentEncoding(getCookie("username").toLatin1());
            qDebug()<<"Login OK!nickname="<<nickname;
            state=NetState::ok;
            emit signalLoginFinished(true,"登录成功");
        }else{
            jsonObj = jsonDoc.object();
            if(jsonObj.value("status_code").toInt()==0){
                emit signalLoginFinished(true,"登录成功");
            }else{
                refreshCaptchaImg();
            }

            //            qDebug()<<"Login failed!";
            //            //qDebug()<<html<<"验证码错误 pos:"<<html.indexOf("验证码错误");
            //            captcha.parseHtml(html);
            //            if(captcha.isneed()){
            //                emit signalShowCaptcha();
            //            }
            //            if(html.indexOf("请输入正确的用户名或注册邮箱和密码")>-1){
            //                emit signalLoginFinished(false,"请输入正确的用户名或注册邮箱和密码");
            //            }else{
            //                emit signalLoginFinished(false,"验证码错误");
            //            }
        }
        break;
    case HttpAction::QueryWordAction:
        //qDebug()<<"query word";
        //jsondata=jsonParser->parse(reply->readAll(),&jsonok);
        //jsonDoc=QJsonDocument::fromJson(replData);
        emit signalRetWordinfo(QString::fromUtf8(replData));
        //        if(!jsonDoc.isNull()){
        //            // jsonObj=jsondata.toMap();
        //            jsonObj=jsonDoc.object();
        //            vocObj=jsonObj.value("voc").toObject();
        //            en_definitionsObj=vocObj.value("en_definitions").toObject();
        //            DICT::word->clear();
        //            DICT::word->name=vocObj.value("content").toString();
        //            DICT::word->learning_id=QString::number(jsonObj.value("learning_id").toDouble(),'g',15);
        //            DICT::word->definition=vocObj.value("definition").toString();
        //            DICT::word->pron=vocObj.value("pron").toString();
        //            DICT::word->audio=vocObj.value("audio").toString();
        //            //DICT::word->en_definitions="<br>";
        //            for(auto it=en_definitionsObj.constBegin();it!=en_definitionsObj.constEnd();it++){
        //                //qDebug()<<it.key()<<it.value();
        //                DICT::word->en_definitions+=QString("<br><font color='black'><b>%1. </b></font>").arg(it.key());
        //                if(it.value().isArray()){
        //                    foreach(QJsonValue jv,it.value().toArray()){
        //                        DICT::word->en_definitions+=QString("%1; ").arg(jv.toString());
        //                    }
        //                }
        //                DICT::word->en_definitions+="<br>";

        //            }
        //                        qDebug()<<QString("wordname=%1,learning_id=%2,definition=%3,pron=[%4],audio=%5,en_definition=%6")
        //                                  .arg(DICT::word->name)
        //                                  .arg(DICT::word->learning_id)
        //                                  .arg(DICT::word->definition)
        //                                  .arg(DICT::word->pron)
        //                                  .arg(DICT::word->audio)
        //                                  .arg(DICT::word->en_definitions);
        //            emit signalQueryFinished();
        //            //qDebug()<<DICT::word->learning_id;
        //            if(DICT::word->learning_id!="0"){
        //                queryExamples(DICT::word->learning_id);
        //            }

        //            //qDebug()<<jsonObj.value("voc").toMap().value("definition").toString();
        //            //qDebug()<<jsondata;
        //        }
        break;
    case HttpAction::AddExampleAction:
        //qDebug()<<QString::fromUtf8(reply->readAll());
        // jsondata=jsonParser->parse(reply->readAll(),&jsonok);
        jsonDoc=QJsonDocument::fromJson(replData);
        if(!jsonDoc.isNull()){
            jsonObj=jsonDoc.object();
            //qDebug()<<"example_status"<<jsonObj.value("example_status").toString();
            double examplestatus=jsonObj.value("example_status").toDouble();
            if(examplestatus==1){
                emit signalAddExampleFinished("例句添加成功");
            }else if(examplestatus==0){
                emit signalAddExampleFinished("例句添加失败，例句或翻译不能为空");

            }else if(examplestatus==100){
                emit signalAddExampleFinished("例句添加失败，例句未包含指定原词，或者它的有效变体");

            }else if(examplestatus==300){
                emit signalAddExampleFinished("例句添加失败，例句及其译文总长超过300个字符");
            }else{
                emit signalAddExampleFinished("例句添加失败，指定词汇学习记录实例不存在，或者用户无权查看其内容");
            }
        }else{
            emit signalAddExampleFinished("例句添加失败");
        }
        break;
    case HttpAction::QueryWordExamplesAction:
        qDebug()<<"query word examples";
        jsonDoc=QJsonDocument::fromJson(replData);
        if(!jsonDoc.isNull()){
            jsonObj=jsonDoc.object();
            if(jsonObj.value("examples_status").toDouble()==1){
                foreach(QJsonValue jv,jsonObj.value("examples").toArray()){
                    //DICT::word->examples.append(jv.toObject());
                }

                //                auto exmList=jsonObj.value("examples").toList();
                //                for(int i=0;i<exmList.size();i++){
                //                    exmObj=exmList.at(i);
                //                    DICT::word->examples.append(exmObj);
                //                    qDebug()<<exmObj.value("first").toString()+exmObj.value("mid").toString()+exmObj.value("last").toString();
                //                    qDebug()<<exmObj.value("translation").toString();
                //                }
                emit signalQueryExampleFinished();
            }

        }
        break;
    case HttpAction::AddWordAction:
        emit signalAddwordFinished(QString::fromUtf8(replData));
        //qDebug()<<"add word_____________"<<QString::fromUtf8(reply->readAll());


        //        jsonDoc=QJsonDocument::fromJson(replData);
        //        if(!jsonDoc.isNull()){
        //            jsonObj=jsonDoc.object();
        //            //qDebug()<<"jsonObj"<<jsonObj;
        //            DICT::word->learning_id=QString::number(jsonObj.value("id").toDouble(),'g',15);
        //            qDebug()<<jsonObj.value("id").toDouble()<<"add word result learning id="<<DICT::word->learning_id<< (DICT::word->learning_id!="0");
        //            emit signalAddwordFinished(DICT::word->learning_id!="0");
        //            queryExamples(DICT::word->learning_id);
        //        }
        //qDebug()<<QString::fromUtf8(reply->readAll());
        break;
    default:
        //        qDebug()<<reply->rawHeader("Content-Encoding");//gzip
        //        qDebug()<<QString::fromUtf8(reply->readAll());
        break;

    }

}
QString ShanbayNet::getCookie(const QString &name){
    qDebug()<<"get cookie";
    foreach(QNetworkCookie cookie , http->cookieJar()->cookiesForUrl(QUrl("http://www.shanbay.com"))){
        qDebug()<<cookie.name();

        if(cookie.name()==name){
            return cookie.value();
        }
    }
    return "RXzZWH51azvrCOFXkFnuJeSZO1B2cOB0";
}
