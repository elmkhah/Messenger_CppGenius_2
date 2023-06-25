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

void MyFile::writeNumberOfMessage(int numberOfChats,QString type,QString _dst)
{
    QFile numberOfMessage(QDir::currentPath()+"/"+type+"Chats/chats/"+_dst+"numberOfMessage.txt");
    if(numberOfMessage.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&numberOfMessage);
        out<<numberOfChats;
        numberOfMessage.close();
    }
}

void MyFile::writeMessages(QString type, QString _dst, Message _msg)
{

          QString Path(QDir::currentPath()+"/"+type+"Chats/chats/"+_dst+".txt");
            QFile Chats(Path);
            if(Chats.open(QIODevice::Append|QIODevice::Text)){
                QTextStream out(&Chats);
                out<< _msg.getSender().getUsername() <<" "<<_msg.getMessageBody()<<" "<<_msg.getSentDate().getRowDate()<<"\n";
                Chats.close();
            }
}

void MyFile::writeMessages(int numberOfChats, QString type, QString _dst, QJsonObject jsonObj)
{
    QString Path(QDir::currentPath()+"/"+type+"Chats/chats/"+_dst+".txt");
    QFile Chats(Path);
    if(Chats.open(QIODevice::Append|QIODevice::Text)){
        QTextStream out(&Chats);
        for(int j=0;j<numberOfChats;j++){
            QJsonObject block = jsonObj.value("block "+QString::number(j)).toObject();
            Message sentMessage(User(block.value("src").toString()),Date(block.value("date").toString()),block.value("body").toString());
            out<<sentMessage.getSender().getUsername()<<" "<<sentMessage.getMessageBody()<<" "<<sentMessage.getSentDate().getRowDate()<<"\n";
        }
        Chats.close();
    }
}

int MyFile::readNumberOfMessage(QString type, QString _dst)
{
    int numOfChats;
    QFile numberOfMessage(QDir::currentPath()+"/"+type+"Chats/chats/"+_dst+"numberOfMessage.txt");
    if(numberOfMessage.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&numberOfMessage);
        in>>numOfChats;
        numberOfMessage.close();
        return numOfChats;
    }

}

