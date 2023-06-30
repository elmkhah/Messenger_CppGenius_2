#include "myfile.h"


QString MyFile::getToken()
{
    QString token;
    //       ***add token***
    QFile tokenFile(QDir::currentPath()+"/information/token.txt");
    if (tokenFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&tokenFile);
        in>>token;
        tokenFile.close();
        return token;
    }
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

void MyFile::addUsernamePassword(QString username, QString password)
{
    QFile userPassword(QDir::currentPath()+"/information/usernamePassword.txt");
    if(userPassword.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream out(&userPassword);
            out<<username<<"\n"<<password;
        }
    userPassword.close();
}

QVector<QString> MyFile::readUsernamePassword()
{
    QString username,password;
    QVector<QString> result;
    QFile userPassword(QDir::currentPath()+"/information/usernamePassword.txt");
    if(userPassword.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream in(&userPassword);
            in>>username>>password;
            result.push_back(username);
            result.push_back(password);
    }
    userPassword.close();
    return result;
}

void MyFile::loginFile(const User& _user)
{
    QString infoPath(QDir::currentPath()+"/information/");

    QFile tokenFile(infoPath+"token.txt");
    if (tokenFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&tokenFile);
        out<<_user.getToken();}
    tokenFile.close();

    QFile isLoginFile(infoPath+"isLogin.txt");
    if (isLoginFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&isLoginFile);
        out<<"1";
    isLoginFile.close();
    }
    MyFile ::addUsernamePassword(_user.getUsername(),_user.getPassword());

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

void MyFile::createChat(QString type, QString _name)
{
    QFile MessageFile(QDir::currentPath()+"/"+type+"Chats"+"/chats/"+_name+".txt");
    if (MessageFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        MessageFile.close();
    }
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
                out<< _msg.getSender().getUsername() <<"\n"<<_msg.getMessageBody()<<"\n"<<_msg.getSentDate().getRowDate()<<"\n";
                Chats.close();
            }
}

void MyFile::writeMessages(int numberOfChats, QString type, QString _dst, QJsonObject jsonObj,bool clear)
{

    QString Path(QDir::currentPath()+"/"+type+"Chats/chats/"+_dst+".txt");
    QFile Chats(Path);
    if((clear&&Chats.open(QIODevice::WriteOnly|QIODevice::Text))){//||(!clear&&Chats.open(QIODevice::Append|QIODevice::Text))){
        QTextStream out(&Chats);
        for(int j=0;j<numberOfChats;j++){
            QJsonObject block = jsonObj.value("block "+QString::number(j)).toObject();
            Message sentMessage(User(block.value("src").toString()),Date(block.value("date").toString()),block.value("body").toString());
            out<<sentMessage.getSender().getUsername()<<"\n"<<sentMessage.getMessageBody()<<"\n"<<sentMessage.getSentDate().getRowDate()<<"\n";
        }
        Chats.close();
    }
    if((!clear&&Chats.open(QIODevice::Append|QIODevice::Text))){
        QTextStream out(&Chats);
        for(int j=0;j<numberOfChats;j++){
            QJsonObject block = jsonObj.value("block "+QString::number(j)).toObject();
            Message sentMessage(User(block.value("src").toString()),Date(block.value("date").toString()),block.value("body").toString());
            out<<sentMessage.getSender().getUsername()<<"\n"<<sentMessage.getMessageBody()<<"\n"<<sentMessage.getSentDate().getRowDate()<<"\n";
        }
        Chats.close();
    }
}

void MyFile::writeMessages(int numOfChats, QString type, QJsonObject jsonObj)
{
    QString name;
    QFile listFile(QDir::currentPath()+"/"+type+"Chats/list.txt");
    if(listFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        for(int j=0;j<numOfChats;j++){
            QTextStream out(&listFile);
            QJsonObject block = jsonObj.value("block "+QString::number(j)).toObject();
            if(type=="private"){
             name = block.value("src").toString();
            }
            else{
            name = block.value(type+"_name").toString();
            }
            out<<name<<"\n";
        }
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

bool MyFile::existChats(QString type, QString _dst)
{
    QString ChatPath(QDir::currentPath()+"/"+type+"Chats/chats/"+_dst+".txt");
    QFile Chats(ChatPath);
    if(Chats.exists()) return 1;
    return 0;
}

void MyFile::writeNumberOfChats(int numOfChats, QString type)
{
    QFile numberOfChats(QDir::currentPath()+"/"+type+"Chats"+"/numberOfChats.txt");
    if(numberOfChats.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&numberOfChats);
            out<<numOfChats;
        numberOfChats.close();
    }
}

int MyFile::readNumberOfChats(QString type)
{
    QString numOfChats;
    QFile numberOfChats(QDir::currentPath()+"/"+type+"Chats/"+"numberOfChats.txt");
    if(numberOfChats.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&numberOfChats);
        in>>numOfChats;
        numberOfChats.close();

    }
    return numOfChats.toInt();
}

void MyFile::addNameTitel(QString type, QString _name)
{
    QFile ListFile(QDir::currentPath()+"/"+type+"Chats/"+"list.txt");
    if (ListFile.open(QIODevice::Append | QIODevice::Text)){
        QTextStream out(&ListFile);
        out<<_name<<"\n";
        ListFile.close();
    }
}

QString MyFile::getTimeLastMessage(QString type, QString _dst)
{
    // calculate number of message in dst chat
    int numberOfMessages = MyFile::readNumberOfMessage(type, _dst);
    if (numberOfMessages == 0) {
        QString empty = "";
        return empty;
    }

    QString lastLine;
    QFile lastMessage(QDir::currentPath() + "/" + type + "Chats/chats/" + _dst + ".txt");
    if (lastMessage.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&lastMessage);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.isNull()) {
            lastLine = line;
            }
        }
        lastMessage.close();

        QDateTime lastMsgDateTime = QDateTime::fromString(lastLine, "yyyyMMddhhmmss");
        lastMsgDateTime = lastMsgDateTime.addSecs(1);
        QString newLastLine = lastMsgDateTime.toString("yyyyMMddhhmmss");
        return newLastLine;
    }
}

bool MyFile::setChannelAdmin(QString myUser_name,QString _channelName)
{
    int numberOfMessages=MyFile::readNumberOfMessage("channel",_channelName);
    if(numberOfMessages==0){
        return false;
    }
    QString AdminName;
    QFile findChannelAdmin(QDir::currentPath()+"/channelChats/chats/"+_channelName+".txt");
    qDebug()<<QDir::currentPath()+"/channelChats/chats/"+_channelName+".txt";
    if(findChannelAdmin.open(QIODevice::ReadOnly|QIODevice::Text)){
             QTextStream in(&findChannelAdmin);
        in>>AdminName;
        findChannelAdmin.close();
        QFile setAdmin(QDir::currentPath()+"/channelChats/chats/"+_channelName+"isAdmin.txt");
        if(setAdmin.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream out(&setAdmin);

            if(AdminName==myUser_name) {
                out<<1;

            }
            else{

                out<<0;
            }
         setAdmin.close();
        }
    }
    return true;
}

void MyFile::setChannelAdmin(QString _channelName, int determinate)
{
    QFile setAdmin(QDir::currentPath()+"/channelChats/chats/"+_channelName+"isAdmin.txt");
    if(setAdmin.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&setAdmin);
        out<<determinate;
        setAdmin.close();
    }

}

void MyFile::writeActiveChat( QString name)
{
    QFile active(QDir::currentPath()+"/active.txt");
    if(active.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&active);
        out<<name;
        active.close();
    }
}

QVector<QString> MyFile::readChats(QString type){
    QVector<QString> chats;
    MyFile f;
    QString temp;
    QFile listFile(QDir::currentPath()+"/"+type+"Chats/list.txt");
    if(listFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&listFile);

        for(int i=0;i<f.readNumberOfChats(type);i++){
            in>>temp;
            chats.push_front(temp);
        }
        listFile.close();
    }
    return chats;
}

QVector<Message> MyFile::readMessages(QString type,QString dst){
    QVector<Message> messages;
    MyFile f;
    QString _username,_msg,_date;
    QFile listFile(QDir::currentPath()+"/"+type+"Chats/chats/"+dst+".txt");
    if(listFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&listFile);
        while(!in.atEnd()){
            _username=in.readLine();
            _msg=in.readLine();
            _date=in.readLine();
            User _user(_username);
            Date _time(13,_date);
            Message temp(_user,_time,_msg);
            messages.push_back(temp);
        }
        listFile.close();
    }
    return messages;
}
