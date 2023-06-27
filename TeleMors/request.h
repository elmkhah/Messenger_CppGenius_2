#ifndef REQUEST_H
#define REQUEST_H
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include"user.h"
#include<QObject>
#include"myfile.h"
class Request

{
private:
     QString baseUrl;
     QJsonObject sendRequest(QString);

     int calculate(QString);
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
    int getUserChats(QString,QString,Date _date=Date());
    int getGroupChats(QString,QString,Date _date=Date());
    int getChannelChats(QString,QString,Date _date=Date());
};

#endif // REQUEST_H
