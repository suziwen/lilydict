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
    void queryWord(const QString &word);
    QNetworkAccessManager * http;
};

#endif // YOUDAONET_H
