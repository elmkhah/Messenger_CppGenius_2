#ifndef MYFILE_H
#define MYFILE_H
#include<QString>
#include<QFile>
#include<QDir>
#include<QTextStream>
class MyFile
{
public:
    MyFile()=default;
    QString getToken();
    void makeDirectory();
    void loginFile(QString);
    void logoutFile();
    void createChat();
};

#endif // MYFILE_H
