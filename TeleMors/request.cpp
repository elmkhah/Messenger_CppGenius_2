#include "request.h"
#include<QCoreApplication>


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
        return result;
        }
    return result ;
}

int Request::signup(User& _user){
    QString url;
    url+=baseUrl+"signup?username="+_user.getUsername()+"&password="+_user.getPassword();
    QJsonObject jsonObj = Request::sendRequest(url);
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    return result;
}

int Request::logout(User & _user)
{
    QString url;
    url+=baseUrl+"logout?username="+_user.getUsername()+"&password="+_user.getPassword();
    QString infoPath(QDir::currentPath()+"/information/");

    QJsonObject jsonObj = Request::sendRequest(url);
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
        return result;
    }
    return result;
}

int Request::createGroup(QString _token,QString _name,QString _title){
    QString url;

    //***url***
    url+=baseUrl+"creategroup?token="+_token+"&group_name="+_name+"&group_title="+_title;


    QString groupPath(QDir::currentPath()+"/groupChats/");

    QJsonObject jsonObj = Request::sendRequest(url);
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
        if (groupMessageFile.open(QIODevice::Append | QIODevice::Text)){
            groupMessageFile.close();}
        return result;
    }
    return result;
}

int Request::createChannel(QString _token,QString _name, QString _title)
{
    QString url;

    //***url***
    url+=baseUrl+"createchannel?token="+_token+"&channel_name="+_name+"&channel_title="+_title;


    QString channelPath(QDir::currentPath()+"/channelChats/");

    QJsonObject jsonObj = Request::sendRequest(url);
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){

        //***add channel to files***
        QFile channelListFile( channelPath+"list.txt");
        if (channelListFile.open(QIODevice::Append | QIODevice::Text)){
            QTextStream out(&channelListFile);
            out<<_name<<"\n"<<_title<<"\n";}
        channelListFile.close();
        QFile channelMessageFile(channelPath+"/chats/"+_name+".txt");
        if (channelMessageFile.open(QIODevice::Append | QIODevice::Text)){
            channelMessageFile.close();}
        return result;
    }
    return result;
}

int Request::joinGroup(QString _token,QString _name)
{
    QString _title="0";
    QString url;
     //***url***
    url+=baseUrl+"joingroup?token="+_token+"&group_name="+_name;
    QString groupPath(QDir::currentPath()+"/groupChats/");

    QJsonObject jsonObj = Request::sendRequest(url);
    QString resultCode=jsonObj.value("code").toString();
    int result=resultCode.toInt();
    if(result==200){
        //***add group to files***
        QFile groupListFile(groupPath +"list.txt");
        if (groupListFile.open(QIODevice::Append | QIODevice::Text)){
            QTextStream out(&groupListFile);
            out<<_name<<"\n"<<_title<<"\n";}
        groupListFile.close();
        QFile groupMessageFile(groupPath+"/chats/"+_name+".txt");
        if (groupMessageFile.open(QIODevice::Append | QIODevice::Text)){
           //add messege of group to file
        }
        return result;
    }
    return result;
}

int Request::getGroupList(QString _token)
{
    QString url;
        //***url***
    url+=baseUrl+"getgrouplist?token="+_token;
    QString groupPath(QDir::currentPath()+"/groupChats/");

    QJsonObject jsonObj = Request::sendRequest(url);
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
        if(groupListFile.open(QIODevice::Append|QIODevice::Text)){
            QTextStream out(&groupListFile);
            out<<numberOfGroups<<"\n";
            for(int j=0;j<numberOfGroups;j++){
                QJsonObject block = jsonObj.value("block"+j).toObject();
                QString groupName = block.value("group_name").toString();
                out<<groupName<<"\n";
            }
            groupListFile.close();
        }
        return result;
    }
    return result;
}

int Request::getChannelList(QString _token)
{
    QString url;
        //***url***
    url+=baseUrl+"getchannellist?token="+_token;
    QString channelPath(QDir::currentPath()+"/channelChats/");

    QJsonObject jsonObj = Request::sendRequest(url);
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
        if(channelListFile.open(QIODevice::Append|QIODevice::Text)){
            QTextStream out(&channelListFile);
            out<<numberOfChannels<<"\n";
            for(int j=0;j<numberOfChannels;j++){
                QJsonObject block = jsonObj.value("block"+j).toObject();
                QString channelName = block.value("channel_name").toString();
                out<<channelName<<"\n";
            }
            channelListFile.close();
        }
        return result;
    }
    return result;
}
