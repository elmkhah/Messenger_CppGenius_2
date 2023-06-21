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
};

#endif // MYFILE_H
