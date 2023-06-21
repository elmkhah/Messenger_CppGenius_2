#include "myfile.h"
#include<QFile>
#include<QDir>

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
