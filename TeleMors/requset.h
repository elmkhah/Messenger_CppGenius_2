#ifndef REQUSET_H
#define REQUSET_H
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
class Requset

{
public:
    QString baseUrl;
    Requset();
    int login(User&);
};

#endif // REQUSET_H
