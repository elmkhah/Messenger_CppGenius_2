#ifndef MYFILE_H
#define MYFILE_H
#include<QString>
#include<QFile>
#include<QDir>
#include<QTextStream>
#include <QJsonObject>
#include <QJsonValue>
#include"message.h"
class MyFile
{
public:
    MyFile()=default;
    QString getToken();
    void makeDirectory();
    void loginFile(QString);
    void logoutFile();
    void createChat();
    void writeNumberOfMessage(int,QString,QString);
    void writeMessages(QString,QString,Message);
    void writeMessages(int,QString,QString,QJsonObject);
    int readNumberOfMessage(QString,QString);
};

#endif // MYFILE_H
