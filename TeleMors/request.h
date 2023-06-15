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
#include "message.h"
#include<QObject>
#include<QFile>
#include<QTextStream>
#include<QDir>
class Request

{
private:
     QString baseUrl;
     QJsonObject sendRequest(QString);
     QString getToken();
public:

    Request();
    int login(User&);
    int signup(User&);
    int logout(User&);
    int createGroup(QString,QString,QString);
    int createChannel(QString,QString,QString);
    int joinGroup(QString,QString);
    int joinChannel(QString,QString);
    int getGroupList(QString);
    int getChannelList(QString);
    int getUserList(QString);
    int sendMessageUser(User&,Message);
    int sendMessageGroup(QString,Message);
    int sendMessageChannel(QString,Message);

};

#endif // REQUEST_H
