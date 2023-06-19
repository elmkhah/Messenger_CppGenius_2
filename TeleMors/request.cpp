#include "request.h"
#include<QCoreApplication>
#define OFFLINE 500

Request::Request()
{
    baseUrl="http://api.barafardayebehtar.ml:8080/";
}

QJsonObject Request::sendRequest(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QNetworkReply *reply = manager->get(request);
    while (!reply->isFinished()) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    if (reply->error() == QNetworkReply::NoError) {
    QByteArray data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    reply->deleteLater();
    return jsonObj;
    }
     else {
    if (reply->error() == QNetworkReply::HostNotFoundError) {
        qDebug() << "Host not found";
    }
    reply->deleteLater();
    return QJsonObject();
    }
}

QString Request::getToken()
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
    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    qDebug()<<result;
    if(result==200){
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
        }
    return result;
    }
    return OFFLINE;
}

int Request::signup(User& _user){
    QString url;
    url+=baseUrl+"signup?username="+_user.getUsername()+"&password="+_user.getPassword();
    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    return result;
    }
    return OFFLINE;

}

int Request::logout(User & _user)
{
    QString url;
    url+=baseUrl+"logout?username="+_user.getUsername()+"&password="+_user.getPassword();
    QString infoPath(QDir::currentPath()+"/information/");

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){

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
    return result;
    }
    return OFFLINE;
}

int Request::createGroup(QString _token,QString _name,QString _title){
    QString url;
    int numOfChats;

    //***url***
    url+=baseUrl+"creategroup?token="+_token+"&group_name="+_name+"&group_title="+_title;


    QString groupPath(QDir::currentPath()+"/groupChats/");

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){

        //***add group to files***
        QFile groupListFile(groupPath+"list.txt");
        if (groupListFile.open(QIODevice::Append | QIODevice::Text)){
            QTextStream out(&groupListFile);
            out<<_name<<"\n"<<_title<<"\n";}
        groupListFile.close();
        QFile groupMessageFile(groupPath+"/chats/"+_name+".txt");
        if (groupMessageFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            groupMessageFile.close();}

        //add number of groups
        QFile numberOfGroups(groupPath+"numberOfGroups.txt");
        if(numberOfGroups.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&numberOfGroups);
            in>>numOfChats;}
        numberOfGroups.close();
        if(numberOfGroups.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&numberOfGroups);
            out<<numOfChats+1;}
        numberOfGroups.close();
    }
    return result;
    }
    return OFFLINE;
}

int Request::createChannel(QString _token,QString _name, QString _title)
{
    QString url;
    int numOfChats;

    //***url***
    url+=baseUrl+"createchannel?token="+_token+"&channel_name="+_name+"&channel_title="+_title;


    QString channelPath(QDir::currentPath()+"/channelChats/");

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){

        //***add channel to files***
        QFile channelListFile( channelPath+"list.txt");
        if (channelListFile.open(QIODevice::Append | QIODevice::Text)){
            QTextStream out(&channelListFile);
            out<<_name<<"\n"<<_title<<"\n";}
        channelListFile.close();

        //set isAdmin
        QFile channelMessageFile(channelPath+"/chats/"+_name+".txt");
        if (channelMessageFile.open(QIODevice::Append | QIODevice::Text)){
            QTextStream out(&channelMessageFile);
            out<<"1\n";
            channelMessageFile.close();}

        //add number of channels
        QFile numberOfChannels(channelPath+"numberOfChannels.txt");
        if(numberOfChannels.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&numberOfChannels);
            in>>numOfChats;}
        numberOfChannels.close();
        if(numberOfChannels.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&numberOfChannels);
            out<<numOfChats+1;}
        numberOfChannels.close();
    }
    return result;
    }
    return OFFLINE;
}

int Request::joinGroup(QString _token,QString _name)
{
    QString _title="0";
    QString url;
    int numOfChats;

     //***url***
    url+=baseUrl+"joingroup?token="+_token+"&group_name="+_name;
    QString groupPath(QDir::currentPath()+"/groupChats/");

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        //***add group to files***
        QFile groupListFile(groupPath +"list.txt");
        if (groupListFile.open(QIODevice::Append | QIODevice::Text)){
            QTextStream out(&groupListFile);
            out<<_name<<"\n"<<_title<<"\n";}
        groupListFile.close();

        //add number of groups
        QFile numberOfGroups(groupPath+"numberOfGroups.txt");
        if(numberOfGroups.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&numberOfGroups);
            in>>numOfChats;}
        numberOfGroups.close();
        if(numberOfGroups.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&numberOfGroups);
            out<<numOfChats+1;}
        numberOfGroups.close();

        QFile groupMessageFile(groupPath+"/chats/"+_name+".txt");
        if (groupMessageFile.open(QIODevice::Append | QIODevice::Text)){
           //add messege of group to file
        }
    }
    return result;
    }
    return OFFLINE;
}

int Request::joinChannel(QString _token,QString _name)
{
    QString _title="0";
    QString url;
    int numOfChats;
        //***url***
    url+=baseUrl+"joinchannel?token="+_token+"&channel_name="+_name;
    QString channelPath(QDir::currentPath()+"/channelChats/");

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        //***add channel to files***
        QFile channelListFile(channelPath +"list.txt");
        if (channelListFile.open(QIODevice::Append | QIODevice::Text)){
            QTextStream out(&channelListFile);
            out<<_name<<"\n"<<_title<<"\n";}
        channelListFile.close();

        //add number of channels
        QFile numberOfChannels(channelPath+"numberOfChannels.txt");
        if(numberOfChannels.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&numberOfChannels);
            in>>numOfChats;}
        numberOfChannels.close();
        if(numberOfChannels.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&numberOfChannels);
            out<<numOfChats+1;}
        numberOfChannels.close();

        //set isAdmin
        QFile channelMessageFile(channelPath+"/chats/"+_name+".txt");
        if (channelMessageFile.open(QIODevice::Append | QIODevice::Text)){
                QTextStream out(&channelMessageFile);
                out<<"0\n";
            //add messege of channel to file
            channelMessageFile.close();
        }
    }
    return result;
    }
    return OFFLINE;
}

int Request::getGroupList(QString _token)
{
    QString url;
        //***url***
    url+=baseUrl+"getgrouplist?token="+_token;
    QString groupPath(QDir::currentPath()+"/groupChats/");

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        QString messageResult=jsonObj.value("message").toString();
        //*******calculate number of groups***********
        int i=0;
        QString num="";
        while(messageResult[i]!='-')
            i++;
        i++;
        while(messageResult[i]!='-'){
            num+=messageResult[i];
            i++;
        }
        int numberOfGroups=num.toInt();
        QFile groupListFile(groupPath+"list.txt");
        QFile numOfGroups(groupPath+"numberOfGroups.txt");

        // add groups to file
        if(numOfGroups.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream out(&numOfGroups);
            out<<numberOfGroups<<"\n";
            numOfGroups.close();}
        if(groupListFile.open(QIODevice::WriteOnly|QIODevice::Text)){
            for(int j=0;j<numberOfGroups;j++){
                QTextStream out(&groupListFile);
                QJsonObject block = jsonObj.value("block "+QString::number(j)).toObject();
                QString groupName = block.value("group_name").toString();
                out<<groupName<<"\n";
            }
            groupListFile.close();
        }
    }
    return result;
    }
    return OFFLINE;
}

int Request::getChannelList(QString _token)
{
    QString url;
        //***url***
    url+=baseUrl+"getchannellist?token="+_token;
    QString channelPath(QDir::currentPath()+"/channelChats/");

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        QString messageResult=jsonObj.value("message").toString();
        //*******calculate number of channels***********
        int i=0;
        QString num="";
        while(messageResult[i]!='-')
            i++;
        i++;
        while(messageResult[i]!='-'){
            num+=messageResult[i];
            i++;
        }
        int numberOfChannels=num.toInt();
        QFile channelListFile(channelPath+"list.txt");
        QFile numOfChannels(channelPath+"numberOfChannels.txt");

        // add channels to file
        if(numOfChannels.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream out(&numOfChannels);
            out<<numberOfChannels<<"\n";
            numOfChannels.close();}
        if(channelListFile.open(QIODevice::WriteOnly|QIODevice::Text)){
            for(int j=0;j<numberOfChannels;j++){
                QTextStream out(&channelListFile);
                QJsonObject block = jsonObj.value("block "+QString::number(j)).toObject();
                QString channelName = block.value("channel_name").toString();
                out<<channelName<<"\n";
            }
            channelListFile.close();
        }
    }
    return result;
    }
    return OFFLINE;
}

int Request::getUserList(QString _token)
{
    QString url;
        //***url***
    url+=baseUrl+"getuserlist?token="+_token;
    QString userPath(QDir::currentPath()+"/userChats/");

    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        QString messageResult=jsonObj.value("message").toString();
        //*******calculate number of users***********
        int i=0;
        QString num="";
        while(messageResult[i]!='-')
            i++;
        i++;
        while(messageResult[i]!='-'){
            num+=messageResult[i];
            i++;
        }
        int numberOfUsers=num.toInt();
        QFile numOfUsers(userPath+"numberOfUsers.txt");

        // add users to file
        if(numOfUsers.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream out(&numOfUsers);
            out<<numberOfUsers<<"\n";
            numOfUsers.close();}

        QFile userListFile(userPath+"list.txt");
        if(userListFile.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream out(&userListFile);
            for(int j=0;j<numberOfUsers;j++){
                QJsonObject block = jsonObj.value("block "+QString::number(j)).toObject();
                QString UserName = block.value("src").toString();
                out<<UserName<<"\n";
            }
            userListFile.close();
        }
    }
    return result;
    }
    return OFFLINE;
}

int Request::sendMessageUser(User &_dst, Message _msg)
{
    QString url;
    int numOfChats;
        //***url***
    url+=baseUrl+"sendmessageuser?token="+_msg.getSender().getToken()+"&dst="+_dst.getUsername()+"&body="+_msg.getMessageBody();
    QString userPath(QDir::currentPath()+"/userChats/");
    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){

        //*********check user chat history************
        QString userChatPath(QDir::currentPath()+"/userChats/chats/"+_dst.getUsername()+".txt");
        QFile userChats(userChatPath);
        if(userChats.exists()){
            if(userChats.open(QIODevice::WriteOnly|QIODevice::Text)){
                QTextStream out(&userChats);
                out<< _msg.getSender().getUsername() <<" "<<_msg.getMessageBody()<<" "<<_msg.getSentDate().getRowDate()<<"\n";
                userChats.close();
            }
        }
        else{
            if(userChats.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream out(&userChats);
                out<< _msg.getSender().getUsername() <<" "<<_msg.getMessageBody()<<" "<<_msg.getSentDate().getRowDate()<<"\n";
                userChats.close();
            }

            //add number of private chats

            QFile numberOfUsers(userPath+"numberOfUsers.txt");
            if(numberOfUsers.open(QIODevice::ReadOnly | QIODevice::Text)){
                QTextStream in(&numberOfUsers);
                in>>numOfChats;}
            numberOfUsers.close();
            if(numberOfUsers.open(QIODevice::WriteOnly | QIODevice::Text)){
                QTextStream out(&numberOfUsers);
                out<<numOfChats+1;}
            numberOfUsers.close();
        }

    }
    return result;
    }
    return OFFLINE;
}

int Request::sendMessageGroup(QString _groupName, Message _msg)
{
    QString url;
    //***url***
    url+=baseUrl+"sendmessagegroup?token="+_msg.getSender().getToken()+"&dst="+_groupName+"&body="+_msg.getMessageBody();
    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){

        QString groupChatPath(QDir::currentPath()+"/groupChats/chats/"+_groupName+".txt");
        QFile groupChats(groupChatPath);
        if(groupChats.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream out(&groupChats);
            out<< _msg.getSender().getUsername() <<" "<<_msg.getMessageBody()<<" "<<_msg.getSentDate().getRowDate()<<"\n";
            groupChats.close();
        }
    }
    return result;
    }
    return OFFLINE;
}

int Request::sendMessageChannel(QString _channelName, Message _msg)
{
    QString url;
    //***url***
    url+=baseUrl+"sendmessagechannel?token="+_msg.getSender().getToken()+"&dst="+_channelName+"&body="+_msg.getMessageBody();
    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){

        QString channelChatPath(QDir::currentPath()+"/channelChats/chats/"+_channelName+".txt");
        QFile channelChats(channelChatPath);
        if(channelChats.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream out(&channelChats);
            out<< _msg.getSender().getUsername() <<" "<<_msg.getMessageBody()<<" "<<_msg.getSentDate().getRowDate()<<"\n";
            channelChats.close();
        }
    }
    return result;
    }
    return OFFLINE;
}

int Request::getUserChats(QString _token,QString _dst, Date _date)
{
    QString url;
    //***url***
    url+=baseUrl+"getuserchats?token="+_token+"&dst="+_dst;
    if(_date.getRowDate()==Date().getRowDate());
    //********add data if parametr data send***//////
    else {
    url+="&date="+_date.getRowDate();
    }


    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        QString messageResult=jsonObj.value("message").toString();
        //*******calculate number of message with dst user***********
        int i=0;
        QString num="";
        while(messageResult[i]!='-')
            i++;
        i++;
        while(messageResult[i]!='-'){
            num+=messageResult[i];
            i++;
        }
        int numberOfChats=num.toInt();

        QString userPath(QDir::currentPath()+"/userChats/chats/"+_dst+".txt");
        QFile userChats(userPath);
        if(userChats.open(QIODevice::Append|QIODevice::Text)){
            QTextStream out(&userChats);
            for(int j=0;j<numberOfChats;j++){
                QJsonObject block = jsonObj.value("block "+QString::number(j)).toObject();
                Message sentMessage(User(block.value("src").toString()),Date(block.value("date").toString()),block.value("body").toString());
                out<<sentMessage.getSender().getUsername()<<" "<<sentMessage.getMessageBody()<<" "<<sentMessage.getSentDate().getRowDate();
            }
            userChats.close();
        }
    return result;
    }
    }
    return OFFLINE;
}

int Request::getGroupChats(QString _token, QString _dst, Date _date)
{
    QString url;
    //***url***
    url+=baseUrl+"getgroupchats?token="+_token+"&dst="+_dst;
    if(_date.getRowDate()==Date().getRowDate());
    //********add data if parametr data send***//////
    else {
    url+="&date="+_date.getRowDate();
    }


    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
    QString messageResult=jsonObj.value("message").toString();
    //*******calculate number of message with dst user***********
    int i=0;
    QString num="";
    while(messageResult[i]!='-')
            i++;
    i++;
    while(messageResult[i]!='-'){
            num+=messageResult[i];
            i++;
    }
    int numberOfChats=num.toInt();

    QString groupPath(QDir::currentPath()+"/groupChats/chats/"+_dst+".txt");
    QFile groupChats(groupPath);
    if(groupChats.open(QIODevice::Append|QIODevice::Text)){
            QTextStream out(&groupChats);
            for(int j=0;j<numberOfChats;j++){
                QJsonObject block = jsonObj.value("block "+QString::number(j)).toObject();
                Message sentMessage(User(block.value("src").toString()),Date(block.value("date").toString()),block.value("body").toString());
                out<<sentMessage.getSender().getUsername()<<" "<<sentMessage.getMessageBody()<<" "<<sentMessage.getSentDate().getRowDate();
            }
            groupChats.close();
    }
    return result;
    }
    }
    return OFFLINE;

}

int Request::getChannelChats(QString _token, QString _dst, Date _date)
{
    QString url;
    //***url***
    url+=baseUrl+"getchannelchats?token="+_token+"&dst="+_dst;
    if(_date.getRowDate()==Date().getRowDate());
    //********add data if parametr data send***//////
    else {
    url+="&date="+_date.getRowDate();
    }


    QJsonObject jsonObj = Request::sendRequest(url);
    if(!jsonObj.isEmpty()){
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
    QString messageResult=jsonObj.value("message").toString();
    //*******calculate number of message with dst user***********
    int i=0;
    QString num="";
    while(messageResult[i]!='-')
            i++;
    i++;
    while(messageResult[i]!='-'){
            num+=messageResult[i];
            i++;
    }
    int numberOfChats=num.toInt();

    QString channelPath(QDir::currentPath()+"/channelChats/chats/"+_dst+".txt");
    QFile channelChats(channelPath);
    if(channelChats.open(QIODevice::Append|QIODevice::Text)){
            QTextStream out(&channelChats);
            for(int j=0;j<numberOfChats;j++){
                QJsonObject block = jsonObj.value("block "+QString::number(j)).toObject();
                Message sentMessage(User(block.value("src").toString()),Date(block.value("date").toString()),block.value("body").toString());
                out<<sentMessage.getSender().getUsername()<<" "<<sentMessage.getMessageBody()<<" "<<sentMessage.getSentDate().getRowDate();
            }
            channelChats.close();
    }
    return result;
    }
    }
    return OFFLINE;

}

