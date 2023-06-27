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
    int createChat(QString,QString,QString,QString);
    int joinChat(QString,QString,QString);
    int getChatList(QString,QString);
    int sendMessageChat(QString,QString,Message);
    int getChatMessages(QString,QString,QString,Date _date=Date());
};

#endif // REQUEST_H
