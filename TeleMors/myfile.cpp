#include "myfile.h"


QString MyFile::getToken()
{
    QString token;
    //       ***add token***
    QFile tokenFile(QDir::currentPath()+"/information/token.txt");
    if (tokenFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&tokenFile);
        in>>token;}
    tokenFile.close();
    return token;
}

void MyFile::makeDirectory()
{
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

}

void MyFile::loginFile(QString _token)
{
    QString infoPath(QDir::currentPath()+"/information/");

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

}

void MyFile::logoutFile()
{
    QString infoPath(QDir::currentPath()+"/information/");
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
}

