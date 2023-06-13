#include "request.h"
#include<QCoreApplication>


Request::Request()
{
    baseUrl="http://api.barafardayebehtar.ml:8080/";
}

int Request::login(User &_user)
{
    QString url;
    url+=baseUrl+"login?username="+_user.getUsername()+"&password="+_user.getPassword();

// ******directory set******
    QDir dir(QDir::currentPath());
    dir.mkdir("information");
    dir.mkdir("privateChats");
    dir.mkdir("groupChats");
    dir.mkdir("channelChats");
    QDir privateChatsDir(QDir::currentPath()+"/privateChats/");
    privateChatsDir.mkdir("chats");
    QDir groupChatsDir(QDir::currentPath()+"/groupChats/");
    groupChatsDir.mkdir("chats");
    QDir channelChatsDir(QDir::currentPath()+"/channelChats/");
    channelChatsDir.mkdir("chats");


    QString infoPath(QDir::currentPath()+"/information/");
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QNetworkReply *reply = manager->get(request);
    while (!reply->isFinished()) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    QByteArray data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QString result=jsonObj.value("code").toString();
    if(result=="200"){
        QString _token=jsonObj.value("token").toString();
        _user.setToken(_token);

        QFile tokenFile(infoPath+"token.txt");
        if (tokenFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&tokenFile);
            out<<_token;}
        tokenFile.close();

        QFile isLoginFile(infoPath+"isLogin.txt");
        if (isLoginFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&isLoginFile);
            out<<"1";}

        isLoginFile.close();
        return 200;
        }
    return 0;
}

int Request::signup(User& _user){
    QString url;
    url+=baseUrl+"signup?username="+_user.getUsername()+"&password="+_user.getPassword();

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QNetworkReply *reply = manager->get(request);
    while (!reply->isFinished()) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    QByteArray data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QString result=jsonObj.value("code").toString();
    if(result=="200"){
        return 200;
    }
    return 0;
}

int Request::logout(User & _user)
{
    QString url;
    url+=baseUrl+"logout?username="+_user.getUsername()+"&password="+_user.getPassword();
    QString infoPath(QDir::currentPath()+"/information/");

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QNetworkReply *reply = manager->get(request);
    while (!reply->isFinished()) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    QByteArray data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QString result=jsonObj.value("code").toString();
    if(result=="200"){

        QFile isLoginFile(infoPath+"isLogin.txt");
        if (isLoginFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&isLoginFile);
            out<<"0";}
        QDir gDir(QDir::currentPath()+"/groupChats");
        gDir.removeRecursively();
        QDir cDir(QDir::currentPath()+"/channelChats");
        cDir.removeRecursively();
        QDir pDir(QDir::currentPath()+"/privateChats");
        pDir.removeRecursively();

        isLoginFile.close();
        return 200;
    }
    return 0;
}

int Request::createGroup(QString _name,QString _title){
    QString url;
    QString _token;

    //       ***add token***
    QFile tokenFile(QDir::currentPath()+"/information/token.txt");
    if (tokenFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&tokenFile);
        in>>_token;}
    tokenFile.close();

    //***url***
    url+=baseUrl+"creategroup?token="+_token+"&group_name="+_name+"&group_title="+_title;


    QString groupPath(QDir::currentPath()+"/groupChats/");
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QNetworkReply *reply = manager->get(request);
    while (!reply->isFinished()) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    QByteArray data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    QString result=jsonObj.value("code").toString();
    if(result=="200"){

        //***add group to files***
        QFile groupListFile(groupPath+"list.txt");
        if (groupListFile.open(QIODevice::Append | QIODevice::Text)){
            QTextStream out(&groupListFile);
            out<<_name<<"\n"<<_title<<"\n";}
        groupListFile.close();
        QFile groupMessageFile(groupPath+"/chats/"+_name+".txt");
        if (groupMessageFile.open(QIODevice::Append | QIODevice::Text)){
            groupMessageFile.close();}
        return 200;
    }
    return 0;
}

