#ifndef REQUEST_H
#define REQUEST_H
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>
#include"user.h"
#include<QObject>
#include<QFile>
#include<QTextStream>
#include<QDir>
class Request

{
public:
    QString baseUrl;
    Request();
    int login(User&);
    int signup(User&);
    int logout(User&);
    int createGroup(QString,QString);
};

#endif // REQUEST_H
