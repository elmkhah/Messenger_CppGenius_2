#ifndef MYFILE_H
#define MYFILE_H
#include<QString>
#include<QFile>
#include<QDir>
#include<QTextStream>
#include <QJsonObject>
#include <QJsonValue>
#include"message.h"
#include<QVector>
class MyFile
{
public:
    MyFile()=default;
    QString getToken();
    void makeDirectory();
    void addUsernamePassword(QString,QString);
    QVector<QString> readUsernamePassword();
    void loginFile(const User&);
    void logoutFile();
    void createChat(QString,QString);
    void writeNumberOfMessage(int,QString,QString);
    void writeMessages(QString,QString,Message);
    void writeMessages(QString,QString,int);
    void writeMessages(int,QString,QString,QJsonObject);
    void writeMessages(int,QString,QJsonObject);
    int readNumberOfMessage(QString,QString);
    bool existChats(QString,QString);
    void writeNumberOfChats(int,QString);
    int readNumberOfChats(QString);
    void addNameTitel(QString,QString,QString);

};

#endif // MYFILE_H
